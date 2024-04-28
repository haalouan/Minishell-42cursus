/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helpers_functions.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haalouan <haalouan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 17:27:26 by haalouan          #+#    #+#             */
/*   Updated: 2024/04/27 22:52:54 by haalouan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

size_t	ft_strlen(const char *str)
{
	size_t	i;
	
	if (str == NULL)
		return 0;
	i = 0;
	while (str[i] != '\0')
		i++;
	return (i);
}

char    *ft_strncpy(char *dest, const char *src, int len)
{
	int i;
	int k;

    i = 0;
	k = 0;
	while (src[i] != '\0' && len > 0)
	{
		if (src[i] == '\'' || src[i] == '\"')
		{
			i++;
			continue;
		}
		dest[k] = src[i];
		i++;
		k++;
		len--;
	}
	dest[k] = '\0';
	return (dest);
}

void check_check(char *line, t_check *check)
{
        if (is_character(*line) == 1 || *line == '\"' || *line == '\'')
            check->find_word = 1;
        if (*line == '$')
            check->find_$ = 1;
        if (*line == '|')
            check->find_pipe = 1;
        if (*line == '>')
        {
			line++;
            if (*line == '>')
                check->find_append_op = 1;
            else if (check->find_append_op == -1)
                check->find_in_re = 1;
        }
        if (*line == '<')
        {
			line++;
            if (*line == '<')
                check->find_here_doc = 1;
            else if (check->find_here_doc == -1)
                check->find_out_re = 1;
        }
}

void check_init(t_check *check)
{
    check->find_word = -1;
    check->find_pipe = -1;
    check->find_in_re = -1;
    check->find_out_re = -1;
    check->find_append_op = -1;
    check->find_here_doc = -1;
    check->find_$ = -1;
}

int	ft_strcmp(const char *str1, const char *str2)
{
	if (!str1 || !str2)
		return 0;
	while (*str1 != '\0' || *str2 != '\0')
	{
		if (*str1 != *str2)
			return ((unsigned char)(*str1) - (unsigned char)(*str2));
		str1++;
		str2++;
	}
	return (0);
}

char *ft_strcat(char *dest, char *src)
{
	int i;
	int j;

	i = 0;
	while (dest[i] != '\0')
		i++;
	j = 0;
	while (src[j] != '\0')
	{
		dest[i + j] = src[j];
		j++;
	}
	dest[i + j] = '\0';
	return (dest);
}

int is_character(char c)
{
	if ((c <= 'Z' && c >= 'A') || (c <= 'z' && c >= 'a') || (c <= '9' && c >= '0') || c == '*' || c == '\\' || c == '-')
		return 1;
	return 0;
}