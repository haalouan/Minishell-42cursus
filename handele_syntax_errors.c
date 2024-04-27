/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handele_syntax_errors.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haalouan <haalouan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 21:55:56 by haalouan          #+#    #+#             */
/*   Updated: 2024/04/27 10:49:46 by haalouan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void handele_error()
{
    printf("=> " ANSI_BACKGROUND_RED     "syntax error"     ANSI_RESET_ALL "\n");
    exit(0);
}
void check_errors(char *line)
{
    if (*line == '-')
        handele_error();
    int i = 0;
    int j = 0;
    while (line[i] != '\0')
    {
        j = i + 1;
        if (line[j] == '-')
        {
            if (line[i] != ' ')
                handele_error();
        }
        i++;
    }
}

void check_tab(char **tab, char *line)
{
    int i = 0;
    if (tab[i][0] == '>' || tab[i][0] == '<' || tab[i][0] == '|')
        handele_error();
    int count = count_cmds(line);
    if (tab[count - 1][0] == '>' || tab[count - 1][0] == '<' || tab[count - 1][0] == '|')
        handele_error();
}