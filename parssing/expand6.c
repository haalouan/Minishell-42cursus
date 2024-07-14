/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand6.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haalouan <haalouan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/02 00:31:58 by haalouan          #+#    #+#             */
/*   Updated: 2024/07/14 03:35:42 by haalouan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*ft_str_replace(char *tab, const char *key, char *value)
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
		exit(EXIT_FAILURE);
	memcpy(new_str, tab, occurrence - tab);
	new_str[occurrence - tab] = '\0';
	ft_strcat(new_str, value);
	ft_strcat(new_str, occurrence + key_len);
	free(tab);
	return (new_str);
}

char	*get_env_value(char *key, t_env *export_i)
{
	t_env	*tmp;
	char	*value;

	value = NULL;
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
		ft_strncpy(key, &str[key_start], i - key_start);
		key[i - key_start] = '\0';
	}
	return (key);
}

char	*protect_env(char *str, int key)
{
	char	*value;
	t_int	f;

	f.i = 0;
	f.j = 0;
	value = NULL;
	value = malloc(ft_strlen(str) + 2 + 1);
	if (!value)
		exit(EXIT_FAILURE);
	value[f.j++] = '\"';
	while ((key == 1 && str[f.i] == ' ') || str[f.i] == '\t')
		f.i++;
	while (str && str[f.i])
		value[f.j++] = str[f.i++];
	if (key == 1 && (value[f.j - 1] == ' ' || value[f.j - 1] == '\t'))
	{
		f.j--;
		while (value[f.j] == ' ' || value[f.j] == '\t')
			f.j--;
		f.j++;
	}
	value[f.j++] = '\"';
	value[f.j] = '\0';
	free(str);
	return (value);
}

char	**ft_realloc(char **tab)
{
	int		i;
	int		j;
	int		count;
	char	**new_tab;

	count = 0;
	i = 0;
	j = 0;
	new_tab = NULL;
	count = c_str(tab);
	new_tab = safe_alloc(count);
	while (j < count)
	{
		if (ft_strcmp(tab[i], "") != 0)
		{
			new_tab[j] = ft_strdup(tab[i]);
			j++;
		}
		i++;
	}
	free_tab(tab);
	return (new_tab);
}
