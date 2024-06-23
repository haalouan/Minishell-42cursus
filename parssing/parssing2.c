/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parssing2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haalouan <haalouan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/27 11:05:44 by haalouan          #+#    #+#             */
/*   Updated: 2024/06/10 01:54:07 by haalouan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	arg(char **tab, t_list *list, int *ii, int *i)
{
	while (tab[*ii] && tab[*ii][0] && is_character2(tab[*ii][0]) == 0)
	{
		if (tab[*ii] && (tab[*ii][0] == '<'
			|| tab[*ii][0] == '>') && tab[(*ii) + 1])
			(*ii) += 2;
	}
	if (tab[*ii] && is_character2(tab[*ii][0]) == 1 && list->cmd == NULL)
	{
		list->cmd = malloc(ft_strlen(tab[*ii]) + 1);
		if (!list->cmd)
			exit(EXIT_FAILURE);
		ft_strncpy(list->cmd, tab[*ii], ft_strlen(tab[*ii]));
		(*ii)++;
	}
	else if (tab[*ii] && is_character2(tab[*ii][0]) == 1)
	{
		list->args[*i] = malloc(ft_strlen(tab[*ii]) + 1);
		if (!list->args[*i])
			exit(EXIT_FAILURE);
		ft_strncpy(list->args[*i], tab[*ii], ft_strlen(tab[*ii]));
		(*i)++;
		(*ii)++;
	}
	else
		(*ii)++;
}

static void	args(t_list *list, char **tab, int ii)
{
	int	count;
	int	i;

	i = 0;
	count = count_args(tab, ii);
	if (count == 0)
		return ;
	if (!list->cmd)
		count--;
	if (count == 0)
		return ;
	list->args = safe_alloc(count);
	while (i < count)
		arg(tab, list, &ii, &i);
}

static t_list	*list_init(t_list *list)
{
	list = malloc(sizeof(t_list) + 1);
	if (!list)
		exit(EXIT_FAILURE);
	list->cmd = NULL;
	list->redir = NULL;
	list->args = NULL;
	list->check_export = 0;
	return (list);
}

static void	put_in_list(t_list **list, char **tab, int count, int size)
{
	int	k;
	int	pipe;
	int	next_pipe;

	k = 0;
	while (k < size)
	{
		pipe = 0;
		next_pipe = finnd_pipe(tab, count);
		list[k] = list_init(list[k]);
		if (tab && tab[pipe] && tab[pipe][0] && tab[pipe][0] != '>'
			&& tab[pipe][0] != '<')
		{
			list[k]->cmd = malloc(ft_strlen(tab[pipe]) + 1);
			if (!list[k]->cmd)
				exit(EXIT_FAILURE);
			ft_strncpy(list[k]->cmd, tab[pipe], ft_strlen(tab[pipe]));
			pipe++;
		}
		args(list[k], tab, pipe);
		redirection(list, tab, pipe, k);
		tab = tab + next_pipe;
		k++;
	}
	(*list)->nbr = k;
}

int	continue_parssing(t_list **list, char **tab, char *line, t_env *env_list)
{
	int	count;
	int	size;
	int	i;

	i = 0;
	count = count_cmds(line);
	size = count_pipe(tab);
	tab = expend(tab, env_list, 0);
	if (check_error2(tab) == 1)
		return (1);
	while (i <= size)
	{
		list[i] = NULL;
		i++;
	}
	put_in_list(list, tab, count, size);
	return (0);
}
