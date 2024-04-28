/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haalouan <haalouan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/26 16:35:11 by haalouan          #+#    #+#             */
/*   Updated: 2024/04/28 16:57:40 by haalouan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int main(int arc, char **arv, char **env)
{
    (void)arc;
    (void)arv;
    char *line;
    t_list **list;

    line = NULL;
    list = NULL;
    while (42)
    {
        line = readline("=>  "ANSI_COLOR_YELLOW  "minishell => "   ANSI_RESET_ALL "");
        if (line)
        {
            //parssing
            list = parssing(line);
            if (!list)
                continue;
            //execution
            execution(list,env);
        }
    }
}
