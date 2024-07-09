/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_in_here_doc.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haalouan <haalouan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/09 17:53:18 by haalouan          #+#    #+#             */
/*   Updated: 2024/07/09 12:30:28 by haalouan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	get_key_value(char **l, char **k, char **v, int i)
{
	*k = get_env_key((*l), i);
	*v = expand_digit((*l) + i);
}

static void	continue_expand_in_here_doc(char **l, t_env *env_list,
	int i, char *v)
{
	char	*k;

	k = NULL;
	if ((*l)[i] == '$' && ft_isdigit((*l)[i + 1]) == 1)
	{
		get_key_value(l, &k, &v, i);
		(*l) = ft_str_replace((*l), k, v);
		(*l) = remove_dollar((*l), 1);
	}
	else if ((*l)[i] == '$' && (*l)[i + 1] != '\'' && (*l)[i + 1] != '\"')
	{
		k = get_env_key((*l), i);
		v = get_env_value(k, env_list);
	}
	if (k && v && (*l)[i] == '$' && (*l)[i + 1] != '\'' && (*l)[i + 1] != '\'')
	{
		(*l) = ft_str_replace((*l), k, v);
		(*l) = remove_dollar((*l), 1);
	}
	else if ((*l)[i] == '$' && (*l)[i + 1] != '\'' && (*l)[i + 1] != '\"')
	{
		(*l) = ft_str_replace((*l), k, "");
		(*l) = remove_dollar((*l), 1);
	}
	free(k);
}

char	*expand_in_here_doc(char *line, t_env *env_list, int ex)
{
	int		i;
	char	*value;

	i = 0;
	value = NULL;
	if (ex == 1)
		return (line);
	while (line && line[i])
	{
		if (line[i] == '$')
		{
			if (line[i] == '\'')
			{
				i++;
				while (line[i] && line[i] != '\'')
					i++;
			}
			continue_expand_in_here_doc(&line, env_list, i, value);
		}
		i++;
	}
	free(value);
	return (line);
}
