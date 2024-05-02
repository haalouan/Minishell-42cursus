/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   count_lists.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haalouan <haalouan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/26 16:34:50 by haalouan          #+#    #+#             */
/*   Updated: 2024/04/28 13:43:03 by haalouan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int is_quote(char c)
{
    if (c == '\'' || c == '\"')
        return 1;
    return 0;
    // return c == '\'' || c == '\"';
}

char* skip_quotes_and_characters(char *line)
{
    char quote;

    quote = 0;
    while (*line != '\0')
    {
        if (is_character(*line) == 1)
        {
            while (is_character(*line) == 1 && *line != '\0')
                line++;
        }
        else if (is_quote(*line))
        {
            quote = *line;
            line++;
            while (*line != quote && *line != '\0')
                line++;
            if (*line == quote)
                line++;
        }
        if (!is_character(*line) && *line != '\'' && *line != '\"')
            break;
    }
    return line;
}


char *continue_count_cmds(char *line, int *count)
{
     if (*line == '<' && *line)
        {
            line++;
            if (*line == '<') 
            {
                (*count)++;
                line++;
            }
            else
                (*count)++;
        }
        else if (*line == '>')
        {
            line++;
            if (*line == '>')
            {
                (*count)++;
                line++;
            }
            else
                (*count)++;
        }
    return line;
}

int count_cmds(char *line)
{
    int count;

    count = 0;
    while (line && *line)
    {
        if (*line == '<' || *line == '>')
            line = continue_count_cmds(line, &count);
        else if (*line == '|')
        {
            count++;
            line++;
        }
        else if (*line == '\'' || *line == '\"' || is_character(*line) == 1)
        {
            count++;
            line = skip_quotes_and_characters(line);
        }
        else
            line++;
    }
    return count;
}


// int count_lists(char *line)
// {
//     int count = 0;
//     while (*line)
//     {
//         if (*line == '<' && *line)
//         {
//             line++;
//             if (*line == '<')
//             {
//                 count++;
//                 line++;
//             }
//             else
//                 count++;
//         }
//         else if (*line == '>')
//         {
//             line++;
//             if (*line == '>')
//             {
//                 count++;
//                 line++;
//             }
//             else
//                 count++;
//         }
//         else if (*line == '|')
//         {
//             count++;
//             line++;
//         }
//         else if (*line == '\'' || *line == '\"' || is_character(*line) == 1)
//         {
//             count++;
//             while (*line != '\0')
//             {
//                 while (is_character(*line) == 1 && *line != '\0')
//                     line++;
//                 if (*line == '\'')
//                 {
//                     line++;
//                     while (*line != '\'' && *line != '\0')
//                         line++;
//                     if (*line == '\'')
//                         line++;
//                     if (is_character(*line) == 0 && *line != '\'' && *line != '\"')
//                         break;
//                 }
//                 else if (*line == '\"')
//                 {
//                     line++;
//                     while (*line != '\"' && *line != '\0')
//                         line++;
//                     if (*line == '\"')
//                         line++;
//                     if (is_character(*line) == 0 && *line != '\'' && *line != '\"')
//                         break;
//                 }
//                 else
//                     break;
//             }
//         }
//         else
//             line++;
//     }
//     return count;
// }
