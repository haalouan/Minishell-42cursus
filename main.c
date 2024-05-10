/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haalouan <haalouan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/26 16:35:11 by haalouan          #+#    #+#             */
/*   Updated: 2024/05/09 21:48:53 by haalouan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int main(int arc, char **arv, char **env)
{
    (void)arc;
    (void)arv;
    char *line;
    t_list **list;
    t_env *env_list;

    line = NULL;
    list = NULL;
    env_list = NULL;
    set_env(env, &env_list);
    dup2(3, 0);
	dup2(4, 1);
    while (42)
    {
        line = readline("=>  "ANSI_COLOR_YELLOW  "minishell => "   ANSI_RESET_ALL "");
        if (line)
        {
            //parssing
            list = parssing(line, env_list);
            if (!list)
                continue;
            //execution
            execution(list, env_list, env);
            dup2(0, 3);
			dup2(1, 4);
        }
    }
}
