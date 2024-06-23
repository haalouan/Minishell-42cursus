/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expend_in_here_doc.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haalouan <haalouan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/09 17:53:18 by haalouan          #+#    #+#             */
/*   Updated: 2024/06/23 22:52:14 by haalouan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	continue_expend_in_here_doc(char **l, t_env *env_list,
	int i, char *v)
{
	char	*k;

	k = NULL;
	if ((*l)[i] == '$' && ft_isdigit((*l)[i + 1]) == 1)
	{
		k = get_env_key((*l), i);
		v = expend_digit((*l) + i);
		(*l) = ft_str_replace((*l), k, v);
		(*l) = remove_dolar((*l), 1);
	}
	else if ((*l)[i] == '$' && (*l)[i + 1] != '\'' && (*l)[i + 1] != '\"')
	{
		k = get_env_key((*l), i);
		v = get_env_value(k, env_list);
	}
	if (k && v && (*l)[i] == '$' && (*l)[i + 1] != '\'' && (*l)[i + 1] != '\'')
	{
		(*l) = ft_str_replace((*l), k, v);
		(*l) = remove_dolar((*l), 1);
	}
	else if ((*l)[i] == '$' && (*l)[i + 1] != '\'' && (*l)[i + 1] != '\"')
	{
		(*l) = ft_str_replace((*l), k, "");
		(*l) = remove_dolar((*l), 1);
	}
}

char	*expend_in_here_doc(char *line, t_env *env_list, int ex)
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
			continue_expend_in_here_doc(&line, env_list, i, value);
		}
		i++;
	}
	return (line);
}
