/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achater <achater@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/17 11:49:08 by achater           #+#    #+#             */
/*   Updated: 2024/07/30 11:25:51 by achater          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	here_doc_child(int fd[2], int j, t_env *env_list, t_list *list)
{
	char	*line;

	close(fd[0]);
	setup_signal_handlers(sig_handler_child, SIG_IGN);
	while (1)
	{
		line = readline("> ");
		if (ft_strcmp(line, list->redir[j + 1]) == 0)
		{
			free(line);
			break ;
		}
		line = expand_in_here_doc(line, env_list,
				list->flag_here_doc);
		write(fd[1], line, ft_strlen(line));
		write(fd[1], "\n", 1);
		free(line);
	}
	close(fd[1]);
	exit(0);
}

int	here_doc_parent(int fd[2], int i, t_list **list, int pid)
{
	close(fd[1]);
	waitpid(pid, &g_status, 0);
	if (WIFEXITED(g_status))
	{
		if (WEXITSTATUS(g_status) == 1)
		{
			close(fd[0]);
			exit_status(1);
			return (1);
		}
	}
	list[i]->here_doc = fd[0];
	return (0);
}

int	here_doc_helper(int i, int j, t_env *env_list, t_list **list)
{
	int	fd[2];
	int	pid;

	ignore_signals();
	if (pipe(fd) == -1)
		error();
	pid = fork();
	if (pid == -1)
		error();
	if (pid == 0)
		here_doc_child(fd, j, env_list, list[i]);
	else
	{
		if (here_doc_parent(fd, i, list, pid) == 1)
			return (1);
	}
	return (0);
}

int	set_here_doc(t_list **list, int i, int j, t_env *env_list)
{
	int	prev;
	int	k;

	while (++i < (*list)->nbr)
	{
		k = 0;
		j = 0;
		prev = -1;
		while (list[i]->redir[j])
		{
			if (ft_strcmp(list[i]->redir[j], "<<") == 0)
			{
				if (k > 0 && prev != -1)
					close(prev);
				if (here_doc_helper(i, j, env_list, list) == 1)
					return (1);
				prev = list[i]->here_doc;
				k++;
			}
			j += 2;
		}
	}
	return (0);
}
