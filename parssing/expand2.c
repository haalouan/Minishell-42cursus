/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haalouan <haalouan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/24 15:45:59 by haalouan          #+#    #+#             */
/*   Updated: 2024/07/09 12:16:50 by haalouan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	exppp(char *tab, int j)
{
	if (tab[j + 1] == '?')
		return (11);
	return (0);
}

static char	*handle_value(char *key, t_env *env_list)
{
	char	*value;

	value = NULL;
	value = get_env_value(key, env_list);
	if (value)
		value = protect_env(value, 1);
	return (value);
}

char	*cont_exp(char **value)
{
	char	*key;

	key = malloc(2);
	if (!key)
		exit(EXIT_FAILURE);
	ft_strncpy(key, "?", 1);
	if (exit_status(-1) == 0)
	{
		*value = malloc(2);
		if (!(*value))
			exit(EXIT_FAILURE);
		ft_strncpy(*value, "0", 1);
	}
	else
		*value = int_to_str(exit_status(-1));
	return (key);
}

char	*cont_exp2(char **value, int j, t_env *env_list, char *tab)
{
	char	*key;

	key = get_env_key(tab, j);
	*value = handle_value(key, env_list);
	return (key);
}

char	**continue_expand(char **tab, t_int *f, t_env *env_list)
{
	char	*key;
	char	*value;

	if (exppp(tab[f->i], f->j) == 11)
		key = cont_exp(&value);
	else
		key = cont_exp2(&value, f->j, env_list, tab[f->i]);
	if (key && value)
	{
		tab[f->i] = ft_str_replace(tab[f->i], key, value);
		tab[f->i] = remove_dollar(tab[f->i], 1);
		if (search_for_value(tab[f->i], value) == 1 && f->in_here_doc == 0)
			tab = change_tab(tab, tab[f->i]);
	}
	else
	{
		tab[f->i] = ft_str_replace(tab[f->i], key, "");
		tab[f->i] = remove_dollar(tab[f->i], 1);
	}
	free(key);
	free(value);
	return (tab);
}
