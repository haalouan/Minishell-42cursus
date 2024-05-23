/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achater <achater@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 11:28:38 by achater           #+#    #+#             */
/*   Updated: 2024/05/21 17:08:35 by achater          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	change_value(t_env **env_list,char *value)
{
	free((*env_list)->value);
	(*env_list)->value = ft_strdup(value);
}

void ft_cd(char	**args, t_env *env_list)
{
	char *oldpwd;
	char *newpwd;

	oldpwd = getcwd(NULL, 0);
	if (args == NULL )
		chdir(getenv("HOME"));
	else if (chdir(args[0]) == -1)
		printf("minishell: cd: %s: No such file or directory\n", args[0]);
	newpwd = getcwd(NULL, 0);
	while(env_list->next)
	{
		if(ft_strcmp(env_list->key, "OLDPWD") == 0)
			change_value(&env_list, oldpwd);
		else if(ft_strcmp(env_list->key, "PWD") == 0)
			change_value(&env_list, newpwd);
		env_list = env_list->next;
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
		if (prev == NULL && ft_strcmp(temp->key, key) == 0)
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

void	ft_unset(t_env **env_list, char **args)
{
	int i = 0;

	if (args == NULL)
		return ;
	if(env_list == NULL)
		return ;
	while (args[i])
	{
		if(ft_strcmp(args[i], "_") == 0)
		{
			i++;
			continue;
		}
		ft_remove(env_list, args[i]);
		i++;
	}
}

char	**struct_to_char(t_env *env_list)
{
	int i;
	char **new_env;
	t_env *temp;

	i = 0;
	temp = env_list;
	new_env = malloc(sizeof(char *) * (ft_lstsize(env_list) + 1));
	if (new_env == NULL)
		return (NULL);
	while (temp)
	{
		if(temp->value == NULL)
			new_env[i] = ft_strjoin3(temp->key, "", "");
		else
			new_env[i] = ft_strjoin3(temp->key, "=", temp->value);
		temp = temp->next;
		i++;
	}
	new_env[i] = NULL;
	return (new_env);
}
int check_builtins(char *cmd)
{
	if (ft_strcmp(cmd, "echo") == 0)
		return (1);
	if (ft_strcmp(cmd, "cd") == 0)
		return (1);
	if (ft_strcmp(cmd,"env") == 0)
		return (1);
	if (ft_strcmp(cmd, "export") == 0)
		return (1);
	if (ft_strcmp(cmd, "pwd") == 0 || ft_strcmp(cmd, "PWD") == 0)
		return (1);
	if (ft_strcmp(cmd, "unset") == 0)
		return(1);
	if (ft_strcmp(cmd, "exit") == 0)
		return (1);
	return (0);
}


void	handle_one_cmd(t_list *cmds, t_env **env_list,char **env, t_here_doc **here_doc)
{
	int pid;
	char **new_env;

	(void)env;
	new_env = struct_to_char(*env_list);
	handle_redir(cmds, here_doc);
	if (cmds->file_in < 0)
		return;
	if (ft_strcmp(cmds->cmd, "cd") == 0)
		ft_cd(cmds->args, *env_list);
	else if (ft_strcmp(cmds->cmd, "unset") == 0)
		ft_unset(env_list,cmds->args);
	else if (ft_strcmp(cmds->cmd, "exit") == 0)
		ft_exit(cmds->args, cmds);
	else if (ft_strcmp(cmds->cmd, "export") == 0 && cmds->args != NULL)
		ft_export(cmds->args, env_list);
	pid = fork();
	if (pid == -1)
		error();
	if (pid == 0)
	{
		dup2(cmds->file_in, STDIN_FILENO);
		dup2(cmds->file_out, STDOUT_FILENO);
		if (ft_strcmp(cmds->cmd, "echo") == 0)
			ft_echo(cmds->args, 0, 0, 0);
		else if (ft_strcmp(cmds->cmd, "env") == 0 && cmds)
			ft_env(*env_list, cmds->args);
		else if (ft_strcmp(cmds->cmd, "export") == 0 && cmds->args == NULL)
			ft_export(cmds->args, env_list);
		else if (ft_strcmp(cmds->cmd, "pwd") == 0 || ft_strcmp(cmds->cmd, "PWD") == 0)
			ft_pwd();
		if(check_builtins(cmds->cmd) == 1)
			exit(0);
		else
			handle_cmd(cmds, new_env);
	}
	else
		wait(NULL);
}

void	ft_builtins(t_list *cmds, t_env **env_list,char **env)
{
	char **new_env;

	(void)env;
	new_env = struct_to_char(*env_list);
	if (ft_strcmp(cmds->cmd, "echo") == 0)
		ft_echo(cmds->args, 0, 0, 0);
	else if (ft_strcmp(cmds->cmd, "cd") == 0)
		ft_cd(cmds->args, *env_list);
	else if (ft_strcmp(cmds->cmd, "env") == 0 && cmds)
		ft_env(*env_list, cmds->args);
	else if (ft_strcmp(cmds->cmd, "export") == 0)
		ft_export(cmds->args, env_list);
	else if (ft_strcmp(cmds->cmd, "pwd") == 0 || ft_strcmp(cmds->cmd, "PWD") == 0)
		ft_pwd();
	else if (ft_strcmp(cmds->cmd, "unset") == 0)
		ft_unset(env_list,cmds->args);
	else if (ft_strcmp(cmds->cmd, "exit") == 0)
		ft_exit(cmds->args, cmds);
	else
		handle_cmd(cmds, new_env);
}

void set_env(char **env, t_env **env_list)
{
	int i = 0;
	char **splited_env = NULL;
	char *pdw = NULL;

	pdw = getcwd(NULL, 0);
	if(env[0] == NULL)
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
		if(ft_strcmp(splited_env[0],"SHLVL") == 0)
			splited_env[1] = shlvl_increment(splited_env[1]);
		else if(ft_strcmp(splited_env[0],"OLDPWD") == 0)
			ft_lstadd_back(env_list, ft_lstnew("OLDPWD", NULL));
		else if(ft_strcmp(splited_env[0], "_") == 0)
			ft_lstadd_back(env_list, ft_lstnew("_", "/usr/bin/env"));
		else
			ft_lstadd_back(env_list, ft_lstnew(splited_env[0], splited_env[1]));
		i++;
	}
}

void execution(t_list **list, t_env **env_list, char **env)
{
    int i;
    int fd[2];
    pid_t pid;
    int prev_pipe = -1;
    t_here_doc *her_doc;

    i = 0;
    her_doc = NULL;
    (*list)->file_in = 0;
    (*list)->file_out = 1;
    set_here_doc(list, &her_doc);
    if ((*list)->nbr == 1)
    {
	if((*list)->cmd == NULL && (*list)->redir[0] == NULL)
		return;
        if ((*list)->redir[0] != NULL && (*list)->cmd == NULL)
		handle_redir_no_command(*list);
	else
            handle_one_cmd(*list, env_list, env, &her_doc);
    }
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
		handle_redir(list[i], &her_doc);
		if(list[i]->file_in < 0)
			exit(EXIT_FAILURE);
                if (i == 0)
                    dup2(list[i]->file_in, STDIN_FILENO);
                else
                {
		    if (list[i]->file_in == 0)
			dup2(prev_pipe, STDIN_FILENO);
		    else
		    	dup2(list[i]->file_in, STDIN_FILENO);
			 close(prev_pipe);
                }

                if (i != (*list)->nbr - 1)
                {
			if(list[i]->file_out == 1)
			{
				close(fd[0]);
		    		dup2(fd[1], STDOUT_FILENO);
			}
			else
				dup2(list[i]->file_out, STDOUT_FILENO);
			 close(fd[1]);
                }
		else
		{
			dup2(list[i]->file_out, STDOUT_FILENO);
			close(fd[1]);
		}
                if (list[i]->redir[0] != NULL && list[i]->cmd == NULL)
                {
                    handle_redir_no_command(*list);
                    exit(EXIT_SUCCESS);
                }
                else
                {
                    ft_builtins(list[i], env_list, env);
                    exit(EXIT_SUCCESS);
                }
            }
            else
            {
                if (i != 0)
                    close(prev_pipe);
                prev_pipe = fd[0];
                close(fd[1]);
            }
            if (i != (*list)->nbr - 1)
            {
		list[i + 1]->file_in = 0;
		list[i + 1]->file_out = 1;
            }
            i++;
        }
        while (wait(NULL) > 0)
            ;
    }
}
