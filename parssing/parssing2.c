/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parssing2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haalouan <haalouan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/27 11:05:44 by haalouan          #+#    #+#             */
/*   Updated: 2024/05/11 17:08:06 by haalouan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

//ba9a mamgadach hh


int count_redir(char **tab, int i)
{
    int count;

    count = 0;
    while (tab && tab[i] && tab[i][0] && tab[i][0] != '|')
    {
        if (tab[i] && (tab[i][0] == '>' || tab[i][0] == '<'))
            count++;
        i++;
    }
    return count * 2;
}

int count_args(char **tab, int i)
{
    int count;

    count = 0;
    if (!tab)
        return 0;
    while (tab && tab[i])
    {
        if (tab[i][0] == '|')
            break;
        if ((tab[i][0] == '>' || tab[i][0] == '<'))
            i += 2;
        else
        {
            i++;
            count++;
        }
    }
    return count;
    
}

void args(t_list **list, char **tab, int k, int ii)
{
    int count;
    int i;

    i = 0;
    count = count_args(tab , ii);
    if (count == 0)
        return;
    if (!list[k]->cmd)
        count--;
    if (count == 0)
        return;
    list[k]->args = (char **)malloc(sizeof(char *) * (count + 1) + 1);
    if (!list[k]->args)
        exit(EXIT_FAILURE);
    while (i++ < count)
        list[k]->args[i] = NULL;
    i = 0;
    while (i < count)
    {
        while (tab[ii] && tab[ii][0] && is_character2(tab[ii][0]) == 0)
        {
            if (tab[ii] && (tab[ii][0] == '<' || tab[ii][0] == '>'))
                ii += 2;
        }
        if (tab[ii] && is_character2(tab[ii][0]) == 1 && list[k]->cmd == NULL)
        {
            list[k]->cmd = malloc(ft_strlen(tab[ii]) + 1);
            if (!list[k]->cmd)
                exit(EXIT_FAILURE);
            ft_strncpy(list[k]->cmd, tab[ii], ft_strlen(tab[ii]));
            ii++;
        }
        if (tab[ii]&& is_character2(tab[ii][0]) == 1)
        {
            list[k]->args[i] = malloc(ft_strlen(tab[ii]) + 1);
            if (!list[k]->args[i])
                exit(EXIT_FAILURE);
            ft_strncpy(list[k]->args[i], tab[ii], ft_strlen(tab[ii]));
            // ii++;
        }
        ii++;
        i++;
    }
}


void redirection(t_list **list, char **tab, int pipe, int k)
{
    int i;
    int count;
    int size;
    int j;

    j = 0;
    i = 0;
    size = 0;
    count = count_redir(tab, pipe);
    list[k]->redir = (char **)malloc(sizeof(char *) * (count + 1) + 1);
    if (!list[k]->redir)
        exit(EXIT_FAILURE);
    while (i <= count)
    {
        list[k]->redir[i] = NULL;
        i++;
    }
    i = 0;
    while (tab[i] && tab[i][0] != '|')
    {
        if (tab[i][0] == '>' || tab[i][0] == '<')
        {
            list[k]->redir[j] = malloc(ft_strlen(tab[i]) + 1);
            if (!list[k]->redir[j])
                exit(EXIT_FAILURE); 
            ft_strncpy(list[k]->redir[j], tab[i], ft_strlen(tab[i]));
            size = 0;
            i++;
            if (tab[i][0] == '|')
                break;
            j++;
            list[k]->redir[j] = malloc(ft_strlen(tab[i]) + 1);
            if (!list[k]->redir[j])
                exit(EXIT_FAILURE);
            ft_strncpy(list[k]->redir[j], tab[i], ft_strlen(tab[i]));
            j++;
            i++;
        }
        else if (tab[i] && is_character2(tab[i][0]) == 1 && list[k]->cmd == NULL)
        {
            list[k]->cmd = malloc(ft_strlen(tab[i]) + 1);
            (!list[k]->cmd) ? exit(EXIT_FAILURE) : 0;
            ft_strncpy(list[k]->cmd, tab[i], ft_strlen(tab[i]));
            i++;
        }
        else 
            i++;
    }
}

void continue_parssing(t_list **list, char **tab, char *line, t_env *env_list)
{
    tab = expend(tab, env_list);
    // (void)env_list;
    int count = count_cmds(line);
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
        pipe = 0;
        next_pipe = finnd_pipe(tab, count);
        list[k] = malloc(sizeof(t_list) + 1);
        if (!list)
            exit(EXIT_FAILURE);
        list[k]->cmd = NULL;
        list[k]->redir = NULL;
        list[k]->args = NULL;
        list[k]->check_export = 0;
        if (tab && tab[pipe] && tab[pipe][0] && tab[pipe][0] != '>' && tab[pipe][0] != '<')
        {
            list[k]->cmd = malloc(ft_strlen(tab[pipe]) + 1);
            if (!list[k]->cmd)
                exit(EXIT_FAILURE);
            ft_strncpy(list[k]->cmd, tab[pipe], ft_strlen(tab[pipe]));
            pipe++;
        }
        args(list, tab, k, pipe);
        redirection(list, tab, pipe , k);
        tab = tab + next_pipe;
        k++;
    }
    (*list)->nbr = k;
}
