/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   remove_quotes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haalouan <haalouan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/02 00:47:28 by haalouan          #+#    #+#             */
/*   Updated: 2024/05/10 22:23:44 by haalouan         ###   ########.fr       */
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

void handele_export(t_list **list, int *i, int *j , int *k, int *l)
{
    while (list && list[*i] && list[*i]->args && list[*i]->args[*j] && list[*i]->args[*j][*l])
    {
        list[*i]->args[*j][*k] = list[*i]->args[*j][*l];
        (*k)++;
        (*l)++;
    }
}


int check_expend(char *str, t_env *env_list, char c)
{
    int i = 0;
    i++;
    printf("%s\n", str);
    while (str && str[0] && str[i] && str[i] != c)
        i++;
    while (env_list != NULL)
    {
        if (str && ft_strncmp(str, env_list->value, i) == 0)
        {
            return 1;
        }
        env_list = env_list->next;
    }
    return 0;
}

void handele_args(t_list **list, int *i, int *j, int *k, int *l, t_env *env_list)
{
    while (list && list[*i] && list[*i]->args && list[*i]->args[*j])
    {
        *l = 0;
        *k = 0;                                                                                                                                                                                                                      
        while (list && list[*i] && list[*i]->args && list[*i]->args[*j] && list[*i]->args[*j][*l])
        {
            if (list && list[*i] && list[*i]->args && list[*i]->args[*j] && list[*i]->args[*j][*l] && list[*i]->args[*j][*l] == '\"')
            {
                if (check_expend(list[*i]->args[*j] + *l, env_list, '\"') == 1)
                {
                    list[*i]->args[*j][*k] = list[*i]->args[*j][*l];
                    (*k)++;
                    (*l)++;
                    while (list && list[*i] && list[*i]->args && list[*i]->args[*j][*l] && list[*i]->args[*j][*l] != '\"')
                    {
                        printf("%c\n", list[*i]->args[*j][*l]);
                        list[*i]->args[*j][*k] = list[*i]->args[*j][*l];
                        (*k)++;
                        (*l)++;
                    }
                    if (list[*i] && list[*i]->args && list[*i]->args[*j][*l] && list[*i]->args[*j][*l] == '\"')
                    {
                        // (*k)++;
                        // (*l)++;
                        printf("%c\n", list[*i]->args[*j][*l]);
                        list[*i]->args[*j][*k] = list[*i]->args[*j][*l];
                        (*k)++;
                    }
                }
                else
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
                if (check_expend(list[*i]->args[*j] + *l, env_list, '\'') == 1)
                {
                    list[*i]->args[*j][*k] = list[*i]->args[*j][*l];
                    (*k)++;
                    (*l)++;
                    while (list && list[*i] && list[*i]->args && list[*i]->args[*j][*l] && list[*i]->args[*j][*l] != '\'')
                    {
                        printf("%c\n", list[*i]->args[*j][*l]);
                        list[*i]->args[*j][*k] = list[*i]->args[*j][*l];
                        (*k)++;
                        (*l)++;
                    }
                    if (list[*i] && list[*i]->args && list[*i]->args[*j][*l] && list[*i]->args[*j][*l] == '\'')
                    {
                        // (*k)++;
                        // (*l)++;
                        printf("%c\n", list[*i]->args[*j][*l]);
                        list[*i]->args[*j][*k] = list[*i]->args[*j][*l];
                        (*k)++;
                    }
                }
                else
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


void remove_quotes(t_list** list, t_env *env_list)
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
        handele_args(list, &i, &j, &k, &l, env_list);
        i++;
    }
}
