/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achater <achater@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/01 12:50:01 by achater           #+#    #+#             */
/*   Updated: 2024/08/02 12:31:58 by achater          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	export_no_plus(char *key, char *value, t_env **env, t_env **tmp1)
{
	if (key_exist(*env, key) == 0)
		ft_lstadd_back(env, ft_lstnew(key, value));
	else
	{
		if (value == NULL)
		{
			free(key);
			return ;
		}
		while (tmp1)
		{
			if (ft_strcmp((*tmp1)->key, key) == 0)
			{
				free((*tmp1)->value);
				(*tmp1)->value = value;
				break ;
			}
			*tmp1 = (*tmp1)->next;
		}
		free(key);
	}
}

void	export_helper(char *key, char *value, t_env **env, t_env **tmp1)
{
	char	*tmp;

	tmp = NULL;
	if (key[ft_strlen(key) - 1] != '+')
		return (export_no_plus(key, value, env, tmp1));
	key[ft_strlen(key) - 1] = '\0';
	if (key_exist(*env, key) == 0)
		return (ft_lstadd_back(env, ft_lstnew(key, value)));
	while (tmp1)
	{
		if (ft_strcmp((*tmp1)->key, key) == 0)
		{
			tmp = ft_strjoin((*tmp1)->value, value, -1, 0);
			(*tmp1)->value = tmp;
			break ;
		}
		*tmp1 = (*tmp1)->next;
	}
	free(key);
}

void	error_hendler(char *key, char *value, int i)
{
	write(2, "minishell: export not a valid identifier\n", 41);
	exit_status(1);
	if (i == 1)
		free(value);
	if (i == 0)
		free(key);
	if (i == 2)
	{
		free(key);
		free(value);
	}
}

void	export_whith_args(char **args, t_env **tmp1, int i, t_env **env)
{
	char	*key;
	char	*value;

	while (args && args[++i])
	{
		if (args[i][0] == '\0')
		{
			write(2, "minishell: not a valid identifier\n", 35);
			exit_status(1);
			continue ;
		}
		split_by_equal(args[i], &key, &value, 0);
		if (key == NULL)
		{
			error_hendler(key, value, 1);
			continue ;
		}
		if (check_args(key, "export") == 1)
			error_hendler(key, value, 2);
		else if (key[ft_strlen(key) - 1] == '+' && value == NULL )
			error_hendler(key, value, 0);
		else
			export_helper(key, value, env, tmp1);
	}
}

void	ft_export(char **args, t_env **env)
{
	int		i;
	t_env	*tmp1;

	i = -1;
	tmp1 = *env;
	exit_status(0);
	if (args == NULL)
		print_env(*env, ft_strcmp);
	else
		export_whith_args(args, &tmp1, i, env);
}
