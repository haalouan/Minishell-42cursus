/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_cmd1.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achater <achater@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/03 11:21:04 by achater           #+#    #+#             */
/*   Updated: 2024/08/03 11:25:58 by achater          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*find_path(char *cmd, char **envp)
{
	static int	i = 0;
	static int	x = -1;
	char		*path;
	char		**str;

	while (envp[i] && ft_strnstr(envp[i], "PATH", 4) == 0)
		i++;
	if (!envp[i])
		return (NULL);
	(1 == 1) && (str = ft_split(envp[i] + 5, ':'), i = -1);
	while (str[++i])
	{
		path = ft_strjoin3(str[i], "/", cmd);
		if (access(path, X_OK) >= 0)
		{
			x = i;
			break ;
		}
		free(path);
	}
	i = -1;
	ft_free(str);
	if (x < 0)
		return (NULL);
	return (path);
}

int	ft_strchr(char *str, char caractere)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == caractere)
			return (1);
		i++;
	}
	return (0);
}

void	handle_access(char **cmds, char **envp, char *cmd, char *path)
{
	if (access(cmd, X_OK) >= 0)
		execve(cmd, cmds, envp);
	else if (access(cmd, F_OK) >= 0)
	{
		if (ft_strchr(cmd, '/') == 0)
			if (execve(path, cmds, envp) < 0)
				error_handling(cmd, ": command not found", 20, 127);
		error_handling(cmd, ": Permission denied", 20, 126);
	}
}

void	handle_directory(char **cmds, char **envp, char *cmd, char *path)
{
	struct stat	sb;

	stat(cmd, &sb);
	if (S_ISDIR(sb.st_mode))
	{
		if (ft_strchr(cmd, '/') == 0)
			if (execve(path, cmds, envp) < 0)
				error_handling(cmd, ": command not found", 20, 127);
		error_handling(cmd, ": is a directory", 16, 126);
	}
}

void	execute(char **cmds, char **envp, char *cmd)
{
	char	*path;

	path = find_path(cmd, envp);
	handle_access(cmds, envp, cmd, path);
	handle_directory(cmds, envp, cmd, path);
	if (ft_strchr(cmd, '/') != 0)
		error_handling(cmd, ": No such file or directory", 28, 127);
	if (execve(path, cmds, envp) < 0)
	{
		if (cmd[0] == '.' && cmd[1] == '\0' )
		{
			write(2, "minishell: .: filename argument required\n", 41);
			write(2, ".: usage: . filename [arguments]\n", 33);
			exit(2);
		}
		error_handling(cmd, ": command not found", 20, 127);
	}
}
