/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achater <achater@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/17 11:49:08 by achater           #+#    #+#             */
/*   Updated: 2024/05/19 16:20:29 by achater          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	set_here_doc(t_list **list, t_here_doc **here_doc)
{
	int i = 0;
	int j = 0;
	int k = 0;
	t_here_doc *node;
	t_here_doc *last_node = NULL;
	char *line;
	int pid;

	while(i < (*list)->nbr)
	{
		j = 0;
		while(list[i]->redir[j])
		{
			if(ft_strcmp(list[i]->redir[j], "<<") == 0)
			{
				pid = fork();
				if( pid == 0)
				{
					node = malloc(sizeof(t_here_doc));
					node->lines = malloc(sizeof(char *) * 100);
					k = 0;
					while(1)
					{
						line = readline("> ");
						if (ft_strcmp(line, list[i]->redir[j + 1]) == 0)
						{
							node->lines[k] = NULL;
							break;
						}
						node->lines[k] = ft_strdup(line);
						k++;
					}
					node->next = NULL;
					if (*here_doc == NULL)
						*here_doc = node;
					else
						last_node->next = node;
					last_node = node;
					// exit(0);
				}
				else
				{
					waitpid(pid, NULL, 0);
				}
			}
			j += 2;
		}
		i++;
	}
	// i = 0;
	// while(*here_doc)
	// {
	// 	j = 0;
	// 	while((*here_doc)->lines[j])
	// 	{
	// 		printf("%s\n", (*here_doc)->lines[j]);
	// 		j++;
	// 	}
	// 	*here_doc = (*here_doc)->next;
	// }
}
