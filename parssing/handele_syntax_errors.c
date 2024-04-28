/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handele_syntax_errors.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haalouan <haalouan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 21:55:56 by haalouan          #+#    #+#             */
/*   Updated: 2024/04/28 13:42:42 by haalouan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void handele_error()
{
    printf("=> " ANSI_BACKGROUND_RED     "syntax error"     ANSI_RESET_ALL "\n");
    exit(0);
}
int  check_tab(char **tab, char *line)
{
    int i = 0;
    if (tab[i] && (tab[i][0] == '>' || tab[i][0] == '<' || tab[i][0] == '|'))
        return 1;
    int count = count_cmds(line);
    if (tab[i] && (tab[count - 1][0] == '>' || tab[count - 1][0] == '<' || tab[count - 1][0] == '|'))
        return 1;
    return 0;
}

int count_quote(char *line, int len)
{
    int count = 0;
    while (*line && len > 0)
    {
        if (*line == '\"' || *line == '\'')
            count++;
        line++;
        len--;
    }
    return (count % 2);
}