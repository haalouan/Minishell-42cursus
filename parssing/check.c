/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haalouan <haalouan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/02 00:35:06 by haalouan          #+#    #+#             */
/*   Updated: 2024/06/23 15:01:11 by haalouan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	check_check(char *line, t_check *check)
{
	if (line && *line && (is_character(*line) == 1
			|| *line == '\"' || *line == '\''))
		check->find_word = 1;
	if (line && *line == '|')
		check->find_pipe = 1;
	if (line && *line == '>')
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

void	check_init(t_check *check)
{
	check->find_word = -1;
	check->find_pipe = -1;
	check->find_in_re = -1;
	check->find_out_re = -1;
	check->find_append_op = -1;
	check->find_here_doc = -1;
}

static int	continue_check(char *tab, char *tab2)
{
	if (!tab || !tab2)
		return (0);
	if (tab[0] == '|' && tab2[0] == '|')
		return (1);
	else if (tab[0] == '>' && tab2[0] == '|')
		return (1);
	else if (tab[0] == '<' && tab2[0] == '|')
		return (1);
	else if (tab[0] == '<' && tab2[0] == '<')
		return (1);
	else if (tab[0] == '>' && tab2[0] == '>')
		return (1);
	else if (tab[0] == '>' && tab2[0] == '<')
		return (1);
	else if (tab[0] == '<' && tab2[0] == '>')
		return (1);
	else
		return (0);
}

int	check(char **tab)
{
	int	i;

	i = 0;
	if (!tab || !*tab)
		return (2);
	if (tab[0][0] == '|')
		return (1);
	while (tab && tab[i])
	{
		if (continue_check(tab[i], tab[i + 1]) == 1)
			return (1);
		else
			i++;
	}
	if (tab && tab[i] && tab[i][0] == '\0' && tab[i - 1]
		&& (tab[i - 1][0] == '|' || tab[i - 1][0] == '<'
		|| tab[i - 1][0] == '>'))
		return (1);
	return (0);
}
