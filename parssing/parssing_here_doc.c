/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parssing_here_doc.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haalouan <haalouan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/25 14:30:26 by haalouan          #+#    #+#             */
/*   Updated: 2024/05/25 16:11:52 by haalouan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char **remove_quotes_tab(char **tab)
{
    int i = 0;
    int j = 0;
    int k = 0;
    while (tab && tab[i])
    {
        j = 0;
        k = 0;                                                                                                                                                                                                
        while (tab && tab[i] && tab[i][j])
        {
            if (tab[i] && tab[i][j] == '\"')
            {
                j++;
                while (tab[i] && tab[i][j] != '\"')
                {
                    tab[i][k] = tab[i][j];
                    k++;
                    j++;
                }
                if (tab[i] && tab[i][j] == '\"')
                    j++;
            }
            else if (tab[i][j] == '\'')
            {
                j++;
                while (tab[i] && tab[i][j] != '\'')
                {
                    tab[i][k] = tab[i][j];
                    k++;
                    j++;
                }
                if (tab[i] && tab[i][j] == '\'')
                    j++;
            }
            else if (tab[i] && tab[i][j] != '\"' && tab[i][j] != '\'')
            {
                tab[i][k] = tab[i][j];
                j++;
                k++;
            }
        }
        if (tab && tab[i])
            tab[i][k] = '\0';
        i++;
    }
    return tab;
}

void handle_her_doc(t_here_doc *her_doc, t_env *env_list)
{
    int i = 0;
    while (her_doc)
    {
        i = 0;
        // while (her_doc->lines && her_doc->lines[i])
        // {
        //     printf("before : %s\n", her_doc->lines[i]);
        //     i++;
        // }
        i = 0;
        her_doc->lines = expend(her_doc->lines, env_list, 1);
        her_doc->lines = remove_quotes_tab(her_doc->lines);
        // while (her_doc->lines && her_doc->lines[i])
        // {
        //     printf("after : %s\n", her_doc->lines[i]);
        //     i++;
        // }
        her_doc = her_doc->next;
    }
}
