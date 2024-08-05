/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handl_mult_cmd1.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achater <achater@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/21 11:04:48 by achater           #+#    #+#             */
/*   Updated: 2024/08/02 15:37:32 by achater          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	help_fct2(t_list **list, int fd[2], int pid[(*list)->nbr])
{
	int	status;
	int	i;

	close(fd[0]);
	i = -1;
	while (++i < (*list)->nbr)
	{
		waitpid(pid[i], &status, 0);
	}
	if (WIFSIGNALED(status))
		exit_status(128 + WTERMSIG(status));
	else
		exit_status(WEXITSTATUS(status));
	free(pid);
}

void	exit_helper(t_list *cmds, int status)
{
	wait(&status);
	if (check_builtins(cmds->cmd) == 0)
	{
		if (WIFSIGNALED(status))
			exit_status(128 + WTERMSIG(status));
		else
			exit_status(WEXITSTATUS(status));
	}
}

void	fork_error(int *x, int i, int *pid, int *fd)
{
	int	j;

	j = 0;
	close(fd[0]);
	close(fd[1]);
	if (*x == 0)
		perror("fork");
	(*x)++;
	while (j < i)
		kill(pid[j++], SIGKILL);
}
