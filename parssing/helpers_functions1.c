/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helpers_functions1.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haalouan <haalouan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 17:27:26 by haalouan          #+#    #+#             */
/*   Updated: 2024/07/10 10:29:39 by haalouan         ###   ########.fr       */
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
	char	*s2 = NULL;
	size_t	len = 0;
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

void print_tab(t_list **list)
{
	int i = 0;
	while (list && list[i])
	{
		int n;
		printf("*-------------------------*\n");
		printf("|            (%d)          |\n", i + 1);
		printf("*-------------*-----------*\n");
		printf("|");
		printf(""ANSI_COLOR_GREEN"    COMOND   " ANSI_RESET_ALL"");
		printf("|");
		printf("   %s\n", list[i]->cmd);
		printf("*-------------*-----------*\n");
		n = 0;
		while (list && list[i] && list[i]->args && list[i]->args[n])
		{
			printf("|");
			printf(""ANSI_COLOR_GREEN"  ARGUMENTS  " ANSI_RESET_ALL"");
			printf("|");
			printf("   %s\n", list[i]->args[n]);
			printf("*-------------*-----------*\n");
			n++;
		}
		n = 0;
		while (list && list[i] && list[i]->redir && list[i]->redir[n])
		{
			printf("|");
			printf(""ANSI_COLOR_GREEN" REDIRECTION " ANSI_RESET_ALL"");
			printf("|");
			printf("   %s\n", list[i]->redir[n]);
			printf("*-------------*-----------*\n");
			n++;
			printf("|");
			printf(""ANSI_COLOR_GREEN"     FILE    " ANSI_RESET_ALL"");
			printf("|");
			if (list[i]->redir)
				printf("   %s\n", list[i]->redir[n]);
			printf("*-------------*-----------*\n");
			n++;
		}
		i++;
		if (list[i])
			printf("            <PIPE>\n");
	}
}