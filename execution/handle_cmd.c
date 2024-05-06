/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_cmd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achater <achater@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/01 17:29:29 by achater           #+#    #+#             */
/*   Updated: 2024/05/05 16:28:21 by achater          ###   ########.fr       */
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

	while (ft_strnstr(envp[i], "PATH", 4) == 0)
		i++;
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

void	execute(char *argv, char **envp)
{
	char	**cmds;
	char	*path;
	int		i;

	i = 0;
	cmds = ft_split(argv, ' ');
	if (access(cmds[0], X_OK) >= 0)
		execve(cmds[0], cmds, NULL);
	path = find_path(cmds[0], envp);
	if (!path)
	{
		while (cmds[i])
		{
			free(cmds[i]);
			i++;
		}
		free(cmds);
	}
	if (execve(path, cmds, envp) < 0)
		error();
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

char	*arg_to_str(char **args, char *cmd)
{
	char *arg;
	int i;

	i = 0;
	arg = ft_strjoin(cmd, NULL);
	if(args == NULL)
		return(arg);
	while(args[i])
	{
		arg = ft_strjoin(arg, " ");
		arg = ft_strjoin(arg, args[i]);
		i++;
	}
	return(arg);
}

void	handle_cmd(t_list *cmds,char **env)
{
	char *arg;
	arg = arg_to_str(cmds->args,cmds->cmd);
	execute(arg, env);
}
