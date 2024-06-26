/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand5.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haalouan <haalouan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/24 15:45:59 by haalouan          #+#    #+#             */
/*   Updated: 2024/06/24 15:53:54 by haalouan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	search_for_value(char *str, char *s)
{
	int	i;

	i = 0;
	while (str && str[i] && str[i] != '=')
		i++;
	if (str[i] != '=')
		return (1);
	if (ft_strncmp(str, s, i) == 0)
		return (1);
	return (0);
}

char	*expand_digit(char *str)
{
	int		i;
	char	*new;

	i = 1;
	new = malloc(ft_strlen(str) - 2 + 1);
	if (!new)
		exit(EXIT_FAILURE);
	while (str[i])
	{
		if (ft_isdigit(str[i]) == 1)
			i++;
		break ;
	}
	new = ft_strncpy(new, str + i, ft_strlen(str));
	return (new);
}

static int	exp(char *tab, int j)
{
	if (ft_isdigit(tab[j + 1]) == 1)
	{
		tab = expand_digit(tab);
		return (1);
	}
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

char	**continue_expand(char **tab, t_int *f, t_env *env_list)
{
	char	*key;
	char	*value;

	key = NULL;
	value = NULL;
	if (exp(tab[f->i], f->j) == 1)
		return (tab);
	key = get_env_key(tab[f->i], f->j);
	value = handle_value(key, env_list);
	if (key && value)
	{
		tab[f->i] = ft_str_replace(tab[f->i], key, value);
		tab[f->i] = remove_dollar(tab[f->i], 1);
		if (search_for_value(tab[f->i], value) == 1 && f->in_here_doc == 0)
			tab = change_tab(tab, tab[f->i]);
		return (tab);
	}
	else
	{
		tab[f->i] = ft_str_replace(tab[f->i], key, "");
		tab[f->i] = remove_dollar(tab[f->i], 1);
		if (tab[f->i][0] == '\0')
			tab = ft_realloc(tab, tab[f->i]);
	}
	return (tab);
}
