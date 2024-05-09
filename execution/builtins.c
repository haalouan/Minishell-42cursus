/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haalouan <haalouan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 11:28:38 by achater           #+#    #+#             */
/*   Updated: 2024/05/09 12:40:49 by haalouan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	change_value(t_env **env_list,char *value)
{
	free((*env_list)->value);
	(*env_list)->value = ft_strdup(value);
}

void ft_cd(char	**args, t_env **env_list)
{
	char *oldpwd;
	char *newpwd;

	oldpwd = getcwd(NULL, 0);
	if (args == NULL )
		chdir(getenv("HOME"));
	else if (chdir(args[0]) == -1)
		printf("minishell: cd: %s: No such file or directory\n", args[0]);
	newpwd = getcwd(NULL, 0);
	while((*env_list)->next)
	{
		if(ft_strcmp((*env_list)->key, "OLDPWD") == 0)
			change_value(env_list, oldpwd);
		if(ft_strcmp((*env_list)->key, "PWD") == 0)
			change_value(env_list, newpwd);
		(*env_list) = (*env_list)->next;
	}
	return;
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
void	ft_echo(char **args, int n, int j, int x)
{
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

void	ft_exit(char **args, t_list *cmds)
{
	if(cmds->nbr == 1)
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
void	handle_one_cmd(t_list *cmds, t_env **env_list,char **env)
{
	int pid;
	if (ft_strcmp(cmds->cmd, "echo") == 0)
		ft_echo(cmds->args, 0, 0, 0);
	else if (ft_strcmp(cmds->cmd, "cd") == 0)
		ft_cd(cmds->args, env_list);
	else if (ft_strcmp(cmds->cmd, "env") == 0 && cmds)
		ft_env(*env_list, cmds->args);
	else if (ft_strcmp(cmds->cmd, "export") == 0)
		ft_export(cmds->args, env_list);
	else if (ft_strcmp(cmds->cmd, "pwd") == 0 || ft_strcmp(cmds->cmd, "PWD") == 0)
		ft_pwd();
	else if (ft_strcmp(cmds->cmd, "unset") == 0)
		*env_list = ft_unset(env_list,cmds->args);
	else if (ft_strcmp(cmds->cmd, "exit") == 0)
		ft_exit(cmds->args, cmds);
	else
	{
		pid = fork();
		if (pid == -1)
			error();
		if (pid == 0)
			handle_cmd(cmds, env);
		else
			wait(NULL);
	}
}


void	ft_builtins(t_list *cmds, t_env **env_list,char **env)
{
	if (ft_strcmp(cmds->cmd, "echo") == 0)
		ft_echo(cmds->args, 0, 0, 0);
	else if (ft_strcmp(cmds->cmd, "cd") == 0)
		ft_cd(cmds->args, env_list);
	else if (ft_strcmp(cmds->cmd, "env") == 0 && cmds)
		ft_env(*env_list, cmds->args);
	else if (ft_strcmp(cmds->cmd, "export") == 0)
		ft_export(cmds->args, env_list);
	else if (ft_strcmp(cmds->cmd, "pwd") == 0 || ft_strcmp(cmds->cmd, "PWD") == 0)
		ft_pwd();
	else if (ft_strcmp(cmds->cmd, "unset") == 0)
		*env_list = ft_unset(env_list,cmds->args);
	else if (ft_strcmp(cmds->cmd, "exit") == 0)
		ft_exit(cmds->args, cmds);
	else
		handle_cmd(cmds, env);
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

void execution(t_list **list, t_env *env_list, char **env)
{
    int i;
    int fd[2];
    pid_t pid;
    int prev_pipe = -1;

    i = 0;
    if ((*list)->nbr == 1)
    	handle_one_cmd(*list, &env_list, env);
	else
	{
        while (i < (*list)->nbr)
        {
            if (pipe(fd) == -1)
                error();
            pid = fork();
            if (pid == -1)
                error();
            if (pid == 0)
	        {
                if (i != 0)
	                {
                    dup2(prev_pipe, STDIN_FILENO);
                    close(prev_pipe);
                    }
                    if (i != (*list)->nbr - 1)
                        dup2(fd[1], STDOUT_FILENO);
                    close(fd[0]);
                    ft_builtins(list[i], &env_list, env);
                     exit(EXIT_SUCCESS);
            }
	        else
	        {
                if (i != 0)
                    close(prev_pipe);
                prev_pipe = fd[0];
                close(fd[1]);
            }
            i++;
        }
        while(wait(NULL) > 0)
    	    ;
    }
}
