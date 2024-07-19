/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achater <achater@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/30 16:40:37 by achater           #+#    #+#             */
/*   Updated: 2024/07/14 16:48:02 by achater          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	change_value(t_env **env_list, char *value)
{
	free((*env_list)->value);
	(*env_list)->value = ft_strdup(value);
	return (0);
}

void	change_env_last_cmd(t_list *cmds, t_env **env_list)
{
	t_env	*tmp;
	char	*last_cmd;
	int	i;

	tmp = *env_list;
	i = 0;
	if (cmds->args == NULL)
		last_cmd = cmds->cmd;
	else
	{
		while (cmds->args[i])
			i++;
		last_cmd = cmds->args[i - 1];
	}
	while (tmp)
	{
		if (ft_strcmp(tmp->key, "_") == 0)
			change_value(&tmp, last_cmd);
		tmp = tmp->next;
	}
}

void	ft_cd(char **args, t_env *env_list,int x, int y)
{
	char	*oldpwd;
	char	*newpwd;

	(1) && (oldpwd = getcwd(NULL, 0), newpwd = getcwd(NULL, 0));
	if (args == NULL)
		write(2, "no path given\n", 14);
	else if (chdir(args[0]) == -1)
	{
		printf("minishell: cd: %s: No such file or directory\n", args[0]);
		exit_status(1);
	}
	while (env_list && env_list->next)
	{
		(!ft_strcmp(env_list->key, "OLDPWD"))
			&& (change_value(&env_list, oldpwd), x++);
		(!ft_strcmp(env_list->key, "PWD"))
			&& (change_value(&env_list, newpwd), y++);
		env_list = env_list->next;
	}
	if (x == 0)
		ft_lstadd_back(&env_list, ft_lstnew("OLDPWD", oldpwd));
	if (y == 0)
		ft_lstadd_back(&env_list, ft_lstnew("PWD", newpwd));
	(x == 1) && (free(oldpwd), x = 1);
	(y == 1) && (free(newpwd), y = 1);
}
