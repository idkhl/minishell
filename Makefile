# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: afrikach <afrikach@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/09/16 15:38:17 by afrikach          #+#    #+#              #
#    Updated: 2024/09/20 17:14:03 by afrikach         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

SRCS = src/prout.c src/signals.c src/pipes.c src/exec_cmd.c \
		\
		src/builtins/echo.c src/builtins/cd_pwd.c src/builtins/env.c src/builtins/exit.c\
		src/builtins/export.c src/builtins/unset.c src/builtins/builtins.c\
		\
		src/utils/ft_tabdup.c src/utils/ft_tablen.c src/utils/split_pipes.c src/utils/split_quotes.c\
		src/utils/get_big_tab.c src/utils/path_access.c src/utils/fill_struct.c src/utils/ft_structcpy.c \
		\
		src/parsing/util.c src/parsing/syntax_quotes.c src/parsing/syntax_pipes.c\
		src/parsing/syntax_open_redir.c src/parsing/syntax_close_redir.c\
		\
		#src/exec_redir_out.c src/exec_redir_in.c \
		src/expand.c
		
OBJS = ${SRCS:.c=.o}
CFLAGS = -Wall -Wextra -Werror -g3 
LIBFT = ./libft/libft.a
CC = cc
RM = rm -f

all : $(NAME) 

.c.o:
	cc $(CFLAGS) -c -o $@ $< 

$(NAME): $(OBJS)
	make -C libft all
	$(CC) $(CFLAGS) $(OBJS) -lreadline -o $(NAME) $(LIBFT)

clean :
	${RM} ${OBJS}
	make -C libft clean

fclean : clean
	${RM} ${NAME}
	make -C libft fclean

ac : all clean
	make clean
	make -C libft clean

re : fclean all

.PHONY = make clean fclean re