/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achater <achater@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/23 15:01:15 by haalouan          #+#    #+#             */
/*   Updated: 2024/08/06 09:22:55 by achater          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	check_error(char **tab)
{
	if (check(tab) == 2)
	{
		free_tab(tab);
		return (1);
	}
	else if (check(tab) == 1)
	{
		handle_error();
		free_tab(tab);
		return (1);
	}
	if (check_error2(tab) == 1)
		return (1);
	return (0);
}

int	check_ambiguous_redir(char **tab)
{
	int	i;

	i = 0;
	while (tab && tab[i])
	{
		if (tab[i][0] == '>' || tab[i][0] == '<')
		{
			i++;
			if (tab[i][0] == '\0')
				return (1);
		}
		i++;
	}
	return (0);
}

int	check_error2(char **tab)
{
	if (check(tab) == 2)
		return (1);
	// if (check(tab) == 0 && check_ambiguous_redir(tab) == 1)
	// {
	// 	printf("minishell: ambiguous redirect\n");
	// 	exit_status(1);
	// 	free_tab(tab);
	// 	return (1);
	// }
	return (0);
}

int	check_line(char *line)
{
	int	i;

	i = 0;
	while (line && line[i] != '\0')
		i++;
	i--;
	while (line && i != 0 && (line[i] == ' ' || line[i] == '\t'))
		i--;
	if (line[i] && (line[i] == '|' || line[i] == '>' || line[i] == '<'))
	{
		exit_status(258);
		return (1);
	}
	return (0);
}
