SRCS =	main.c ./parssing/helpers_functions.c ./parssing/handele_syntax_errors.c ./parssing/parssing.c ./parssing/count_cmds.c ./parssing/parssing2.c
OBJS = ${SRCS:.c=.o}
NAME = minishell
CC = cc
RM = rm -f
CFLAGS = -Wall -Wextra -Werror -fsanitize=address

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
