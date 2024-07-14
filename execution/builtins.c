/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achater <achater@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 11:28:38 by achater           #+#    #+#             */
/*   Updated: 2024/07/13 09:43:16 by achater          ###   ########.fr       */
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

void	close_here_doc(t_list **list)
{
	int	i;

	i = 0;
	while (i < (*list)->nbr)
	{
		 if (list[i]->here_doc > 2)
			close(list[i]->here_doc);
		i++;
	}
}

void	ft_builtins(t_list *cmds, t_env **env_list)
{
	char **new_env;

	new_env = struct_to_char(*env_list);
	if (ft_strcmp(cmds->cmd, "echo") == 0)
		ft_echo(cmds->args, 0, 0, 0);
	else if (ft_strcmp(cmds->cmd, "cd") == 0)
		ft_cd(cmds->args, *env_list);
	else if (ft_strcmp(cmds->cmd, "env") == 0 && cmds)
		ft_env(*env_list, cmds->args);
	else if (ft_strcmp(cmds->cmd, "export") == 0)
		ft_export(cmds->args, env_list);
	else if (ft_strcmp(cmds->cmd, "pwd") == 0
		|| ft_strcmp(cmds->cmd, "PWD") == 0)
		ft_pwd(*env_list);
	else if (ft_strcmp(cmds->cmd, "unset") == 0)
		ft_unset(env_list,cmds->args);
	else if (ft_strcmp(cmds->cmd, "exit") == 0)
		ft_exit(cmds->args, cmds);
	else
		handle_cmd(cmds, new_env);
	free_struct(new_env);
}

void	execution(t_list **list, t_env **env_list)
{
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
	handle_mult_cmd(list, env_list, -1,-1);
    close_here_doc(list);
}
