# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: idakhlao <idakhlao@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/07/05 14:53:25 by idakhlao          #+#    #+#              #
#    Updated: 2024/08/27 20:03:05 by idakhlao         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

SRCS = src/prout.c src/expand.c src/path_access.c \
		src/exec_redir_out.c src/exec_redir_in.c src/exec_cmd.c \
		src/builtins/echo.c src/builtins/cd_pwd.c src/builtins/env.c src/builtins/export.c src/builtins/unset.c src/builtins/exit.c\
		src/utils/ft_tabdup.c src/utils/ft_tablen.c src/utils/split_pipes.c\
		src/signals.c
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
