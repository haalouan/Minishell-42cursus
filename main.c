/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haalouan <haalouan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/26 16:35:11 by haalouan          #+#    #+#             */
/*   Updated: 2024/04/27 10:50:20 by haalouan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int main()
{
    char *line = NULL;
    char **tab = NULL;
    while (1)
    {
        line = readline("=>  "ANSI_COLOR_YELLOW  "minishell => "   ANSI_RESET_ALL "");
        if (line)
        {
            if (ft_strlen(line) == 0)
                continue;
            add_history(line);
            check_errors(line);
            if (count_quote(line, ft_strlen(line)) % 2 != 0)
            {
                handele_error();
                continue;
            }
            tab = parssing(line);
            check_tab(tab, line);
            print_tab(tab, line);
        }
    }
}

void print_tab(char **tab, char *line)
{
    int i = 0;
    if (!tab)
        return ;
    while (i < count_cmds(line))
    {
        printf("*******************\n");
        printf(""ANSI_COLOR_GREEN  "      %s\n" ANSI_RESET_ALL "", tab[i]);
        i++;
    }
}