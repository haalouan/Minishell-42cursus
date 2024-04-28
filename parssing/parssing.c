/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parssing.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haalouan <haalouan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/26 16:38:45 by haalouan          #+#    #+#             */
/*   Updated: 2024/04/28 13:50:07 by haalouan         ###   ########.fr       */
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

void handele_word(char **le, char **tab)
{
    int i;
    char *line = *le;
    // (void)tab;
    i = 0;
    while (line[i] != '\0')
    {
        while (is_character(line[i]) == 1 && line[i] != '\0')
            i++;
        if (line[i] == '\'')
        {
            i++;
            while (line[i] != '\'' && line[i] != '\0')
                i++;
            if (line[i] == '\'')
                i++;
            if (is_character(*line) == 0 && *line != '\'' && *line != '\"')
                break;
        }
        else if (line[i] == '\"')
        {
            i++;
            while (line[i] != '\"' && line[i] != '\0')
                i++;
            if (line[i] == '\"')
                i++;
            if (is_character(line[i]) == 0 && *line != '\'' && *line != '\"')
                break;
        }
        else
            break;
    }
    *le += i;
    int j = count_quote(line, i);
    add_tab(line , tab, i - j);
}

void handele_line(char **line, char **tab, t_check check)
{
    if (check.find_here_doc == 1)
    {
        add_tab(*line, tab, 2);
        *line += 2;
    }
    else if (check.find_append_op == 1)
    {
        add_tab(*line, tab, 2);
        *line += 2;
    }
    else if (check.find_pipe == 1)
    {
        add_tab(*line ,tab, 1);
        *line += 1;
    }
    else if (check.find_in_re == 1)
    {
        add_tab(*line, tab, 1);
        *line += 1;
    }
    else if (check.find_out_re == 1)
    {
        add_tab(*line, tab, 1);
        *line += 1;
    }
    else if (check.find_word == 1)
        handele_word(line, tab);
    else if (*line)
        *line += 1;
}


char **handele_parssing(char *line)
{
    int count = count_cmds(line);
    printf("*-------------------------*\n");
    printf("|   nbr of cmds -> [%d]    |\n", count);
    printf("*-------------------------*\n");
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


t_list **parssing(char *line)
{
    char **tab = NULL;
    t_list **list = NULL;
    int count = 0;
    int size = 0;

    if (ft_strlen(line) == 0)
        return NULL;
    add_history(line);
    if (count_quote(line, ft_strlen(line)) == 1)
    {
        handele_error();
        return NULL;
    }
    tab = handele_parssing(line);
    if (check_tab(tab, line) == 1)
    {
        handele_error();
        return NULL;
    }
    count = count_cmds(line);
    size = count_pipe(tab, count);
    list = (t_list **)malloc(sizeof(t_list *) * (size + 1) + 1);
    if (!list)
        exit(1);
    continue_parssing(list, tab, line);
    print_tab(tab, line, list);
    return list;
}