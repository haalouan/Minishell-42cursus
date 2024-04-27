/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haalouan <haalouan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 17:22:31 by haalouan          #+#    #+#             */
/*   Updated: 2024/04/27 10:50:11 by haalouan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <readline/readline.h>
# include <readline/history.h>


//
#define ANSI_RESET_ALL          "\x1b[0m"
#define ANSI_COLOR_RED          "\x1b[31m"
#define ANSI_COLOR_GREEN        "\x1b[32m"
#define ANSI_COLOR_YELLOW       "\x1b[33m"
#define ANSI_BACKGROUND_RED     "\x1b[41m"
#define ANSI_COLOR_MAGENTA      "\x1b[35m"
//
typedef struct s_check
{
    int find_word;
    int find_pipe;
    int find_in_re;
    int find_out_re;
    int find_append_op;
    int find_here_doc;
    int find_$;
    int in_d_cote;
    int in_s_cote;
    int find_minus;
}t_check;

typedef struct s_list
{
    struct s_list *next;
    char *cmmd;
    int index;
    char *token;
    int flag_red;
}t_list;


typedef struct s_mini
{
    struct s_mini *next;
    char *cmd;
    char *redir;
}t_mini;

typedef struct s_comonds{
    int pipe; // |
    int in_re; // >
    int out_re; // <
    int append_op; // >>
    int here_doc; // <<
}t_comonds;

//utils
size_t	ft_strlen(const char *str);
char    *ft_strncpy(char *dest, const char *src, int len);
int	ft_strcmp(const char *str1, const char *str2);
char *ft_strcat(char *dest, char *src);
//handele_line

//handele_error
void handele_error();
int check_syntax_error(char *line);
int count_cmds(char *line);
void print_tab(char **tab, char *line);
//hndele_node
void check_init(t_check *check);
void check_check(char *line, t_check *check);
int count_quote(char *line, int len);
void handele_error();
void add_tab(char *line, char **tab, int len);
//parssing.c
char **parssing(char *line);
void check_errors(char *line);
int is_word(char c);
void check_tab(char **tab, char *line);
#endif