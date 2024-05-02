/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parssing1.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haalouan <haalouan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/26 16:38:45 by haalouan          #+#    #+#             */
/*   Updated: 2024/05/02 01:32:54 by haalouan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"


void add_tab(char *line, char **tab, int len)
{
    int i = 0;
    if (!tab)
        exit(0);
    while (tab[i] != NULL)
        i++;
    tab[i] = malloc(len + 1);
    if (!tab[i])
        exit(0);
    ft_strncpy(tab[i], line, len);
}


char **handele_parssing(char *line)
{
    int count = count_cmds(line);
    // printf("*-------------------------*\n");
    // printf("|   nbr of cmds -> [%d]    |\n", count);
    // printf("*-------------------------*\n");
    // return NULL;
    // exit(0);
    t_check check;
    int i = 0;
    char **tab = malloc(sizeof(char *) * (count + 1) + 1);
    if (!tab)
        exit(EXIT_FAILURE);
    while (i <= count)
    {
        tab[i] = NULL;
        i++;
    }
    while (*line != '\0')
    {
        check_init(&check);
        check_check(line, &check);
        handele_line(&line, tab, check);
    }
    return tab;
}

t_list **parssing(char *line, t_env *env_list)
{
    char **tab;
    t_list **list;

    tab = NULL;
    list = NULL;
    if (ft_strlen(line) == 0)
        return NULL;
    add_history(line);
    if (count_quote(line) == 1)
        return NULL;
    tab = handele_parssing(line);
    if (check_error(tab) == 1)
        return NULL;
    list = (t_list **)malloc(sizeof(t_list *) * (count_pipe(tab, count_cmds(line)) + 1) + 1);
    if (!list)
        exit(EXIT_FAILURE);
    continue_parssing(list, tab, line, env_list);
    if (check_tab(list) == 1)
        return NULL;
    remove_quotes(list);
    print_tab(tab, line, list);
    return list;
}