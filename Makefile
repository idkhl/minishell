# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: inesdakhlaoui <inesdakhlaoui@student.42    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/07/05 14:53:25 by idakhlao          #+#    #+#              #
#    Updated: 2024/09/09 18:38:59 by inesdakhlao      ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

SRCS = src/prout.c src/pipes.c src/exec_cmd.c src/redir.c \
		\
		src/builtins/echo.c src/builtins/cd_pwd.c src/builtins/env.c src/builtins/exit.c\
		src/builtins/export.c src/builtins/unset.c src/builtins/builtins.c\
		\
		src/utils/ft_tabdup.c src/utils/ft_tablen.c src/utils/split_pipes.c src/utils/split_quotes.c\
		src/utils/get_big_tab.c src/utils/path_access.c\
		\
		#src/exec_redir_out.c src/exec_redir_in.c \
		src/signals.c\
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
