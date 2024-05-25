/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_cmd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achater <achater@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/01 17:29:29 by achater           #+#    #+#             */
/*   Updated: 2024/05/25 14:09:53 by achater          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	error(void)
{
	perror("Error");
	exit(EXIT_FAILURE);
}


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
	while (str[++i])
		free(str[i]);
	free(str);
	if (x < 0)
		return (NULL);
	return (path);
}

int	ft_strchr(char *str, char caractere)
{
	int i;

	i = 0;
	while(str[i])
	{
		if(str[i] == caractere)
			return (1);
		i++;
	}
	return (0);

}

void	execute(char **cmds, char **envp,char *cmd)
{
	// char	**cmds;
	char	*path;
	int		i;

	i = 0;
	if (access(cmd, X_OK) >= 0)
		execve(cmd, cmds, envp);
	if (ft_strchr(cmd, '/') != 0)
	{
		write(2, "minishell:", 10);
		write(2, cmd, ft_strlen(cmd));
		write(2, ": No such file or directory\n", 28);
		exit(127);
	}
	path = find_path(cmd, envp);
	if (execve(path, cmds, envp) < 0)
	{
		write(2, "minishell:", 10);
		write(2, cmd, ft_strlen(cmd));
		write(2, ": command not found\n", 20);
		exit(127);
	}
}

char	*ft_strjoin(char *s1,char *s2)
{
	char *s3;
	int i;
	int j;

	i = 0;
	j = 0;
	s3 = malloc(ft_strlen(s1) + ft_strlen(s2) + 1);
	if(s3 == NULL)
		return(NULL);
	if(s1 == NULL)
		return(s2);
	if(s2 == NULL)
		return(s1);
	while(s1[i])
	{
		s3[i] = s1[i];
		i++;
	}
	while(s2[j])
	{
		s3[i] = s2[j];
		i++;
		j++;
	}
	s3[i] = '\0';
	return(s3);
}

int	count_args0(char **args)
{
	int i;

	i = 0;
	while(args[i])
		i++;
	return (i);
}

char **cmds_whit_args(char *cmd, char **args)
{
	char **cmds;
	int i;

	i = 0;
	cmds = malloc(sizeof(char *) * (count_args0(args) + 2));
	if(cmds == NULL)
		return (NULL);
	cmds[0] = cmd;
	while(args[i])
	{
		cmds[i + 1] = args[i];
		i++;
	}
	cmds[i + 1] = NULL;
	return (cmds);
}

void	handle_cmd(t_list *cmds,char **env)
{
	char **args;

	if(cmds->args == NULL)
	{
		args = malloc(sizeof(char *) * 2);
		args[0] = cmds->cmd;
		args[1] = NULL;
	}
	else
		args = cmds_whit_args(cmds->cmd, cmds->args);
	execute(args, env,cmds->cmd);
}
