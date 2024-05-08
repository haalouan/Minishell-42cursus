/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haalouan <haalouan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/02 00:35:06 by haalouan          #+#    #+#             */
/*   Updated: 2024/05/08 18:26:44 by haalouan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void check_check(char *line, t_check *check)
{
        if (line && *line && (is_character(*line) == 1 || *line == '\"' || *line == '\''))
            check->find_word = 1;
        if (line &&*line == '$')
            check->find_$ = 1;
        if (line &&*line == '|')
            check->find_pipe = 1;
        if (line && *line == '>')
        {
			line++;
            if (*line == '>')
                check->find_append_op = 1;
            else if (check->find_append_op == -1)
                check->find_in_re = 1;
        }
        if (*line == '<')
        {
			line++;
            if (*line == '<')
                check->find_here_doc = 1;
            else if (check->find_here_doc == -1)
                check->find_out_re = 1;
        }
}

void check_init(t_check *check)
{
    check->find_word = -1;
    check->find_pipe = -1;
    check->find_in_re = -1;
    check->find_out_re = -1;
    check->find_append_op = -1;
    check->find_here_doc = -1;
    check->find_$ = -1;
}


int check(char **tab)
{
    int i = 0;
    
    if (!tab || !*tab)
        return 2;
    if (tab[0][0] == '|')
        return 1;
    while (tab && tab[i] != NULL)
    {
        if (tab && tab[i] && tab[i][0] == '|' && tab[i + 1] && tab[i + 1][0] == '|')
            return 1;
        if (tab && tab[i] && tab[i][0] == '>' && tab[i + 1] && tab[i + 1][0] == '|')
            return 1;
        if (tab && tab[i] && tab[i][0] == '<' && tab[i + 1] && tab[i + 1][0] == '|')
            return 1;
        if (tab && tab[i] && tab[i][0] == '<' && tab[i + 1] && tab[i + 1][0] == '<')
            return 1;
        if (tab && tab[i] && tab[i][0] == '>' && tab[i + 1] && tab[i + 1][0] == '>')
            return 1;
        if (tab && tab[i] && tab[i][0] == '>' && tab[i + 1] && tab[i + 1][0] == '<')
            return 1;
        if (tab && tab[i] && tab[i][0] == '<' && tab[i + 1] && tab[i + 1][0] == '>')
            return 1;
        i++;
    }
    if (tab && tab[i - 1] && (tab[i - 1][0] == '|' || tab[i - 1][0] == '<' || tab[i - 1][0] == '>'))
        return 1;
    return 0;
}

int check_error(char **tab)
{
    if (check(tab) == 2)
        return 1;
    if (check(tab) == 1)
    {
        handele_error();
        return 1;
    }
    return 0;
}


int check_line(char *line)
{
    int i = 0;
    while (line && line[i] != '\0')
        i++;
    if (line[i - 1] == '|' || line[i - 1] == '>' || line[i - 1] == '<')
        return 1;
    return 0;
}