/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haalouan <haalouan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/24 15:44:43 by haalouan          #+#    #+#             */
/*   Updated: 2024/07/11 12:40:06 by haalouan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static t_int	init2(int in_here_doc)
{
	t_int	f;

	f.i = 0;
	f.j = 0;
	f.in_here_doc = in_here_doc;
	return (f);
}

static void	exp2(char **tab, t_int *f, t_env *env_list)
{
	if (tab[f->i] && tab[f->i][f->j] == '\"')
	{
		f->j++;
		while (tab && tab[f->i] && tab[f->i][f->j] && tab[f->i][f->j] != '\"')
		{
			if (tab && tab[f->i] && tab[f->i][f->j] == '$'
				&& tab[f->i][f->j + 1] != '\0' && tab[f->i][f->j + 1] != '\"')
			{
				if (f->i != 0 && ft_strcmp(tab[f->i - 1], "<<") == 0)
					break ;
				tab = expand_in_double_quote(tab, f->i, &f->j, env_list);
				break ;
			}
			f->j++;
		}
		if (tab && tab[f->i] && tab[f->i][f->j] == '\"')
			f->j++;
	}
}

static void	exp_s(char **tab, t_int *f)
{
	f->j++;
	while (tab && tab[f->i] && tab[f->i][f->j] && tab[f->i][f->j] != '\'')
		f->j++;
	if (tab && tab[f->i] && tab[f->i][f->j] == '\'')
		f->j++;
}

static char	**expp(char **tab, t_int *f, t_env *env_list)
{
	while (tab && tab[f->i] && tab[f->i][f->j])
	{
		exp2(tab, f, env_list);
		if (tab[f->i] && tab[f->i][f->j] == '\'')
			exp_s(tab, f);
		else if (tab[f->i] && tab[f->i][f->j] == '$'
			&& tab[f->i][f->j + 1] != '\"' && tab[f->i][f->j + 1] != '\'')
		{
			if (f->i != 0 && ft_strcmp(tab[f->i - 1], "<<") == 0)
				break ;
			if (ft_isdigit(tab[f->i][f->j + 1]) == 1)
				tab[f->i] = expand_digit(tab[f->i]);
			else if (tab[f->i][f->j + 1] == '\0')
				break ;
			else
				tab = continue_expand(tab, f, env_list);
				
		}
		else if (tab[f->i] && tab[f->i][f->j] == '$'
			&& (tab[f->i][f->j + 1] == '\'' || tab[f->i][f->j + 1] == '\"'))
			tab[f->i] = remove_dollar(tab[f->i], 1);
		else if (tab && tab[f->i] && tab[f->i][f->j])
			f->j++;
	}
	return (tab);
}

char	**expand(char **tab, t_env *env_list, int in_here_doc)
{
	t_int	f;

	f = init2(in_here_doc);
	while (tab && tab[f.i])
	{
		f.j = 0;
		tab = expp(tab, &f, env_list);
		f.i++;
	}
	return (tab);
}
