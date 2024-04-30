/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achater <achater@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 11:28:38 by achater           #+#    #+#             */
/*   Updated: 2024/04/30 18:37:45 by achater          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_env	*ft_copy_list(t_env *env_list)
{
	t_env *new;
	t_env *tmp;

	new = NULL;
	tmp = env_list;
	while (tmp)
	{
		ft_lstadd_back(&new, ft_lstnew(tmp->key, tmp->value));
		tmp = tmp->next;
	}
	return (new);
}


void	sort_and_print_env(t_env *lst, int (*cmp)(char*,char*))
{
	char	*swap;
	char	*swap2;
	t_env	*tmp;

	tmp = lst;
	while(lst->next != NULL)
	{
		if (((*cmp)(lst->key, lst->next->key)) > 0)
		{
			swap = lst->key;
			swap2 = lst->value;
			lst->value = lst->next->value;
			lst->key = lst->next->key;
			lst->next->key = swap;
			lst->next->value = swap2;
			lst = tmp;
		}
		else
			lst = lst->next;
	}
	lst = tmp;
	while(lst)
	{
		if((*cmp)(lst->key, "_") != 0 && lst->value != NULL)
			printf("declare -x %s=\"%s\"\n", lst->key, lst->value);
		else if((*cmp)(lst->key, "_") != 0 && lst->value == NULL)
			printf("declare -x %s\n", lst->key);
		lst = lst->next;
	}
}

void	ft_export(char **args, t_env **env)
{
	t_env *tmp;
	int i = 0;
	// char **split;

	tmp = ft_copy_list(*env);
	if (args == NULL)
	{
		sort_and_print_env(tmp, ft_strcmp);
		return;
	}
	else
	{
		while(args[i])
		{
			if(check_args(args[i], "export") == 1)
			{
				printf("minishell: export: `%s': not a valid identifier\n", args[i]);
				return;
			}
			// else
			// {
			// 	split = ft_split(args[i], '=');

			// }
			i++;
		}
	}
}

void ft_cd(char	**args)
{
	if (args == NULL )
	{
		chdir(getenv("HOME"));
		return;
	}
	if (chdir(args[0]) == -1)
	{
		printf("minishell: cd: %s: No such file or directory\n", args[0]);
		return;
	}
}

int cmp(char *s1)
{
	int i = 0;

	if(s1[i] == '-' && s1[i + 1] == 'n')
	{
		i++;
		while(s1[i])
		{
			if(s1[i] != 'n')
				return (1);
			i++;
		}
		return (0);
	}
	return (1);
}
void	ft_echo(char **args)
{
	int j;
	int n;
	int x;

	j = 0;
	n = 0;
	x = 0;
	if (args == NULL)
	{
		printf("\n");
		return;
	}
	if (cmp(args[0]) == 0)
	{
		j++;
		n = 1;
		x = 1;
	}
	while (args[j])
	{
		if (cmp(args[j]) == 0 && n == 1)
		{
			j++;
			continue ;
		}
		if (cmp(args[j]) != 0 )
			n = 0;
		printf("%s", args[j]);
		if (args[j + 1])
			printf(" ");
		j++;
	}
	if (x == 0)
		printf("\n");
}
void	ft_env(t_env *env_list, char **args)
{
	if(args && args[0])
	{
		printf("env: %s: No such file or directory\n", args[0]);
		return;
	}
	while (env_list)
	{
		if(env_list->value != NULL)
			printf("%s=%s\n", env_list->key, env_list->value);
		env_list = env_list->next;
	}
}

void	ft_exit(char **args)
{
	printf("exit\n");
	if(args && args[0])
		printf("minishell: exit: %s: numeric argument required\n", args[0]);
	exit(0);
}

void	ft_pwd()
{
	char *pwd;

	pwd = getcwd(NULL, 0);
	if(pwd == NULL)
	{
		perror("getcwd");
		return;
	}
	printf("%s\n", pwd);
}


void	ft_remove(t_env **env_list, char *key)
{
	t_env *temp = *env_list;
	t_env *prev = NULL;

	while(env_list && temp->next != NULL)
	{
		if (check_args(key, "unset") == 1)
		{
			printf("minishell: unset: `%s': not a valid identifier\n", key);
			return;
		}
		if (ft_strcmp(temp->key, key) != 0)
		{
			prev = temp;
			temp = temp->next;
		}
		else if (prev == NULL && ft_strcmp(temp->key, key) == 0)
		{
			*env_list = temp->next;
			free(temp);
			return;
		}
		else if (ft_strcmp(temp->key, key) == 0)
		{
			prev->next = temp->next;
			free(temp);
			return;
		}
		if(temp->next == NULL && ft_strcmp(temp->key, key) == 0)
		{
			prev->next = NULL;
			free(temp);
			return;
		}
	}
	return;
}

t_env	*ft_unset(t_env **env_list, char **args)
{
	int i = 0;

	if (args == NULL)
		return (*env_list);
	if(env_list == NULL)
		return (NULL);
	while (args[i])
	{
		ft_remove(env_list, args[i]);
		i++;
	}
	return (*env_list);
}

void	ft_builtins(t_list *cmds, t_env **env_list)
{
	if (ft_strcmp(cmds->cmd, "echo") == 0)
		ft_echo(cmds->args);
	else if (ft_strcmp(cmds->cmd, "cd") == 0)
		ft_cd(cmds->args);
	else if (ft_strcmp(cmds->cmd, "env") == 0 && cmds)
		ft_env(*env_list, cmds->args);
	else if (ft_strcmp(cmds->cmd, "export") == 0)
		ft_export(cmds->args, env_list);
	else if (ft_strcmp(cmds->cmd, "pwd") == 0 || ft_strcmp(cmds->cmd, "PWD") == 0)
		ft_pwd();
	else if (ft_strcmp(cmds->cmd, "unset") == 0)
		*env_list = ft_unset(env_list,cmds->args);
	else if (ft_strcmp(cmds->cmd, "exit") == 0)
		ft_exit(cmds->args);
}

void set_env(char **env, t_env **env_list)
{
	int i = 0;
	char **splited_env = NULL;
	char *pdw = NULL;

	pdw = getcwd(NULL, 0);
	if(env == NULL)
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
		ft_lstadd_back(env_list, ft_lstnew(splited_env[0], splited_env[1]));
		i++;
	}
}

void execution(t_list **list, t_env *env_list)
{
	ft_builtins(*list, &env_list);
	// while(env_list)
	// {
	// 	printf("%s=%s\n", env_list->key, env_list->value);
	// 	env_list = env_list->next;
	// }
}
