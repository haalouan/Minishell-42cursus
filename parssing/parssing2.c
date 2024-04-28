/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parssing2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achater <achater@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/27 11:05:44 by haalouan          #+#    #+#             */
/*   Updated: 2024/04/28 15:38:53 by achater          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int count_pipe(char **tab, int len)
{
    int i = 0;
    int count = 0;
    while (i < len)
    {
        if (tab[i][0] == '|')
            count++;
        i++;
    }
    return count + 1;
}

int finnd_pipe(char **tab, int count)
{
    int i = 0;
    int check = 0;
    while (i < count && tab[i])
    {
        if (tab[i] && tab[i][0] == '|')
        {
            check = 1;
            break;
        }
        i++;
    }
    if (check == 0)
        return 0;
    return i + 1;
}


int find_redir(char **tab, int count)
{
    int i = 0;
    while (i < count)
    {
        if (tab[i][0] == '<')
            break;
        i++;
    }
    return i;
}

void continue_parssing(t_list **list, char **tab, char *line)
{
    int count = count_lists(line);
    int size = count_pipe(tab, count);
    int i = 0;
    while (i <= size)
    {
        list[i] = NULL;
        i++;
    }
    int pipe = 0;
    int k = 0;
    i = 0;
    int next_pipe = 0;
    while (k < size)
    {
        next_pipe = finnd_pipe(tab, count);
        list[k] = malloc(sizeof(t_list) + 1);
        if (!list)
            exit(EXIT_FAILURE);
        list[k]->cmd = NULL;
        list[k]->redir = NULL;
        list[k]->args = NULL;
        if (tab[pipe] && tab[pipe][0] != '>' && tab[pipe][0] != '<')
        {
            list[k]->cmd = malloc(ft_strlen(tab[pipe]) + 1);
            if (!list[k]->cmd)
                exit(EXIT_FAILURE);
            ft_strncpy(list[k]->cmd, tab[pipe], ft_strlen(tab[pipe]));
        }
        else
            pipe = pipe - 1;
        int save = pipe + 1;
        int ct = 0;
        while (save < count && tab[save])
        {
            if (tab[save][0] == '>' || tab[save][0] == '<' || tab[save][0] == '|' || !tab[save])
                break;
            ct++;
            save++;
        }
        save = pipe + 1;

        if (ct != 0 && tab[save] != NULL)
        {
        //args
                list[k]->args = (char **)malloc(sizeof(char *) * (ct + 1) + 1);
                if (!list[k]->args)
                    exit(EXIT_FAILURE);
                i = 0;
                while (i <= ct)
                {
                    list[k]->args[i] = NULL;
                    i++;
                }
                i = 0;
                while (i < ct)
                {
                    if (tab[save] == NULL || tab[save][0] == '|')
                        break;
                    list[k]->args[i] = malloc(ft_strlen(tab[save]) + 1);
                    if (!list[k]->args[i])
                        exit(EXIT_FAILURE);
                    ft_strncpy(list[k]->args[i], tab[save], ft_strlen(tab[save]));
                    save++;
                    i++;
                }
        }
        if (tab[save] && (tab[save][0] == '<' || tab[save][0] == '>'))
        {
            int hsseb = 0;
                    i = save;
                    hsseb = 0;
                    ct = 0;
                    while (i < count)
                    {
                        int j = 0;
                        if (tab[i][0] == '|')
                            break;
                        while (tab[i][j++] != '\0')
                            hsseb++;
                        i++;
                        ct++;
                        if (!tab[i])
                            break;
                    }
                    list[k]->redir = malloc(hsseb + 1);
                    if (!list[k]->redir)
                        exit(EXIT_FAILURE);
                    i = 0;
                    while (i < hsseb)
                    {
                        list[k]->redir[i] = 0;
                        i++;
                    }
                    i = 0;
                    while (i < ct)
                    {
                        if (tab[save][0] == '|')
                            break;
                        ft_strcat(list[k]->redir, tab[save]);
                        i++;
                        save++;
                    }
        }
        // pipe = next_pipe;
        tab = tab + next_pipe;
        k++;

    }
    // print_tab(tab, line, list);
}
