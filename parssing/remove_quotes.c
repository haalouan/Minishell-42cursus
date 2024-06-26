/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   remove_quotes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haalouan <haalouan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/02 00:47:28 by haalouan          #+#    #+#             */
/*   Updated: 2024/06/24 14:55:52 by haalouan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	handle_cmds(t_list **list, int *i, int *j, int *k)
{
	while (list[*i] && list[*i]->cmd && list[*i]->cmd[*j] != '\0')
	{
		if (list[*i]->cmd[*j] == '\"')
		{
			(*j)++;
			while (list[*i]->cmd[*j] && list[*i]->cmd[*j] != '\"')
				list[*i]->cmd[(*k)++] = list[*i]->cmd[(*j)++];
			if (list[*i]->cmd[*j] == '\"')
				(*j)++;
		}
		else if (list[*i]->cmd[*j] && list[*i]->cmd[*j] == '\'')
		{
			(*j)++;
			while (list[*i]->cmd[*j] && list[*i]->cmd[*j] != '\'')
				list[*i]->cmd[(*k)++] = list[*i]->cmd[(*j)++];
			if (list[*i]->cmd[*j] == '\'')
				(*j)++;
		}
		else if (list[*i]->cmd[*j] && list[*i]->cmd[*j] != '\"'
			&& list[*i]->cmd[*j] != '\'')
			list[*i]->cmd[(*k)++] = list[*i]->cmd[(*j)++];
	}
	if (list[*i] && list[*i]->cmd)
		list[*i]->cmd[*k] = '\0';
}

static void	re2(t_list *list, int *j, int *l, int *k)
{
	(*l)++;
	while (list->redir[*j][*l] && list->redir[*j][*l] != '\"')
	{
		list->redir[*j][*k] = list->redir[*j][*l];
		(*k)++;
		(*l)++;
	}
	if (list->redir[*j][*l] == '\"')
		(*l)++;
}

static void	re(t_list *list, int *j, int *l, int *k)
{
	if (list->redir[*j][*l] == '\"')
		re2(list, j, l, k);
	else if (list->redir[*j][*l] == '\'')
	{
		(*l)++;
		while (list->redir[*j][*l] && list->redir[*j][*l] != '\'')
		{
			list->redir[*j][*k] = list->redir[*j][*l];
			(*k)++;
			(*l)++;
		}
		if (list->redir[*j][*l] == '\'')
			(*l)++;
	}
	else if (list->redir[*j][*l] && list->redir[*j][*l] != '\"'
		&& list->redir[*j][*l] != '\'')
	{
		list->redir[*j][*k] = list->redir[*j][*l];
		(*k)++;
		(*l)++;
	}
}

void	handle_redi(t_list **list, int *i, int *j, int *l)
{
	int	k;

	while (list && list[*i] && list[*i]->redir && list[*i]->redir[*j])
	{
		*l = 0;
		k = 0;
		if (list[*i]->redir[*j][0] == '\"' || list[*i]->redir[*j][0] == '\'')
			list[*i]->flag_here_doc = 1;
		else
			list[*i]->flag_here_doc = 0;
		while (list[*i]->redir[*j][*l])
			re(list[*i], j, l, &k);
		if (list && list[*i] && list[*i]->redir && list[*i]->redir[*j])
		{
			list[*i]->redir[*j][k] = '\0';
			(*j)++;
		}
	}
}

void	remove_quotes(t_list **list)
{
	int	i;
	int	k;
	int	l;
	int	j;

	i = 0;
	while (list[i])
	{
		j = 0;
		k = 0;
		if (list[i]->cmd && *list[i]->cmd)
			handle_cmds(list, &i, &j, &k);
		j = 0;
		l = 0;
		if (list[i]->redir && *list[i]->redir)
			handle_redi(list, &i, &j, &l);
		j = 0;
		l = 0;
		if (list[i]->args && *list[i]->args)
			handle_args(list, &i, &j, &l);
		i++;
	}
}
