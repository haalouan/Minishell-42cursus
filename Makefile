SRCS =	main.c  ./parssing/parssing3.c ./parssing/remove_quotes.c ./parssing/handle_line.c \
		./parssing/check.c ./parssing/helpers_functions2.c \
		 ./parssing/helpers_functions1.c \
		./parssing/syntax_errors.c ./parssing/count_cmds.c ./parssing/parssing1.c \
		./parssing/parssing2.c ./execution/builtins.c \
		./execution/ft_split.c ./execution/utils.c  ./execution/export.c \
		./execution/handle_cmd.c ./execution/handle_redir.c ./execution/here_doc.c \
		./parssing/expand_in_here_doc.c ./parssing/parssing4.c ./parssing/remove_quotes2.c \
		./parssing/helpers_functions3.c ./parssing/expand1.c ./parssing/expand2.c \
		./parssing/free.c ./parssing/check2.c  ./parssing/expand3.c ./parssing/expand4.c \
		./parssing/expand5.c ./parssing/expand6.c ./execution/echo.c ./execution/cd.c ./execution/env_exit_pwd.c \
		./execution/lst_utils.c ./execution/utils2.c ./execution/utils3.c \
		./execution/unset.c ./execution/set_env.c ./execution/handl_one_cmd.c ./parssing/expand7.c \
		./parssing/remove_dollar.c ./parssing/parssing5.c

OBJS = ${SRCS:.c=.o}
NAME = minishell
CC = cc
RM = rm -f
READLINE_L = /Users/haalouan/.brew/opt/readline/lib
READLINE_I = /Users/haalouan/.brew/opt/readline/include

CFLAGS = -Wall -Wextra -g -I $(READLINE_I) -g -fsanitize=address
LDFLAGS = -L$(READLINE_L) -lreadline -lhistory

$(NAME): $(OBJS)
	@$(CC) -lreadline $(CFLAGS) $(LDFLAGS) $(OBJS) -o $(NAME)
	@echo "minishell ready!"

all: ${NAME}

%.o:%.c minishell.h
	@$(CC) $(CFLAGS) -c $< -o $@

clean:
	@echo "cleaned!"
	@${RM} ${OBJS}

fclean: clean
	@${RM} ${NAME}

re: fclean all

.PHONY : all clean fclean re
