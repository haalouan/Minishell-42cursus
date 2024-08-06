/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haalouan <haalouan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 17:22:31 by haalouan          #+#    #+#             */
/*   Updated: 2024/08/06 18:01:26 by haalouan         ###   ########.fr       */
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
# include <string.h>
# include <signal.h>
# include <fcntl.h>
# include <sys/stat.h>

int	g_status;

# define ANSI_RESET_ALL          "\x1b[0m"
# define ANSI_COLOR_RED          "\x1b[31m"
# define ANSI_COLOR_GREEN        "\x1b[32m"
# define ANSI_COLOR_YELLOW       "\x1b[33m"
# define ANSI_BACKGROUND_RED     "\x1b[41m"
# define ANSI_COLOR_MAGENTA      "\x1b[35m"

typedef struct s_check
{
	int	find_word;
	int	find_pipe;
	int	find_in_re;
	int	find_out_re;
	int	find_append_op;
	int	find_here_doc;
	int	in_d_cote;
	int	in_s_cote;
}	t_check;

typedef struct s_list
{
	int		nbr;
	char	*cmd;
	char	**redir;
	int		exit;
	int		check_export;
	char	**args;
	int		file_in;
	int		file_out;
	int		flag_here_doc;
	int		here_doc;
}	t_list;

typedef struct s_env
{
	char			*key;
	char			*value;
	struct s_env	*next;
}	t_env;

typedef struct s_int
{
	int	i;
	int	j;
	int	k;
	int	size;
	int	size2;
	int	in_here_doc;
}	t_int;

int		ft_strcmp(char *arg, char *str);
t_env	*ft_lstnew(char *key, char *content);
t_env	*ft_lstlast(t_env *lst);
void	ft_lstadd_back(t_env **lst, t_env *new);
char	**ft_split(char const *s, char c);
int		ft_lstsize(t_env *lst);
t_env	*ft_lstlast(t_env *lst);
void	execution(t_list **list, t_env **env_list);
void	set_env(char **env, t_env **env_list, int i);
int		ft_is_alpha(char c);
int		check_args(char *args, char *str);
void	ft_export(char **args, t_env **env);
void	handle_cmd(t_list *cmds, char **env);
char	*ft_strjoin3(char *s1, char *s2, char *s3);
char	*ft_strnstr(const char *haystack, const char *needle, size_t len);
void	error(void);
void	execute(char **cmds, char **envp, char *cmd);
int		change_value(t_env **env_list, char *value);
char	*ft_strjoin(char *s1, char *s2, int i, int j);
void	handle_redir(t_list *list, int i, int x);
void	handle_redir_no_command(t_list *list, int i);
char	*shlvl_increment(char *str);
int		set_here_doc(t_list **list, int i, int j, t_env *env_list);
void	ft_env(t_env *env_list, char **args);
int		ft_is_number(char *str);
int		ft_atoi(const char *str);
void	ft_echo(char **args, int n, int j, int x);
void	ft_cd(char **args, t_env *env_list);
void	ft_env(t_env *env_list, char **args);
void	ft_exit(char **args, t_list *cmds, int x, unsigned char i);
void	ft_pwd(t_env *env_list);
void	ft_unset(t_env **env_list, char **args);
void	ft_free(char **str);
char	**struct_to_char(t_env *env_list);
int		count_args0(char **args);
void	handle_one_cmd(t_list *cmds, t_env **env_list, int status);
void	close_here_doc(t_list **list);
void	handle_mult_cmd(t_list **list, t_env **env_list, int i, int prev_pipe);;
void	ft_builtins(t_list *cmds, t_env **env_list);
char	**free_struct(char **new_env);
char	*ft_strjoin_free(char *s1, char *s2);
void	split_by_equal(char *str, char **key, char **value, int i);
void	print_env(t_env *lst, int (*cmp)(char*, char*));
int		key_exist(t_env *env, char *key);
void	split_by_equal(char *str, char **key, char **value, int i);
void	help_fct2(t_list **list, int fd[2], int pid[(*list)->nbr]);
void	error_handling(char *cmd, char *str, int i, int x);
void	fork_error(int *x, int i, int *pid, int *fd);
void	handle_access(char **cmds, char **envp, char *cmd, char *path);
void	handle_directory(char **cmds, char **envp, char *cmd, char *path);

