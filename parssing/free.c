/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haalouan <haalouan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/23 13:52:36 by haalouan          #+#    #+#             */
/*   Updated: 2024/07/12 21:05:02 by haalouan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	free_tab(char **tab)
{
	int	i;

	i = 0;
	while (tab && tab[i])
	{
		free(tab[i]);
		tab[i] = NULL;
		i++;
	}
	free(tab);
	tab = NULL;
}

void	free_list(t_list **list)
{
	int	i;

	i = 0;
	while (list && list[i])
	{
		if (list[i]->cmd)
			free(list[i]->cmd);
		free_tab(list[i]->redir);
		free_tab(list[i]->args);
		free(list[i]);
		list[i] = NULL;
		i++;
	}
	free(list);
	list = NULL;
}
