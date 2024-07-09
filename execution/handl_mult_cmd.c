/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handl_mult_cmd.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achater <achater@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/09 12:25:01 by achater           #+#    #+#             */
/*   Updated: 2024/07/09 12:25:25 by achater          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	help_fct2(t_list **list,int fd[2], int pid[(*list)->nbr])
{
	int	status;
	int	i;

	close(fd[0]);
	i = -1;
	while (++i < (*list)->nbr)
		waitpid(pid[i], &status, 0);
	exit_status(WEXITSTATUS(status));
}

void	help_fct1(t_list **list, int i)
{
	list[i + 1]->file_in = 0;
	list[i + 1]->file_out = 1;
}

void	help_fct(t_list **list, int i, int prev_pipe)
{
	if (list[i]->file_in == 0)
		dup2(prev_pipe, STDIN_FILENO);
	else
		dup2(list[i]->file_in, STDIN_FILENO);
	close(prev_pipe);
}

void	child_of_mult_cmd(t_list **list, int i, int prev_pipe, int fd[2])
{
	handle_redir(list[i], 0);
	if (list[i]->file_in < 0 || list[i]->file_out < 0)
		exit(EXIT_FAILURE);
	if (i == 0)
		dup2(list[i]->file_in, STDIN_FILENO);
	else
		help_fct(list, i, prev_pipe);
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
}

void child_of_mult_cmd2(t_list **list, t_env **env_list, int i, int fd[2])
{
	if (list[i]->redir[0] != NULL && list[i]->cmd == NULL)
	{
	    handle_redir_no_command(*list, 0);
	    exit(EXIT_SUCCESS);
	}
	else
	{
		ft_builtins(list[i], env_list);
		exit(EXIT_SUCCESS);
	}
	if (list[i]->file_in != 0)
		close(list[i]->file_in);
	if (list[i]->file_out != 1)
		close(list[i]->file_out);
	close(fd[0]);
	close(fd[1]);
}

void	handle_mult_cmd(t_list **list, t_env **env_list, int i, int prev_pipe)
{
	int	fd[2];
	int	pid[(*list)->nbr + 1];

	 while (++i < (*list)->nbr)
        {
        	if (pipe(fd) == -1)
        		error();
        	pid[i] = fork();
        	if (pid[i] == -1)
        		error();
        	if (pid[i] == 0)
		{
			child_of_mult_cmd(list, i, prev_pipe, fd);
			child_of_mult_cmd2(list, env_list, i, fd);
		}
            	else
            	{
                	close(prev_pipe);
			close(fd[1]);
                	prev_pipe = fd[0];
        	}
         	if (i != (*list)->nbr - 1)
			help_fct1(list, i);
        }
	help_fct2(list, fd, pid);
}