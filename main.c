/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haalouan <haalouan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/26 16:35:11 by haalouan          #+#    #+#             */
/*   Updated: 2024/04/28 02:03:42 by haalouan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int main()
{
    char *line = NULL;
    char **tab = NULL;
    t_list **list = NULL;
    int count = 0;
    int size;
    
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
            count = count_cmds(line);
            size = count_pipe(tab, count);
            list = (t_list **)malloc(sizeof(t_list *) * (size + 1) + 1);
            if (!list)
                exit(1);
            int i = 0;
            while (i <= size)
            {
                list[i] = NULL;
                i++;
            }
            continue_parssing(list, tab, line);
            print_tab(tab, line, list);
        }
    }
}

void print_tab(char **tab, char *line, t_list **list)
{
    int i = 0;
    (void)tab;
    (void)line;
    // if (!tab)
    //     return ;
    // while (i < count_cmds(line))
    // {
    //     printf(""ANSI_COLOR_GREEN  "      %s\n" ANSI_RESET_ALL "", tab[i]);
    //     printf("-------------------\n");
    //     i++;
    // }
    if (!list)
    {
        printf("ji\n");
        return ;
    }
    i = 0;
    while (list[i] != NULL)
    {
        printf("     (%d)\n", i + 1);
        printf("CMD : %s\n", list[i]->cmd);
        int n = 0;
        if (!list[i]->args)
            printf("ARG : (null)\n");
        while (list[i]->args && list[i]->args[n] != NULL)
        {
            printf("ARG : %s\n", list[i]->args[n]);
            n++;
        }
        printf("RED : %s\n", list[i]->redir);
        printf("-------------------\n");
        i++;
    }
}