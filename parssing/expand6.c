/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand6.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haalouan <haalouan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/02 00:31:58 by haalouan          #+#    #+#             */
/*   Updated: 2024/07/08 10:08:19 by haalouan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*ft_str_replace(char *tab, const char *key, const char *value)
{
	size_t	key_len;
	size_t	value_len;
	char	*occurrence;
	size_t	new_size;
	char	*new_str;

	if (!tab || !key || !value)
		return (ft_strdup(tab));
	key_len = ft_strlen(key);
	value_len = ft_strlen(value);
	occurrence = ft_strstr(tab, key);
	if (!occurrence)
		return (ft_strdup(tab));
	new_size = ft_strlen(tab) - key_len + value_len + 1;
	new_str = (char *)malloc(new_size);
	if (!new_str)
		return (NULL);
	memcpy(new_str, tab, occurrence - tab);
	new_str[occurrence - tab] = '\0';
	strcat(new_str, value);
	strcat(new_str, occurrence + key_len);
	free(tab);
	return (new_str);
}

char	*add_dollar(char *str)
{
	char	*value;
	int		i;
	int		j;

	i = 0;
	j = 0;
	value = malloc(ft_strlen(str) + 2);
	if (!value)
		return (NULL);
	value[i] = '$';
	i++;
	while (str[j])
	{
		value[i] = str[j];
		i++;
		j++;
	}
	value[i] = '\0';
	return (value);
}

char	*get_env_value(char *key, t_env *export_i)
{
	t_env	*tmp;
	char	*value;

	if (!key)
		return (NULL);
	tmp = export_i;
	while (tmp)
	{
		if (!strcmp(tmp->key, key))
		{
			value = ft_strdup(tmp->value);
			return (value);
		}
		tmp = tmp->next;
	}
	return (NULL);
}

char	*get_env_key(char *str, int i)
{
	char	*key;
	int		key_start;

	key = NULL;
	if (!str)
		return (NULL);
	while (str && str[i] && str[i] != '$')
		i++;
	if (str && str[i] == '$')
	{
		i++;
		key_start = i;
		while (str && str[i] && ((str[i] >= 'a' && str[i] <= 'z')
				|| (str[i] >= 'A' && str[i] <= 'Z')
				|| (str[i] >= '0' && str[i] <= '9') || str[i] == '_'))
			i++;
		key = (char *)malloc((i - key_start + 1) * sizeof(char));
		if (!key)
			exit(EXIT_FAILURE);
		strncpy(key, &str[key_start], i - key_start);
		key[i - key_start] = '\0';
	}
	return (key);
}

char	*protect_env(char *str, int key)
{
	char	*value;
	int		i;
	int		j;

	i = 0;
	j = 0;
	value = malloc(ft_strlen(str) + 2 + 1);
	value[j++] = '\"';
	if (key == 1)
	{
		while (str[i] == ' ' || str[i] == '\t')
			i++;
	}
	while (str && str[i])
		value[j++] = str[i++];
	if (key == 1 && (value[j - 1] == ' ' || value[j - 1] == '\t'))
	{
		j--;
		while (value[j] == ' ' || value[j] == '\t')
			j--;
		j++;
	}
	value[j++] = '\"';
	value[j] = '\0';
	free(str);
	return (value);
}
