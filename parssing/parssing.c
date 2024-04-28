/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parssing.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haalouan <haalouan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/26 16:38:45 by haalouan          #+#    #+#             */
/*   Updated: 2024/04/28 18:34:02 by haalouan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"


void remove_quotes(t_list** list)
{
    int i = 0;
    int k;
    int l;
    while (list[i])
    {
        k = 0;
        int j = 0;
        while (list[i]->cmd && list[i]->cmd[j] != '\0')
        {
            if (list[i]->cmd[j] != '\'' && list[i]->cmd[j] != '"')
            {
                list[i]->cmd[k] = list[i]->cmd[j];
                k++;
                j++;
            }
            else
                j++;
        }
        if (list[i]->cmd)
            list[i]->cmd[k] = '\0';
        k = 0;
        j = 0;
        while (list[i]->redir && list[i]->redir[j] != '\0')
        {
            if (list[i]->redir[j] != '\'' && list[i]->redir[j] != '"')
            {
                list[i]->redir[k] = list[i]->redir[j];
                k++;
                j++;
            }
            else
                j++;
        }
        if (list[i]->redir)
            list[i]->redir[k] = '\0';
        k = 0;
        j = 0;
        l = 0;
        while (list[i]->args && list[i]->args[l])
        {
            k = 0;
            j = 0;
            while (list[i]->args && list[i]->args[l] && list[i]->args[l][j] != '\0')
            {
                if (list[i]->args[l][j] != '\'' && list[i]->args[l][j] != '"')
                {
                    list[i]->args[l][k] = list[i]->args[l][j];
                    k++;
                    j++;
                }
                else
                    j++;
            }
            if (list[i]->args)
                list[i]->args[l][k] = '\0';
            l++;
        }
        i++;
    }
    i = 0;
}


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
    // int j = count_quote(line, i);
    add_tab(line , tab, i);
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
    int count = count_lists(line);
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
    count = count_lists(line);
    size = count_pipe(tab, count);
    list = (t_list **)malloc(sizeof(t_list *) * (size + 1) + 1);
    if (!list)
        exit(1);
    continue_parssing(list, tab, line);
    if (check_tab(list) == 1)
    {
        handele_error();
        return NULL;
    }
    remove_quotes(list);
    print_tab(tab, line, list);
    return list;
}