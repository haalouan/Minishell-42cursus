/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand7.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haalouan <haalouan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/07 14:10:35 by haalouan          #+#    #+#             */
/*   Updated: 2024/07/07 14:11:13 by haalouan         ###   ########.fr       */
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
	char	*new;

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
	return (new);
}

char	*int_to_str(int num)
{
	int		temp;
	int		len;
	int		i;
	char	*str;

	temp = num;
	len = 0;
	while (temp != 0)
	{
		len++;
		temp /= 10;
	}
	str = (char *)malloc((len + 1));
	if (str == NULL)
		return (NULL);
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
