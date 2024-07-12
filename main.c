/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haalouan <haalouan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/26 16:35:11 by haalouan          #+#    #+#             */
/*   Updated: 2024/07/12 14:18:14 by haalouan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void f()
{
    system("leaks minishell");
}

int main(int arc, char **arv, char **env)
{
    // atexit(f);
    (void)arc;
    (void)arv;
    char *line;
    t_list **list;
    t_env *env_list;

    line = NULL;
    list = NULL;
    env_list = NULL;
    g_status = 0;
    set_env(env, &env_list, 0);
    signal(SIGINT, signal_handler);
    signal(SIGQUIT, signal_handler);
    rl_catch_signals = 0;
    while (1337)
    {
        g_status = 0;
        line = readline("=>  "ANSI_COLOR_YELLOW  "minishell => "   ANSI_RESET_ALL "");
        if (line)
        {
            list = parssing(line, env_list);
            add_history(line);
            if (!list)
                continue;
            execution(list, &env_list);
        }
        if (!line)
        {
            free_list(list);
            // freee_list(&env_list);
            exit(1);
        }
    }
    free_list(list);
    // free(line);
}
