/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achater <achater@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 10:43:11 by achater           #+#    #+#             */
/*   Updated: 2024/07/04 10:34:52 by achater          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"


char	**struct_to_char(t_env *env_list)
{
	int	i;
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

void set_env(char **env, t_env **env_list, int i)
{
	char	**splited_env;
	char	*pdw;

	pdw = getcwd(NULL, 0);
	splited_env = NULL;
	if (env[0] == NULL)
	{
		ft_lstadd_back(env_list, ft_lstnew("PWD", pdw));
		ft_lstadd_back(env_list, ft_lstnew("OLDPWD", NULL));
		ft_lstadd_back(env_list, ft_lstnew("SHLVL", "1"));
		ft_lstadd_back(env_list, ft_lstnew("_", "/usr/bin/env"));
		return;
	}
	while(env[i])
	{
		splited_env = ft_split(env[i], '=');
		if (ft_strcmp(splited_env[0],"SHLVL") == 0)
			splited_env[1] = shlvl_increment(splited_env[1]);
		if (ft_strcmp(splited_env[0],"OLDPWD") == 0)
			ft_lstadd_back(env_list, ft_lstnew("OLDPWD", NULL));
		else
			ft_lstadd_back(env_list, ft_lstnew(splited_env[0], splited_env[1]));
		free(splited_env);
		i++;
	}
}
