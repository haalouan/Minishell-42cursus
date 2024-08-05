/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achater <achater@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 10:43:11 by achater           #+#    #+#             */
/*   Updated: 2024/07/25 11:30:36 by achater          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	**struct_to_char(t_env *env_list)
{
	int		i;
	char	**new_env;
	t_env	*temp;

	i = 0;
	temp = env_list;
	new_env = malloc(sizeof(char *) * (ft_lstsize(env_list) + 1));
	if (new_env == NULL)
		return (NULL);
	while (temp)
	{
		if (temp->value == NULL)
			new_env[i] = ft_strjoin3(temp->key, "", "");
		else
			new_env[i] = ft_strjoin3(temp->key, "=", temp->value);
		temp = temp->next;
		i++;
	}
	new_env[i] = NULL;
	return (new_env);
}

void	ft_free(char **str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		free(str[i]);
		i++;
	}
	free(str);
}

void	set_env(char **env, t_env **env_list, int i)
{
	char	**s_env;

	s_env = malloc(sizeof(char *) * 2);
	while (env[++i])
	{
		split_by_equal(env[i], &s_env[0], &s_env[1], 0);
		if (ft_strcmp(s_env[0], "SHLVL") == 0)
			s_env[1] = shlvl_increment(s_env[1]);
		if (ft_strcmp(s_env[0], "OLDPWD") == 0)
			(1) && (free(s_env[1]), ft_lstadd_back(env_list, \
			ft_lstnew(s_env[0], NULL)), i = i + 0);
		else
			ft_lstadd_back(env_list, ft_lstnew(s_env[0], s_env[1]));
	}
	free(s_env);
}
