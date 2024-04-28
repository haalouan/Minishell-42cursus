SRCS =	main.c ./parssing/helpers_functions.c ./parssing/handele_syntax_errors.c ./parssing/count_cmds.c ./parssing/parssing.c  ./parssing/parssing2.c ./execution/builtins.c ./execution/ft_lstadd_back_bonus.c ./execution/ft_lstlast_bonus.c ./execution/ft_lstsize_bonus.c ./execution/ft_lstnew_bonus.c ./execution/ft_split.c ./execution/utils.c
OBJS = ${SRCS:.c=.o}
NAME = minishell
CC = cc
RM = rm -f
CFLAGS = -Wall -Wextra -Werror -g -fsanitize=address

$(NAME): $(OBJS)
	@$(CC) -lreadline $(CFLAGS) $(OBJS) -o $(NAME)
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
