# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: idakhlao <idakhlao@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/03/11 09:10:49 by idakhlao          #+#    #+#              #
#    Updated: 2024/06/14 17:50:06 by idakhlao         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

SRCS = src/prout.c
OBJS = ${SRCS:.c=.o}
CFLAGS = -Wall -Wextra -Werror -g3 
PRINTF = ./printf/libftprintf.a
LIBFT = ./libft/libft.a
CC = cc
RM = rm -f

all : $(NAME) 

.c.o:
	cc $(CFLAGS) -c -o $@ $< 

$(NAME): start $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -lreadline -o $(NAME) $(PRINTF) $(LIBFT)

start :
	make -C printf all
	make -C libft all

clean :
	${RM} ${OBJS}
	make -C printf clean
	make -C libft clean

fclean : clean
	${RM} ${NAME}
	make -C printf fclean
	make -C libft fclean

re : fclean all

.PHONY = make clean fclean re
