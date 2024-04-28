/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   count_cmds.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haalouan <haalouan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/26 16:34:50 by haalouan          #+#    #+#             */
/*   Updated: 2024/04/27 14:48:04 by haalouan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


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
                    if (is_character(*line) == 0)
                        break;
                }
                else if (*line == '\"')
                {
                    line++;
                    while (*line != '\"' && *line != '\0')
                        line++;
                    if (*line == '\"')
                        line++;
                    if (is_character(*line) == 0)
                        break;
                }
                else
                    break;
            }
        }
        // else if  (is_character(*line) == 1 && *line)
        // {
        //     count++;
        //     while  (is_character(*line) == 1 && *line)
        //         line++;
        //     if (*line != '\'' && *line != '\"' && *line)
        //         continue;
        //     else if (*line == '\"')
        //     {
        //         int dq = -1;
        //         int sq = -1;
        //         while (*line)
        //         {
        //             if (*line == '\"')
        //             {
        //                 dq = 1;
        //                 line++;
        //             }
        //             else if (*line == '\'')
        //             {
        //                 sq = 1;
        //                 line++;
        //             }
        //             if (dq == 1)
        //             {
        //                 while ((*line != '\"') && *line)
        //                     line++;
        //             }
        //             else if (sq == 1)
        //             {
        //                 while ((*line != '\'') && *line)
        //                     line++;
        //             }
        //             else
        //             {
        //                 if (*line && is_character(*line) == 1)
        //                     line++;
        //                 else
        //                     break;
        //             }
        //             if (*line == '\"')
        //             {
        //                 line++;
        //                 dq = -1;
        //             }
        //             else if (*line == '\'')
        //             {
        //                 line++;
        //                 sq = -1;
        //             }
        //             if (*line != '\'' && *line != '\"' && *line != '\"' && is_character(*line) == 0)
        //                 break;
        //         }    
        //     }
        //     else if (*line == '\'')
        //     {
        //         int dq = -1;
        //         int sq = -1;
        //         while (*line)
        //         {
        //             if (*line == '\'')
        //             {
        //                 dq = 1;
        //                 line++;
        //             }
        //             else if (*line == '\"')
        //             {
        //                 sq = 1;
        //                 line++;
        //             }
        //             if (dq == 1)
        //             {
        //                 while ((*line != '\'') && *line)
        //                     line++;
        //             }
        //             else if (sq == 1)
        //             {
        //                 while ((*line != '\"') && *line)
        //                     line++;
        //             }
        //             else
        //             {
        //                 if (*line && is_character(*line) == 1)
        //                     line++;
        //                 else
        //                     break;
        //             }
        //             if (*line == '\'')
        //             {
        //                 line++;
        //                 dq = -1;
        //             }
        //             else if (*line == '\"')
        //             {
        //                 line++;
        //                 sq = -1;
        //             }
        //             if (*line != '\'' && *line != '\"' && *line != '\"' && is_character(*line) == 0)
        //                 break;
        //         }    
        //     }
        // }
        // //
        // else if (*line == '\'')
        // {
        //     count++;
        //     int dq = -1;
        //     int sq = -1;
        //     while (*line)
        //     {
        //         if (*line == '\'')
        //         {
        //             dq = 1;
        //             line++;
        //         }
        //         else if (*line == '\"')
        //         {
        //             sq = 1;
        //             line++;
        //         }
        //         if (dq == 1)
        //         {
        //             while ((*line != '\'') && *line)
        //                 line++;
        //         }
        //         else if (sq == 1)
        //         {
        //             while ((*line != '\"') && *line)
        //                 line++;
        //         }
        //         else
        //         {
        //             if (*line && is_character(*line) == 1)
        //                 line++;
        //             else
        //                 break;
        //         }
        //         if (*line == '\'')
        //         {
        //             line++;
        //             dq = -1;
        //         }
        //         else if (*line == '\"')
        //         {
        //             line++;
        //             sq = -1;
        //         }
        //         if (*line != '\'' && *line != '\"' && *line != '\"' && is_character(*line) == 0)
        //             break;
        //     }    
        // }
        //     //
        // else if (*line == '\"')
        // {
        //     count++;
        //     int dq = -1;
        //     int sq = -1;
        //     while (*line)
        //     {
        //         if (*line == '\"')
        //         {
        //             dq = 1;
        //             line++;
        //         }
        //         else if (*line == '\'')
        //         {
        //             sq = 1;
        //             line++;
        //         }
        //         if (dq == 1)
        //         {
        //             while ((*line != '\"') && *line)
        //                 line++;
        //         }
        //         else if (sq == 1)
        //         {
        //             while ((*line != '\'') && *line)
        //                 line++;
        //         }
        //         else
        //         {
        //             if (*line && is_character(*line) == 1)
        //                 line++;
        //             else
        //                 break;
        //         }
        //         if (*line == '\"')
        //         {
        //             line++;
        //             dq = -1;
        //         }
        //         else if (*line == '\'')
        //         {
        //             line++;
        //             sq = -1;
        //         }
        //         if (*line != '\'' && *line != '\"' && *line != '\"' && is_character(*line) == 1)
        //             break;
        //     }    
        // }
        else
            line++;
    }
    return count;
}
