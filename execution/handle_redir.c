/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_redir.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achater <achater@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/09 14:34:20 by achater           #+#    #+#             */
/*   Updated: 2024/05/10 20:03:57 by achater          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	handle_redir_no_command(t_list *list)
{
	int	i;
	int	fd;

	i = 0;
	while(list->redir[i])
	{
		if(ft_strcmp(list->redir[i], ">") == 0)
		{
			fd = open(list->redir[i + 1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
			if (fd < 0)
				perror("Error");
			else
				close(fd);
		}
		else if(ft_strcmp(list->redir[i], ">>") == 0)
		{
			fd = open(list->redir[i + 1], O_WRONLY | O_CREAT | O_APPEND, 0644);
			if (fd < 0)
				perror("Error");
			else
				close(fd);
		}
		else if(ft_strcmp(list->redir[i], "<") == 0)
		{
			fd = open(list->redir[i + 1], O_RDONLY);
			if (fd < 0)
				perror("Error");
			else
				close(fd);
		}
		i += 2;
	}
}
void	handle_redir(t_list *list)
{
	int i;

	i = 0;
	while(list->redir[i])
	{
		if(ft_strcmp(list->redir[i], ">") == 0)
		{
			list->file_out = open(list->redir[i + 1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
			if (list->file_out < 0)
			{
				perror("Error");
				break;
			}
			dup2(list->file_out, 1);
		}
		else if(ft_strcmp(list->redir[i], ">>") == 0)
		{
			list->file_out = open(list->redir[i + 1], O_WRONLY | O_CREAT | O_APPEND, 0644);
			if (list->file_out < 0)
			{
				perror("Error");
				break;
			}
		}
		else if(ft_strcmp(list->redir[i], "<") == 0)
		{
			list->file_in = open(list->redir[i + 1], O_RDONLY);
			if (list->file_in < 0)
			{
				perror("Error");
				break;
			}
		}
	}
}
