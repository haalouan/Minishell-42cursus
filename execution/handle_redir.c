/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_redir.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achater <achater@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/09 14:34:20 by achater           #+#    #+#             */
/*   Updated: 2024/07/05 12:07:59 by achater          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	redir_helper(t_list *list, int i, int x)
{
	if (x == 1 || x == 2)
	{
		if (x == 1)
			list->file_out = open(list->redir[i + 1],
					O_WRONLY | O_CREAT | O_TRUNC, 0644);
		if (x == 2)
			list->file_out = open(list->redir[i + 1],
					O_WRONLY | O_CREAT | O_APPEND, 0644);
		if (list->file_out < 0)
		{
			printf("minishell: %s Permission denied", list->redir[i + 1]);
			return (1);
		}
	}
	if (x == 3)
	{
		list->file_in = open(list->redir[i + 1], O_RDONLY);
		if (list->file_in < 0)
		{
			printf("%s:No such file or directory\n", list->redir[i + 1]);
			return (1);
		}
	}
	return (0);
}

void	handle_redir_no_command(t_list *list, int i)
{
	while (list->redir[i])
	{
		if (ft_strcmp(list->redir[i], ">") == 0)
		{
			if (redir_helper(list, i, 1) == 1)
				return ;
			close(list->file_out);
		}
		else if (ft_strcmp(list->redir[i], ">>") == 0)
		{
			if (redir_helper(list, i, 2) == 1)
				return ;
			close(list->file_out);
		}
		else if (ft_strcmp(list->redir[i], "<") == 0)
		{
			if (redir_helper(list, i, 3) == 1)
				return ;
			close(list->file_in);
		}
		i += 2;
	}
}

void	handle_redir(t_list *list, int i)
{
	if (list->redir == NULL)
		return ;
	while (list->redir[i])
	{
		if (ft_strcmp(list->redir[i], ">") == 0)
		{
			if (redir_helper(list, i, 1) == 1)
				return ;
		}
		else if (ft_strcmp(list->redir[i], ">>") == 0)
		{
			if (redir_helper(list, i, 2) == 1)
				return ;
		}
		else if (ft_strcmp(list->redir[i], "<") == 0)
		{
			if (redir_helper(list, i, 3) == 1)
				return ;
		}
		else if (ft_strcmp(list->redir[i], "<<") == 0)
			list->file_in = list->here_doc;
		i += 2;
	}
}
