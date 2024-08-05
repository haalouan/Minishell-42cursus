/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helpers_functions1.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achater <achater@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 17:27:26 by haalouan          #+#    #+#             */
/*   Updated: 2024/07/30 11:48:18 by achater          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*ft_strstr(const char *haystack, const char *needle)
{
	const char	*h = NULL;
	const char	*n = NULL;

	if (!needle || !*needle)
		return ((char *)haystack);
	while (*haystack != '\0')
	{
		h = haystack;
		n = needle;
		if (*haystack == '$')
		{
			haystack++;
			h = haystack;
			n = needle;
			while (h && n && *h == *n && *n != '\0')
			{
				h++;
				n++;
			}
		}
		if (*n == '\0')
			return ((char *)haystack);
		haystack++;
	}
	return (NULL);
}

char	*ft_strdup(char *s1)
{
	char	*s2;
	size_t	len;
	size_t	i;

	i = 0;
	len = ft_strlen(s1);
	s2 = (char *)malloc(len + 1);
	if (s2 == NULL)
		return (NULL);
	while (i < len)
	{
		s2[i] = s1[i];
		i++;
	}
	s2[i] = '\0';
	return (s2);
}

int	ft_isdigit(int c)
{
	if (c >= '0' && c <= '9')
		return (1);
	return (0);
}

int	is_character2(char c)
{
	if (c != '<' && c != '>' && c != '|' && c != ' ' && c != '\t')
		return (1);
	return (0);
}

int	is_character(char c)
{
	if (c != '<' && c != '>' && c != '\'' && c != '\"'
		&& c != '|' && c != ' ' && c != '\t')
		return (1);
	return (0);
}
