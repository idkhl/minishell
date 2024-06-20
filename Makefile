# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: idakhlao <idakhlao@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/03/11 09:10:49 by idakhlao          #+#    #+#              #
#    Updated: 2024/06/20 18:00:09 by idakhlao         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

SRCS = src/prout.c \
		src/builtins/echo.c src/builtins/cd_pwd.c src/builtins/env.c src/builtins/export.c src/builtins/unset.c \
		src/utils/ft_tabdup.c src/utils/ft_tablen.c
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

re : fclean all

.PHONY = make clean fclean re
