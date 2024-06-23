/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haalouan <haalouan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/23 13:52:36 by haalouan          #+#    #+#             */
/*   Updated: 2024/06/23 15:07:04 by haalouan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	free_tab(char **tab)
{
	int	i;

	i = 0;
	while (tab[i])
	{
		free(tab[i]);
		i++;
	}
	free(tab);
}

void	free_list(t_list **list)
{
	int	i;

	i = 0;
	while (list[i])
	{
		if (list[i]->cmd)
			free(list[i]->cmd);
		free_tab(list[i]->redir);
		free_tab(list[i]->args);
		free(list[i]);
		i++;
	}
	free(list);
}
