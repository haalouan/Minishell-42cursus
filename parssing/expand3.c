/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand3.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achater <achater@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 04:04:33 by haalouan          #+#    #+#             */
/*   Updated: 2024/07/13 08:33:36 by achater          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static char	*replace_and_remove_dollar(char *tab, char *key, char *value)
{
	tab = ft_str_replace(tab, key, value);
	tab = remove_dollar(tab, 1);
	return (tab);
}

static char	*exp_d_q(char *key, char *value, char *tab)
{
	if (key && value)
		tab = replace_and_remove_dollar(tab, key, value);
	else
		tab = replace_and_remove_dollar(tab, key, "");
	return (tab);
}

static char	*exp_d(char *tab, char **value, int j, t_env *env_list)
{
	char	*key;

	key = NULL;
	if (exppp(tab, j) == 11)
		key = cont_exp(value);
	else
		key = cont_exp2(value, j, env_list, tab);
	return (key);
}

char	**expand_in_double_quote(char **tab, int i, int *j, t_env *env_list)
{
	char	*key;
	char	*value;

	key = NULL;
	value = NULL;
	while (tab && tab[i] && tab[i][*j] && tab[i][*j] != '\"')
	{
		if (ft_isdigit(tab[i][*j + 1]) == 1)
			tab[i] = expand_digit(tab[i]);
		else if (tab && tab[i] && tab[i][*j] == '$' && tab[i][*j + 1] != '\"')
		{
			key = exp_d(tab[i], &value, *j, env_list);
			tab[i] = exp_d_q(key, value, tab[i]);
		}
		else if (tab && tab[i] && tab[i][*j] == '$' && tab[i][*j + 1] == '\"')
			break ;
		else
			(*j)++;
	}
	if (ft_strcmp(key, "?") != 0)
	{
		free(key);
		free(value);
	}
	return (tab);
}
