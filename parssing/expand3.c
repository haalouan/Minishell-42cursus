/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand3.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haalouan <haalouan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 04:04:33 by haalouan          #+#    #+#             */
/*   Updated: 2024/06/24 14:46:07 by haalouan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	remove_dollar2(char *tab, int *i, int *k, int check)
{
	if (tab && tab[(*i)] == '\'' && check == 0)
	{
		(*i)++;
		while (tab && tab[(*i)] && tab[(*i)] != '\'')
			(*i)++;
		(*k) = (*i);
	}
}

static void	remove_dollar3(char *tab, int *i, int *chk)
{
	if (tab && tab[(*i)] == '$' && (*chk) == 0)
	{
		(*i)++;
		(*chk) = 1;
	}
}

char	*remove_dollar(char *tab, int check)
{
	int	i;
	int	k;
	int	chk;

	i = 0;
	k = 0;
	chk = 0;
	while (tab && tab[i] != '\0')
	{
		remove_dollar2(tab, &i, &k, check);
		remove_dollar3(tab, &i, &chk);
		tab[k] = tab[i];
		if (tab[i])
		{
			i++;
			k++;
		}
		else
			break ;
	}
	if (tab[k])
		tab[k] = '\0';
	return (tab);
}

static char	*replace_and_remove_dollar(char *tab, char *key, char *value)
{
	tab = ft_str_replace(tab, key, value);
	tab = remove_dollar(tab, 1);
	return (tab);
}

char	**expand_in_double_quote(char **tab, int i, int *j, t_env *env_list)
{
	char	*key;
	char	*value;

	key = NULL;
	value = NULL;
	while (tab && tab[i] && tab[i][*j] && tab[i][*j] != '\"')
	{
		if (tab && tab[i] && tab[i][*j] == '$' && tab[i][*j + 1] != '\"')
		{
			key = get_env_key(tab[i], *j);
			value = get_env_value(key, env_list);
			if (value)
				value = protect_env(value, 0);
			if (key && value)
				tab[i] = replace_and_remove_dollar(tab[i], key, value);
			else
				tab[i] = replace_and_remove_dollar(tab[i], key, "");
		}
		else if (tab && tab[i] && tab[i][*j] == '$' && tab[i][*j + 1] == '\"')
			break ;
		else
			(*j)++;
	}
	return (tab);
}
