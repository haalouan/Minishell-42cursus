/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_cmd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achater <achater@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/01 17:29:29 by achater           #+#    #+#             */
/*   Updated: 2024/08/03 11:24:52 by achater          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	**cmds_whit_args(char *cmd, char **args)
{
	char	**cmds;
	int		i;

	i = 0;
	cmds = malloc(sizeof(char *) * (count_args0(args) + 2));
	if (cmds == NULL)
		return (NULL);
	cmds[0] = cmd;
	while (args[i])
	{
		cmds[i + 1] = args[i];
		i++;
	}
	cmds[i + 1] = NULL;
	return (cmds);
}

void	handle_cmd(t_list *cmds, char **env)
{
	char	**args;

	if (cmds->args == NULL)
	{
		args = malloc(sizeof(char *) * 2);
		args[0] = cmds->cmd;
		args[1] = NULL;
	}
	else
		args = cmds_whit_args(cmds->cmd, cmds->args);
	execute(args, env, cmds->cmd);
}
