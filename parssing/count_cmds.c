/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   count_cmds.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haalouan <haalouan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/26 16:34:50 by haalouan          #+#    #+#             */
/*   Updated: 2024/04/28 13:43:03 by haalouan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"


int count_cmds(char *line)
{
    int count = 0;
    while (*line)
    {
        if (*line == '<' && *line)
        {
            line++;
            if (*line == '<')
            {
                count++;
                line++;
            }
            else
                count++;
        }
        else if (*line == '>')
        {
            line++;
            if (*line == '>')
            {
                count++;
                line++;
            }
            else
                count++;
        }
        else if (*line == '|')
        {
            count++;
            line++;
        }
        else if (*line == '\'' || *line == '\"' || is_character(*line) == 1)
        {
            count++;
            while (*line != '\0')
            {
                while (is_character(*line) == 1 && *line != '\0')
                    line++;
                if (*line == '\'')
                {
                    line++;
                    while (*line != '\'' && *line != '\0')
                        line++;
                    if (*line == '\'')
                        line++;
                    if (is_character(*line) == 0 && *line != '\'' && *line != '\"')
                        break;
                }
                else if (*line == '\"')
                {
                    line++;
                    while (*line != '\"' && *line != '\0')
                        line++;
                    if (*line == '\"')
                        line++;
                    if (is_character(*line) == 0 && *line != '\'' && *line != '\"')
                        break;
                }
                else
                    break;
            }
        }
        else
            line++;
    }
    return count;
}
