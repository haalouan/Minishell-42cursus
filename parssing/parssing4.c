/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parssing4.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haalouan <haalouan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 01:51:31 by haalouan          #+#    #+#             */
/*   Updated: 2024/07/09 11:44:51 by haalouan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static char	*safe_init(int size)
{
	char	*str;
	int		i;

	i = 0;
	str = malloc(size + 1);
	if (!str)
		exit(EXIT_FAILURE);
	while (i <= size)
	{
		str[i] = '\0';
		i++;
	}
	return (str);
}

static int	redir(char **tab, t_list *list, int *i, int *j)
{
	if (tab && tab[*i] && (tab[*i][0] == '>' || tab[*i][0] == '<'))
	{
		list->redir[*j] = safe_init(ft_strlen(tab[*i]));
		ft_strncpy(list->redir[*j], tab[*i], ft_strlen(tab[*i]));
		(*i)++;
		if (tab && tab[*i] && tab[*i][0] == '|')
			return (1);
		else if (!tab[*i])
			return (1);
		(*j)++;
		list->redir[*j] = safe_init(ft_strlen(tab[*i]));
		ft_strncpy(list->redir[*j], tab[*i], ft_strlen(tab[*i]));
		(*j)++;
		(*i)++;
	}
	else if (tab[*i] && is_character2(tab[*i][0]) == 1 && list->cmd == NULL
		&& ft_strcmp(tab[*i], "") != 0)
	{
		list->cmd = safe_init(ft_strlen(tab[*i]));
		ft_strncpy(list->cmd, tab[*i], ft_strlen(tab[*i]));
		(*i)++;
	}
	else
		(*i)++;
	return (0);
}

char	**safe_alloc(int count)
{
	char	**str;
	int		i;

	i = 0;
	str = NULL;
	str = (char **)malloc(sizeof(char *) * (count + 1) + 1);
	if (!str)
		exit(EXIT_FAILURE);
	while (i <= count)
	{
		str[i] = NULL;
		i++;
	}
	return (str);
}

void	redirection(t_list **list, char **tab, int pipe, int k)
{
	int	i;
	int	count;
	int	size;
	int	j;

	j = 0;
	i = 0;
	size = 0;
	count = count_redir(tab, pipe);
	list[k]->redir = safe_alloc(count);
	i = 0;
	while (tab && tab[i] && tab[i][0] != '|' && list[k]->redir)
	{
		if (redir(tab, list[k], &i, &j) == 1)
			break ;
	}
}

void	continue_arg(char **tab, int *ii)
{
	while (tab[*ii] && tab[*ii][0] && is_character2(tab[*ii][0]) == 0)
	{
		if (tab[*ii] && (tab[*ii][0] == '<'
			|| tab[*ii][0] == '>') && tab[(*ii) + 1])
			(*ii) += 2;
	}
}
