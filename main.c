/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haalouan <haalouan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/26 16:35:11 by haalouan          #+#    #+#             */
/*   Updated: 2024/07/20 16:29:00 by haalouan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	main_loop(char *line, t_env *env_list, t_list **list)
{
	while (1337)
	{
		g_status = 0;
		line = readline("=> "ANSI_COLOR_YELLOW
				"minishell => " ANSI_RESET_ALL "");
		if (line)
		{
			list = parssing(line, env_list);
			add_history(line);
			if (!list)
				continue ;
			execution(list, &env_list);
		}
		if (!line)
		{
			free(line);
			exit(1);
		}
		free_list(list);
		free(line);
	}
}

int	main(int arc, char **arv, char **env)
{
	char	*line;
	t_list	**list;
	t_env	*env_list;

	line = NULL;
	list = NULL;
	env_list = NULL;
	(void)arc;
	(void)arv;
	set_env(env, &env_list, -1);
	signal(SIGINT, signal_handler);
	signal(SIGQUIT, signal_handler);
	rl_catch_signals = 0;
	main_loop(line, env_list, list);
}
