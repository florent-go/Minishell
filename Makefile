NAME =		minishell

CFLAGS +=	-Wall -Wextra -Werror

SRCS =		srcs/main.c \
			srcs/execve.c \
			srcs/bultins.c \
			srcs/bultins2.c \
			srcs/builtins_echo.c \
			srcs/builtins_export.c \
			srcs/init_struct.c \
			srcs/init_exectab.c \
			srcs/lexer.c \
			srcs/lexer_collect_id.c \
			srcs/lexer_collect_string.c \
			srcs/lexer_collect_simpleq.c \
			srcs/lexer_utils.c \
			srcs/list_env.c \
			srcs/signal.c \
			srcs/parser.c \
			srcs/tokeniser_loop.c \
			srcs/redirection.c \
			srcs/utils.c \
			srcs/utils2.c \
			srcs/what_is_cmd.c \
			srcs/get_next_line.c \
			srcs/free.c \
			list/ft_lstadd_front.c \
			list/ft_lstnew.c \

OBJS =		$(SRCS:.c=.o)

all:		libft $(NAME)

$(NAME):	$(OBJS)
			gcc $(CFLAGS) $(OBJS) ./libft/libft.a ./includes/libreadline.a -lreadline -lncurses -o $(NAME)

libft:
			make -C ./libft

clean:
			make clean -C ./libft
			rm -f $(OBJS)

fclean:		clean
			rm -f $(NAME)
			make fclean -C ./libft

re: 		fclean all

.PHONY:		re clean fclean all libft