//
char	*ft_substr(char const *s, unsigned int start, int len);
char	**safe_alloc(int count);
int		count_redir(char **tab, int i);
int		is_ch(char c);
char	**safe_alloc(int count);
void	redirection(t_list **list, char **tab, int pipe, int k);
void	free_tab(char **tab);
void	free_list(t_list **list);
char	*expand_in_here_doc(char *line, t_env *env_list, int ex);
int		ft_size(char **tab);
char	*ft_str_replace(char *source, const char *pattern, char *replacement);
char	*get_env_value(char *key, t_env *export_i);
char	*get_env_key(char *str, int i);
char	*remove_dollar(char *tab, int check);
char	**expand_in_double_quote(char **tab, int i, int *j, t_env *env_list);
char	*expand_digit(char *str);
char	**continue_expand(char **tab, t_int *f, t_env *env_list);
char	**expand(char **tab, t_env *env_list, int i);
char	**change_tab(char **old_tab, char *str);
char	*protect_env(char *str, int i);
char	**ft_realloc(char **tab);
char	*protect_new_str(char *str);
int		search_for_value(char *str, char *s);
char	*ft_strstr(const char *haystack, const char *needle);
char	*ft_strdup(char *s1);
int		ft_isdigit(int c);
int		is_character(char c);
int		is_character2(char c);
char	*cont_exp2(char **value, int j, t_env *env_list, char *tab);
char	*cont_exp(char **value);
void	continue_arg(char **tab, int *ii);
int		c_str(char **tab);
int		exppp(char *tab, int j);
void	hndl_line(char *line, int *i);
int		ft_isalpha(int c);
int		ft_isalnum(int c);
size_t	ft_strlen(const char *str);
char	*ft_strncpy(char *dest, const char *src, int len);
char	*ft_strcat(char *dest, char *src);
int		ft_strncmp(const char *str1, const char *str2, size_t n);
char	*protect_new_tab(char *str);
void	handle_error(void);
int		count_single_quote(char *line, int *i);
int		count_double_quote(char *line, int *i);
int		count_quote(char *line);
int		check_error2(char **tab);
void	check_check(char *line, t_check *check);
void	check_init(t_check *check);
int		check(char **tab);
int		check_error(char **tab);
int		check_line(char *line);
t_list	**parssing(char *line, t_env *env_list);
char	**handle_parssing(char *line, t_env *env_list);
void	add_tab(char *line, char **tab, int len);
int		count_args(char **tab, int i);
void	handle_cmds(t_list **list, int *i, int *j, int *k);
void	handle_redi(t_list **list, int *i, int *j, int *l);
void	handle_args(t_list **list, int *i, int *j, int *l);
void	remove_quotes(t_list **list);
void	handle_word(char **le, char **tab);
void	continue_handle_line(t_check check, char **line, char **tab);
void	handle_line(char **line, char **tab, t_check check);
int		is_quote(char c);
char	*continue_count_cmds(char *line, int *count);
int		count_cmds(char *line);
t_list	**parssing(char *line, t_env *env_list);
char	**handle_parssing(char *line, t_env *env_list);
void	add_tab(char *line, char **tab, int len);
int		continue_parssing(t_list **list, char **tab, char *line);
int		exit_status(int status);
int		count_pipe(char **tab);
int		finnd_pipe(char **tab, int count);
int		find_redir(char **tab, int count);
char	*int_to_str(int num);
void	signal_handler(int sig);
void	init_signals(void);
void	setup_signal_handlers(void (*int_)(int), void (*quit_)(int));
void	sig_handler_child(int sig);
void	ignore_signals(void);
void	exit_helper(t_list *cmds, int status);
int		check_builtins(char *cmd);
void	handle_sigint(int signum);
char	*my_alloc(int len);

#endif