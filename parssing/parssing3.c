/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parssing3.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haalouan <haalouan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/02 01:20:05 by haalouan          #+#    #+#             */
/*   Updated: 2024/05/02 01:20:28 by haalouan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int count_pipe(char **tab, int len)
{
    int i = 0;
    int count = 0;
    while (i < len)
    {
        if (tab && tab[i] && tab[i][0] == '|')
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