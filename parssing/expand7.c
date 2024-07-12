/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand7.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haalouan <haalouan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/07 14:10:35 by haalouan          #+#    #+#             */
/*   Updated: 2024/07/10 10:28:43 by haalouan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	search_for_value(char *str, char *s)
{
	int	i;

	i = 0;
	while (str && str[i] && str[i] != '=')
		i++;
	if (str[i] != '=')
		return (1);
	if (ft_strncmp(str, s, i) == 0)
		return (1);
	return (0);
}

char	*expand_digit(char *str)
{
	int		i;
	char	*new = NULL;

	i = 1;
	new = malloc(ft_strlen(str) - 2 + 1);
	if (!new)
		exit(EXIT_FAILURE);
	while (str[i])
	{
		if (ft_isdigit(str[i]) == 1)
			i++;
		break ;
	}
	new = ft_strncpy(new, str + i, ft_strlen(str) -2);
	free(str);
	return (new);
}

char	*int_to_str(int num)
{
	int		temp = 0;
	int		len;
	int		i = 0;
	char	*str = NULL;

	temp = num;
	len = 0;
	while (temp != 0)
	{
		len++;
		temp /= 10;
	}
	str = (char *)malloc((len + 1));
	if (!str)
		exit(EXIT_FAILURE);
	str[len] = '\0';
	i = len - 1;
	while (i >= 0)
	{
		str[i] = (num % 10) + '0';
		num /= 10;
		i--;
	}
	return (str);
}

char	*protect_new_tab(char *str)
{
	int		i;
	int		k;
	char	*s = NULL;

	i = 1;
	k = 1;
	s = malloc(ft_strlen(str) + 1);
	if (!s)
		exit(EXIT_FAILURE);
	while (str && str[i])
	{
		while (str[i] && (str[i] == ' ' || str[i] == '\t'))
			i++;
		s[0] = '\"';
		s[k] = str[i];
		k++;
		i++;
	}
	s[k] = '\0';
	free(str);
	return (s);
}
