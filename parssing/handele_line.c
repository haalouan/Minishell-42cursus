/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handele_line.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haalouan <haalouan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/02 00:46:44 by haalouan          #+#    #+#             */
/*   Updated: 2024/05/12 18:26:36 by haalouan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"



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
            if (is_character(line[i]) == 0 && line[i] != '\'' && line[i] != '\"')
                break;
        }
        else if (line[i] == '\"')
        {
            i++;
            while (line[i] != '\"' && line[i] != '\0')
                i++;
            if (line[i] == '\"')
                i++;
            if (is_character(line[i]) == 0 && line[i] != '\'' && line[i] != '\"')
                break;
        }
        else
            break;
    }
    *le += i;
    // int j = count_quote(line, i);
    add_tab(line , tab, i);
}

// void continue_handele_word(char *line, int *i)
// {
//     while (line[*i] != '\0')
//     {
//         while (is_character(line[*i]) == 1 && line[*i] != '\0')
//             (*i)++;
//         if (line[*i] == '\'')
//         {
//             while (line[++(*i)] != '\'' && line[*i] != '\0')
//                 (*i)++;
//             if (line[*i] == '\'')
//                 (*i)++;
//             if (is_character(*line) == 0 && *line != '\'' && *line != '\"')
//                 break;
//         }
//         else if (line[*i] == '\"')
//         {
//             while (line[++(*i)] != '\"' && line[*i] != '\0')
//                 (*i)++;
//             if (line[*i] == '\"')
//                 (*i)++;
//             if (is_character(line[*i]) == 0 && line[*i] != '\'' && line[*i] != '\"')//
//                 break;
//         }
//         else
//             break;
//     }
// }

// void handele_word(char **le, char **tab)
// {
//     int i;
//     char *line;

//     line = *le;
//     i = 0;
//     continue_handele_word(line, &i);
//     *le += i;
//     add_tab(line , tab, i);
// }

void continue_handele_line(t_check check, char **line, char **tab)
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
}

void handele_line(char **line, char **tab, t_check check)
{
    continue_handele_line(check, line, tab);
    if (check.find_pipe == 1)
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