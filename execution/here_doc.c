/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haalouan <haalouan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/17 11:49:08 by achater           #+#    #+#             */
/*   Updated: 2024/06/24 14:35:09 by haalouan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	set_here_doc(t_list **list, t_env *env_list)
{
	int i;
	int j;
	int fd[2];
	char *line;

	i = 0;
	while(i < (*list)->nbr)
	{
		j = 0;
		while(list[i]->redir[j])
		{
			if(ft_strcmp(list[i]->redir[j], "<<") == 0)
			{
				if(pipe(fd) == -1)
				{
					perror("pipe");
					exit(1);
				}
				while(1)
				{
					line = readline("> ");
					if (ft_strcmp(line, list[i]->redir[j + 1]) == 0)
					{
						free(line);
						break;
					}
					line = expand_in_here_doc(line, env_list, list[i]->flag_here_doc);
					write(fd[1], line, ft_strlen(line));
					write(fd[1], "\n", 1);
					free(line);
				}
				close(fd[1]);
				list[i]->here_doc = fd[0];
			}
			j += 2;
		}
		i++;
	}
}

