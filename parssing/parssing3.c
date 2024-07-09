/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parssing3.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haalouan <haalouan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/02 01:20:05 by haalouan          #+#    #+#             */
/*   Updated: 2024/07/09 11:45:20 by haalouan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	count_pipe(char **tab)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (tab[i])
	{
		if (tab && tab[i] && tab[i][0] == '|')
			count++;
		i++;
	}
	return (count + 1);
}

int	finnd_pipe(char **tab, int count)
{
	int	i;
	int	check;

	i = 0;
	check = 0;
	while (i < count && tab[i])
	{
		if (tab[i] && tab[i][0] == '|')
		{
			check = 1;
			break ;
		}
		i++;
	}
	if (check == 0)
		return (0);
	return (i + 1);
}

int	find_redir(char **tab, int count)
{
	int	i;

	i = 0;
	while (i < count)
	{
		if (tab[i][0] == '<')
			break ;
		i++;
	}
	return (i);
}

int	count_args(char **tab, int i)
{
	int	count;

	count = 0;
	if (!tab)
		return (0);
	while (tab && tab[i])
	{
		if (tab[i][0] == '|')
			break ;
		if ((tab[i][0] == '>' || tab[i][0] == '<') && tab[i + 1])
			i += 2;
		else if (ft_strcmp(tab[i], "") != 0)
		{
			i++;
			count++;
		}
		else
			i++;
	}
	return (count);
}

int	count_redir(char **tab, int i)
{
	int	count;

	count = 0;
	while (tab && tab[i] && tab[i][0] && tab[i][0] != '|')
	{
		if (tab[i] && (tab[i][0] == '>' || tab[i][0] == '<'))
			count++;
		i++;
	}
	return (count * 2);
}
