/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_line.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haalouan <haalouan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/02 00:46:44 by haalouan          #+#    #+#             */
/*   Updated: 2024/06/24 12:30:49 by haalouan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	charact(char *line, int *i)
{
	while (is_character(line[*i]) == 1 && line[*i] != '\0')
		(*i)++;
}

void	continue_handle_word(char *line, int *i)
{
	while (line[*i] != '\0')
	{
		charact(line, i);
		if (line[*i] == '\'')
		{
			(*i)++;
			hndl_line(line, i);
			if (line[*i] == '\'')
				(*i)++;
			if (is_ch(line[*i]) == 0 && line[*i] != '\'' && line[*i] != '\"')
				break ;
		}
		else if (line[*i] == '\"')
		{
			(*i)++;
			while (line && line[*i] && line[(*i)] != '\"' && line[*i] != '\0')
				(*i)++;
			if (line[*i] == '\"')
				(*i)++;
			if (is_ch(line[*i]) == 0 && line[*i] != '\'' && line[*i] != '\"')
				break ;
		}
		else
			break ;
	}
}

void	handle_word(char **le, char **tab)
{
	int		i;
	char	*line;

	line = NULL;
	line = *le;
	i = 0;
	continue_handle_word(line, &i);
	*le += i;
	add_tab(line, tab, i);
}

void	continue_handle_line(t_check check, char **line, char **tab)
{
	if (check.find_here_doc == 1)
	{
		add_tab(*line, tab, 2);
		*line += 1;
	}
	else if (check.find_append_op == 1)
	{
		add_tab(*line, tab, 2);
		*line += 1;
	}
}

void	handle_line(char **line, char **tab, t_check check)
{
	continue_handle_line(check, line, tab);
	if (check.find_pipe == 1)
	{
		add_tab(*line, tab, 1);
		*line += 1;
	}
	else if (check.find_in_re == 1)
	{
		add_tab(*line, tab, 1);
		*line += 1;
	}
	else if (check.find_out_re == 1)
	{
		add_tab(*line, tab, 1);
		*line += 1;
	}
	else if (check.find_word == 1)
		handle_word(line, tab);
	else if (*line)
		*line += 1;
}
