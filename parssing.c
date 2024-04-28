/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parssing.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haalouan <haalouan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/26 16:38:45 by haalouan          #+#    #+#             */
/*   Updated: 2024/04/28 01:02:19 by haalouan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

int count_quote(char *line, int len)
{
    int count = 0;
    while (*line && len > 0)
    {
        if (*line == '\"' || *line == '\'')
            count++;
        line++;
        len--;
    }
    return count;
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
            if (is_character(*line) == 0)
                break;
        }
        else if (line[i] == '\"')
        {
            i++;
            while (line[i] != '\"' && line[i] != '\0')
                i++;
            if (line[i] == '\"')
                i++;
            printf("%c\n", line[i]);
            if (is_character(line[i]) == 0)
                break;
        }
        else
            break;
    }
    *le += i;
    int j = count_quote(line, i);
    // printf("len = %d\n", i - j);
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


char **parssing(char *line)
{
    int count = count_cmds(line);
    printf("-------------------\n");
    printf("nbr of cmds -> %d\n", count);
    printf("-------------------\n");
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