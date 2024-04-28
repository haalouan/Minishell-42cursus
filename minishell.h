/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haalouan <haalouan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 17:22:31 by haalouan          #+#    #+#             */
/*   Updated: 2024/04/28 16:52:59 by haalouan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <errno.h>


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
}t_check;

typedef struct s_list
{
    char *cmd;
    char *redir;
    char **args;
}t_list;



//execution

typedef struct s_env
{
	char *key;
	char *value;
	struct s_env *next;
} t_env;


int ft_strcmp(char *arg, char *str);
t_env	*ft_lstnew(char *key , char *content);
t_env *ft_lstlast(t_env *lst);
void ft_lstadd_back(t_env **lst, t_env *new);
char **ft_split(char const *s, char c);
int ft_lstsize(t_env *lst);
t_env	*ft_lstlast(t_env *lst);
void execution(t_list **list,char **env);






//utils
size_t	ft_strlen(const char *str);
char    *ft_strncpy(char *dest, const char *src, int len);
char *ft_strcat(char *dest, char *src);
int is_character(char c);


//parssing
t_list **parssing(char *line);
void handele_error();
int count_lists(char *line);
void check_init(t_check *check);
void check_check(char *line, t_check *check);
int count_quote(char *line, int len);
void handele_error();
void add_tab(char *line, char **tab, int len);
int count_pipe(char **tab, int len);
char **handele_parssing(char *line);
// int  check_tab(t_list **tab, char *line);
void continue_parssing(t_list **temp, char **tab, char *line);
void print_tab(char **tab, char *line, t_list **list);
int  check_tab(t_list **list);

#endif