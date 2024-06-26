/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helpers_functions3.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haalouan <haalouan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 01:59:14 by haalouan          #+#    #+#             */
/*   Updated: 2024/06/24 12:18:23 by haalouan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_strncmp(const char *str1, const char *str2, size_t n)
{
	while (n > 0)
	{
		if (*str1 == '\0' || *str2 == '\0' || *str1 != *str2)
			return ((unsigned char)(*str1) - (unsigned char)(*str2));
		str1++;
		str2++;
		n--;
	}
	return (0);
}

int	is_ch(char c)
{
	if (c == '<' || c == '>' || c == '\'' || c == '\"'
		|| c == '|' || c == ' ' || c == '\t')
		return (0);
	return (1);
}
