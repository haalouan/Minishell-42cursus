/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haalouan <haalouan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 17:22:31 by haalouan          #+#    #+#             */
/*   Updated: 2024/05/08 19:23:33 by haalouan         ###   ########.fr       */
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
#include <string.h>
# include <fcntl.h>

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
    int nbr;
    char *cmd;
    char **redir;
    int exit;
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
void execution(t_list **list, t_env *env_list,char **env);
void set_env(char **env, t_env **env_list);
int	ft_is_alpha(char c);
int check_args(char *args,char *str);
void	ft_export(char **args, t_env **env);
void	handle_cmd(t_list *cmds,char **env);
char	*ft_strjoin3(char *s1, char *s2, char *s3);
char	*ft_strnstr(const char *haystack, const char *needle, size_t len);
void	childe_process(t_list *list, char **envp);
void	last_command(t_list *list, char **envp);
void	error(void);
void	execute(char *argv, char **envp);

char *ft_substr(char const *s, unsigned int start, int len);
/*******************************************************parssing*******************************************************/

//expend2
char *ft_str_replace(const char *source, const char *pattern, const char *replacement);
char *get_env_value(char *key, t_env *export_i);
char *get_env_key(char *str, int i);
char *remove_$(char *tab, int check);
int expend_in_double_quote(char **tab, int i, int j, t_env *env_list);

//expend1
int continue_expend(char **tab, int i, int j, t_env *env_list);
void expend(char **tab, t_env *env_list);


//helpers_function1
char *ft_strstr(const char *haystack, const char *needle);
char	*ft_strdup(const char *s1);
int	ft_isdigit(int c);
int is_character(char c);
void print_tab(char **tab, char *line, t_list **list);//
int is_character2(char c);

//helpers_function2
int	ft_isalpha(int c);
int	ft_isalnum(int c);
size_t	ft_strlen(const char *str);
char    *ft_strncpy(char *dest, const char *src, int len);
char *ft_strcat(char *dest, char *src);

//syntax_errors
void handele_error();
int count_single_quote(char *line, int *i);
int count_double_quote(char *line, int *i);
int count_quote(char *line);
int  check_tab(t_list **list);

//check
void check_check(char *line, t_check *check);
void check_init(t_check *check);
int check(char **tab);
int check_error(char **tab);
int check_line(char *line);

//parssing1
t_list **parssing(char *line, t_env *env_list);
char **handele_parssing(char *line);
void add_tab(char *line, char **tab, int len);

//remove_quotes
void handele_cmd(t_list **list, int *i, int *j, int *k);
void handele_redir(t_list **list, int *i, int *j, int *k, int *l);
void continue_handele_args(t_list **list, int *i, int *j, int *k, int *l);
void handele_args(t_list **list, int *i, int *j, int *k, int *l);
void remove_quotes(t_list** list);

//handele_line
void continue_handele_word(char *line, int *i);
void handele_word(char **le, char **tab);
void continue_handele_line(t_check check, char **line, char **tab);
void handele_line(char **line, char **tab, t_check check);

//count_cmds
int is_quote(char c);
char *continue_count_cmds(char *line, int *count);
int count_cmds(char *line);

//parssing1
t_list **parssing(char *line, t_env *env_list);
char **handele_parssing(char *line);
void add_tab(char *line, char **tab, int len);

//parssing2
void continue_parssing(t_list **list, char **tab, char *line, t_env *env_list);

//parssing3
int count_pipe(char **tab, int len);
int finnd_pipe(char **tab, int count);
int find_redir(char **tab, int count);

#endif