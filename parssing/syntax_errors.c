/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_errors.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haalouan <haalouan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 21:55:56 by haalouan          #+#    #+#             */
/*   Updated: 2024/06/24 14:49:12 by haalouan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	handle_error(void)
{
	printf("=> " ANSI_BACKGROUND_RED "syntax error" ANSI_RESET_ALL "\n");
}

int	count_single_quote(char *line, int *i)
{
	int	count;

	count = 0;
	count++;
	line++;
	while (line && line[*i] && line[*i] != '\'')
		(*i)++;
	if (line && line[*i] == '\'')
	{
		count++;
		(*i)++;
	}
	return (count);
}

int	count_double_quote(char *line, int *i)
{
	int	count;

	count = 0;
	count++;
	line++;
	while (line && line[*i] && line[*i] != '\"')
		(*i)++;
	if (line && line[*i] == '\"')
	{
		count++;
		(*i)++;
	}
	return (count);
}

int	count_quote(char *line)
{
	int	countd;
	int	counts;
	int	i;

	i = 0;
	countd = 0;
	counts = 0;
	while (line && line[i])
	{
		if (line && line[i] == '\"')
			countd += count_double_quote(line, &i);
		else if (line && line[i] == '\'')
			counts += count_single_quote(line, &i);
		line++;
	}
	if (counts % 2 == 1 || countd % 2 == 1)
	{
		handle_error();
		return (1);
	}
	return (0);
}
