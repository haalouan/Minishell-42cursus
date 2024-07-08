/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achater <achater@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 11:28:38 by achater           #+#    #+#             */
/*   Updated: 2024/07/07 13:35:45 by achater          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int exit_status(int status)
{
	static int var;

	if (status != -1)
		var = status;
	return (var);
}

void	close_here_doc(t_list **list, int i)
{
	while (++i < (*list)->nbr)
	{
		close(list[i]->here_doc);
	}
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
		ft_pwd(*env_list);
	else if (ft_strcmp(cmds->cmd, "unset") == 0)
		ft_unset(env_list,cmds->args);
	else if (ft_strcmp(cmds->cmd, "exit") == 0)
		ft_exit(cmds->args, cmds);
	else
		handle_cmd(cmds, new_env);
	free(new_env);
}

void	execution(t_list **list, t_env **env_list, char **env)
{
    int	i;
    int	fd[2];
    pid_t *pid = malloc(sizeof(pid_t) * (*list)->nbr);
    int prev_pipe = -1;
    int status;

    i = 0;
    (*list)->file_in = 0;
    (*list)->file_out = 1;
    change_env_last_cmd(*list, env_list);
    set_here_doc(list, -1, 0, *env_list);
    if ((*list)->nbr == 1)
    {
	if((*list)->cmd == NULL && (*list)->redir[0] == NULL)
		return ;
        if ((*list)->redir[0] != NULL && (*list)->cmd == NULL)
		handle_redir_no_command(*list, 0);
	else
            handle_one_cmd(*list, env_list, 0);
    }
    else
    {
        while (i < (*list)->nbr)
        {
        	if (pipe(fd) == -1)
        		error();
        	pid[i] = fork();
        	if (pid[i] == -1)
        		error();
        	if (pid[i] == 0)
            	{
			handle_redir(list[i], 0);
			if (list[i]->file_in < 0)
				exit(EXIT_FAILURE);
			if (list[i]->file_out < 0)
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
				if (list[i]->file_out == 1)
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
                	    handle_redir_no_command(*list, 0);
                	    exit(EXIT_SUCCESS);
                	}
                	else
                	{
                		ft_builtins(list[i], env_list, env);
                		exit(EXIT_SUCCESS);
                	}
			if (list[i]->file_in != 0)
				close(list[i]->file_in);
			if (list[i]->file_out != 1)
				close(list[i]->file_out);
			close(fd[0]);
			close(fd[1]);
            	}
            	else
            	{
                	close(prev_pipe);
			close(fd[1]);
                	prev_pipe = fd[0];
        	}
         	if (i != (*list)->nbr - 1)
        	{
			list[i + 1]->file_in = 0;
			list[i + 1]->file_out = 1;
        	}
        	i++;
        }
	close(fd[0]);
	i = -1;
	while (++i < (*list)->nbr)
		waitpid(pid[i], &status, 0);
	exit_status(WEXITSTATUS(status));
    }
    close_here_doc(list, -1);
}
