/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   remove_quotes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haalouan <haalouan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/02 00:47:28 by haalouan          #+#    #+#             */
/*   Updated: 2024/05/08 18:54:59 by haalouan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"


void handele_cmd(t_list **list, int *i, int *j, int *k)
{
    while (list && list[*i] && list[*i]->cmd && list[*i]->cmd[*j] != '\0')
    {
        if (list && list[*i] && list[*i]->cmd && list[*i]->cmd[*j] && list[*i]->cmd[*j] == '\"')
        {
            (*j)++;
            while (list && list[*i] && list[*i]->cmd && list[*i]->cmd[*j] && list[*i]->cmd[*j] != '\"')
                list[*i]->cmd[(*k)++] = list[*i]->cmd[(*j)++];
            if (list && list[*i] && list[*i]->cmd && list[*i]->cmd[*j] == '\"')
                (*j)++;
        }
        else if (list && list[*i] && list[*i]->cmd && list[*i]->cmd[*j] && list[*i]->cmd[*j] == '\'')
        {
            (*j)++;
            while (list && list[*i] && list[*i]->cmd && list[*i]->cmd[*j] && list[*i]->cmd[*j] != '\'')
                list[*i]->cmd[(*k)++] = list[*i]->cmd[(*j)++];
            if (list && list[*i] && list[*i]->cmd && list[*i]->cmd[*j] == '\'')
                (*j)++;
        }
        else if (list && list[*i] && list[*i]->cmd && list[*i]->cmd[*j] && list[*i]->cmd[*j] != '\"' && list[*i]->cmd[*j] != '\'')
            list[*i]->cmd[(*k)++] = list[*i]->cmd[(*j)++];
        }
        if (list[*i] && list[*i]->cmd)
            list[*i]->cmd[*k] = '\0';
}
void handele_redir(t_list **list, int *i, int *j, int *k, int *l)
{
    while (list && list[*i] && list[*i]->redir && list[*i]->redir[*j])
    {
        *l = 0;
        *k = 0;
        while (list && list[*i] && list[*i]->redir && list[*i]->redir[*j] && list[*i]->redir[*j][*l])
        {
            if (list && list[*i] && list[*i]->redir && list[*i]->redir[*j] && list[*i]->redir[*j][*l] && list[*i]->redir[*j][*l] == '\"')
            {
                (*l)++;
                while (list && list[*i] && list[*i]->redir && list[*i]->redir[*j][*l] && list[*i]->redir[*j][*l] != '\"')
                {
                    list[*i]->redir[*j][*k] = list[*i]->redir[*j][*l];
                    (*k)++;
                    (*l)++;
                }
                if (list && list[*i] && list[*i]->redir && list[*i]->redir[*j] && list[*i]->redir[*j][*l] == '\"')
                    (*l)++;
            }
            else if (list && list[*i] && list[*i]->redir && list[*i]->redir[*j] && list[*i]->redir[*j][*l] && list[*i]->redir[*j][*l] == '\'')
            {
                (*l)++;
                while (list && list[*i] && list[*i]->redir && list[*i]->redir[*j][*l] && list[*i]->redir[*j][*l] != '\'')
                {
                    list[*i]->redir[*j][*k] = list[*i]->redir[*j][*l];
                    (*k)++;
                    (*l)++;
                }
                if (list && list[*i] && list[*i]->redir && list[*i]->redir[*j] && list[*i]->redir[*j][*l] == '\'')
                    (*l)++;
            }
            else if (list && list[*i] && list[*i]->redir && list[*i]->redir[*j] && list[*i]->redir[*j][*l] && list[*i]->redir[*j][*l] != '\"' && list[*i]->redir[*j][*l] != '\'')
            {
                list[*i]->redir[*j][*k] = list[*i]->redir[*j][*l];
                (*k)++;
                (*l)++;
            }
        }
        if (list && list[*i] && list[*i]->redir && list[*i]->redir[*j])
            list[*i]->redir[*j][*k] = '\0';
        (*j)++;
    }
}

// void continue_handele_args(t_list **list, int *i, int *j, int *k, int *l)
// {
//     if (list && list[*i] && list[*i]->args && list[*i]->args[*j] && list[*i]->args[*j][*l] && list[*i]->args[*j][*l] == '\'')
//     {
//         while (list && list[*i] && list[*i]->args && list[*i]->args[*j][++(*l)] && list[*i]->args[*j][*l] != '\'')
//         {
//             list[*i]->args[*j][*k] = list[*i]->args[*j][*l];
//             (*k)++;
//             (*l)++;
//         }
//         if (list && list[*i] && list[*i]->args && list[*i]->args[*j] && list[*i]->args[*j][*l] == '\'')
//             (*l)++;
//     }
//     else if (list && list[*i] && list[*i]->args && list[*i]->args[*j] && list[*i]->args[*j][*l] && list[*i]->args[*j][*l] != '\"' && list[*i]->args[*j][*l] != '\'')
//         list[*i]->args[*j][(*k)++] = list[*i]->args[*j][(*l)++];
// }


// void handele_args(t_list **list, int *i, int *j, int *k, int *l)
// {
//     while (list && list[*i] && list[*i]->args && list[*i]->args[*j])
//     {
//         *l = 0;
//         *k = 0;
//         while (list && list[*i] && list[*i]->args && list[*i]->args[*j] && list[*i]->args[*j][*l])
//         {
//             if (list && list[*i] && list[*i]->args && list[*i]->args[*j] && list[*i]->args[*j][*l] && list[*i]->args[*j][*l] == '\"')
//             {
//                 while (list && list[*i] && list[*i]->args && list[*i]->args[*j][++(*l)] && list[*i]->args[*j][*l] != '\"')
//                 {
//                     list[*i]->args[*j][*k] = list[*i]->args[*j][*l];
//                     (*k)++;
//                     (*l)++;
//                 }
//                 if (list && list[*i] && list[*i]->args && list[*i]->args[*j] && list[*i]->args[*j][*l] == '\"')
//                     (*l)++;
//             }
//             continue_handele_args(list, i, j, k, l);
//         }
//         if (list && list[*i] && list[*i]->args && list[*i]->args[*j])
//             list[*i]->args[*j][*k] = '\0';
//         (*j)++;
//     }
// }

void handele_args(t_list **list, int *i, int *j, int *k, int *l)
{
    while (list && list[*i] && list[*i]->args && list[*i]->args[*j])
    {
        *l = 0;
        *k = 0;
        while (list && list[*i] && list[*i]->args && list[*i]->args[*j] && list[*i]->args[*j][*l])
        {
            if (list && list[*i] && list[*i]->args && list[*i]->args[*j] && list[*i]->args[*j][*l] && list[*i]->args[*j][*l] == '\"')
            {
                (*l)++;
                while (list && list[*i] && list[*i]->args && list[*i]->args[*j][*l] && list[*i]->args[*j][*l] != '\"')
                {
                    list[*i]->args[*j][*k] = list[*i]->args[*j][*l];
                    (*k)++;
                    (*l)++;
                }
                if (list && list[*i] && list[*i]->args && list[*i]->args[*j] && list[*i]->args[*j][*l] == '\"')
                    (*l)++;
            }
            else if (list && list[*i] && list[*i]->args && list[*i]->args[*j] && list[*i]->args[*j][*l] && list[*i]->args[*j][*l] == '\'')
            {
                (*l)++;
                while (list && list[*i] && list[*i]->args && list[*i]->args[*j][*l] && list[*i]->args[*j][*l] != '\'')
                {
                    list[*i]->args[*j][*k] = list[*i]->args[*j][*l];
                    (*k)++;
                    (*l)++;
                }
                if (list && list[*i] && list[*i]->args && list[*i]->args[*j] && list[*i]->args[*j][*l] == '\'')
                    (*l)++;
            }
            else if (list && list[*i] && list[*i]->args && list[*i]->args[*j] && list[*i]->args[*j][*l] && list[*i]->args[*j][*l] != '\"' && list[*i]->args[*j][*l] != '\'')
            {
                list[*i]->args[*j][*k] = list[*i]->args[*j][*l];
                (*k)++;
                (*l)++;
            }
        }
        if (list && list[*i] && list[*i]->args && list[*i]->args[*j])
            list[*i]->args[*j][*k] = '\0';
        (*j)++;
    }
}

void remove_quotes(t_list** list)
{
    int i;
    int k;
    int l;
    int j;

    i = 0;
    while (list[i])
    {
        k = 0;
        j = 0;
        //cmd
        handele_cmd(list, &i, &j, &k);
        //redir
        k = 0;
        j = 0;
        l = 0;
        handele_redir(list, &i, &j, &k, &l);
        //args
        j = 0;
        handele_args(list, &i, &j, &k, &l);
        i++;
    }
}