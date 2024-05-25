SRCS =	main.c  ./parssing/parssing3.c ./parssing/remove_quotes.c ./parssing/handele_line.c \
		./parssing/check.c ./parssing/helpers_functions2.c ./parssing/expend1.c \
		./parssing/expend2.c ./parssing/helpers_functions1.c \
		./parssing/syntax_errors.c ./parssing/count_cmds.c ./parssing/parssing1.c \
		./parssing/parssing2.c ./execution/builtins.c \
		./execution/ft_lstadd_back_bonus.c ./execution/ft_lstlast_bonus.c \
		./execution/ft_lstsize_bonus.c ./execution/ft_lstnew_bonus.c \
		./execution/ft_split.c ./execution/utils.c  ./execution/export.c \
		./execution/handle_cmd.c ./execution/handle_redir.c ./execution/here_doc.c \
		./parssing/parssing_here_doc.c
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
