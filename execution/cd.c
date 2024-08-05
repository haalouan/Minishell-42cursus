/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achater <achater@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/30 16:40:37 by achater           #+#    #+#             */
/*   Updated: 2024/08/03 15:39:35 by achater          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	change_value(t_env **env_list, char *value)
{
	free((*env_list)->value);
	(*env_list)->value = ft_strdup(value);
	return (0);
}

void	update_environment(t_env **env_list, char **oldpwd, char **newpwd)
{
	t_env	*temp;
	int		x;
	int		y;

	x = 0;
	y = 0;
	temp = *env_list;
	while (temp)
	{
		(!ft_strcmp(temp->key, "OLDPWD"))
			&& (change_value(&temp, *oldpwd), x = 1);
		(!ft_strcmp(temp->key, "PWD"))
			&& (change_value(&temp, *newpwd), y = 1);
		temp = temp->next;
	}
	if (x == 0)
		ft_lstadd_back(env_list, ft_lstnew(ft_strdup("OLDPWD"), *oldpwd));
	if (y == 0)
		ft_lstadd_back(env_list, ft_lstnew(ft_strdup("PWD"), *newpwd));
	(x == 1) && (free(*oldpwd), x = exit_status(0));
	(y == 1) && (free(*newpwd), y = exit_status(0));
}

void	ft_cd(char **args, t_env *env_list)
{
	char	*oldpwd;
	char	*newpwd;
	char	*tmp;

	if (args == NULL)
		return ((void)write(2, "no path given\n", 14), (void)exit_status(1));
	oldpwd = getcwd(NULL, 0);
	if (args[0][0] == '~')
	{
		tmp = ft_strjoin3("/Users/", getenv("USER"), args[0] + 1);
		chdir(tmp);
		free(tmp);
	}
	else if (chdir(args[0]) == -1)
	{
		printf("minishell: cd: %s: Not a directory\n", args[0]);
		return ((void)exit_status(1), free(oldpwd));
	}
	newpwd = getcwd(NULL, 0);
	update_environment(&env_list, &oldpwd, &newpwd);
}
