/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   remove_quotes2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haalouan <haalouan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 01:37:37 by haalouan          #+#    #+#             */
/*   Updated: 2024/06/10 01:39:05 by haalouan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	arg2(t_list *list, int *j, int *l, int *k)
{
	(*l)++;
	while (list->args[*j][*l] && list->args[*j][*l] != '\"')
	{
		list->args[*j][*k] = list->args[*j][*l];
		(*k)++;
		(*l)++;
	}
	if (list->args[*j][*l] == '\"')
		(*l)++;
}

static void	arg(t_list *list, int *j, int *l, int *k)
{
	if (list->args[*j][*l] == '\"')
		arg2(list, j, l, k);
	else if (list->args[*j][*l] == '\'')
	{
		(*l)++;
		while (list->args[*j][*l] && list->args[*j][*l] != '\'')
		{
			list->args[*j][*k] = list->args[*j][*l];
			(*k)++;
			(*l)++;
		}
		if (list->args[*j][*l] == '\'')
			(*l)++;
	}
	else if (list->args[*j][*l] && list->args[*j][*l] != '\"'
		&& list->args[*j][*l] != '\'')
	{
		list->args[*j][(*k)] = list->args[*j][*l];
		(*k)++;
		(*l)++;
	}
}

void	handele_args(t_list **list, int *i, int *j, int *l)
{
	int	k;

	while (list && list[*i] && list[*i]->args && list[*i]->args[*j])
	{
		*l = 0;
		k = 0;
		while (list[*i] && list[*i]->args && list[*i]->args[*j]
			&& list[*i]->args[*j][*l])
			arg(list[*i], j, l, &k);
		if (list[*i]->args[*j])
			list[*i]->args[*j][k] = '\0';
		(*j)++;
	}
}
