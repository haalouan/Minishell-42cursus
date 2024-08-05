/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handl_one_cmd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achater <achater@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 11:15:20 by achater           #+#    #+#             */
/*   Updated: 2024/08/02 10:56:14 by achater          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	**free_struct(char **new_env)
{
	int	i;

	i = 0;
	while (new_env[i])
	{
		free(new_env[i]);
		i++;
	}
	free(new_env);
	return (NULL);
}

int	check_builtins(char *cmd)
{
	if (ft_strcmp(cmd, "echo") == 0)
		return (1);
	if (ft_strcmp(cmd, "cd") == 0)
		return (1);
	if (ft_strcmp(cmd, "env") == 0)
		return (1);
	if (ft_strcmp(cmd, "export") == 0)
		return (1);
	if (ft_strcmp(cmd, "pwd") == 0 || ft_strcmp(cmd, "PWD") == 0)
		return (1);
	if (ft_strcmp(cmd, "unset") == 0)
		return (1);
	if (ft_strcmp(cmd, "exit") == 0)
		return (1);
	return (0);
}

void	non_builtins(t_list *cmds, char **new_env, int status, int pid)
{
	ignore_signals();
	pid = fork();
	if (pid < 0)
	{
		perror("fork");
		free_struct(new_env);
		return ;
	}
	if (pid == 0)
	{
		setup_signal_handlers(sig_handler_child, sig_handler_child);
		dup2(cmds->file_in, STDIN_FILENO);
		dup2(cmds->file_out, STDOUT_FILENO);
		handle_cmd(cmds, new_env);
	}
	else
	{
		if (cmds->file_in != 0)
			close(cmds->file_in);
		if (cmds->file_out != 1)
			close(cmds->file_out);
		exit_helper(cmds, status);
	}
	free_struct(new_env);
}

int	fct_helper(t_list *cmds, t_env **env_list)
{
	if (ft_strcmp(cmds->cmd, "cd") == 0)
		ft_cd(cmds->args, *env_list);
	else if (ft_strcmp(cmds->cmd, "unset") == 0)
		ft_unset(env_list, cmds->args);
	else if (ft_strcmp(cmds->cmd, "exit") == 0)
		ft_exit(cmds->args, cmds, 0, 0);
	else if (ft_strcmp(cmds->cmd, "export") == 0)
		ft_export(cmds->args, env_list);
	else if (ft_strcmp(cmds->cmd, "env") == 0 && cmds)
		ft_env(*env_list, cmds->args);
	else if (ft_strcmp(cmds->cmd, "pwd") == 0
		|| ft_strcmp(cmds->cmd, "PWD") == 0)
		ft_pwd(*env_list);
	else if (ft_strcmp(cmds->cmd, "echo") == 0)
		ft_echo(cmds->args, 0, 0, 0);
	else
		return (0);
	return (1);
}

void	handle_one_cmd(t_list *cmds, t_env **env_list, int status)
{
	int		pid;
	char	**new_env;
	int		in;
	int		out;

	pid = 0;
	new_env = struct_to_char(*env_list);
	handle_redir(cmds, 0, 0);
	if (cmds->file_in < 0 || cmds->file_out < 0)
	{
		(cmds->file_in != 0) && (close(cmds->file_in));
		(cmds->file_out != 1) && (close(cmds->file_out));
		return ((void)free_struct(new_env));
	}
	if (check_builtins(cmds->cmd) == 1)
	{
		(1) && (in = dup(STDIN_FILENO), out = dup(STDOUT_FILENO));
		(1) && (dup2(cmds->file_in, 0), dup2(cmds->file_out, 1));
		fct_helper(cmds, env_list);
		(1) && (close(cmds->file_in), close(cmds->file_out));
		(1) && (dup2(in, 0), dup2(out, 1), close(in), close(out));
		free_struct(new_env);
		return ;
	}
	non_builtins(cmds, new_env, status, pid);
}
