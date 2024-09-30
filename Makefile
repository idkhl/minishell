# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: inesdakhlaoui <inesdakhlaoui@student.42    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/07/05 14:53:25 by idakhlao          #+#    #+#              #
#    Updated: 2024/09/11 11:52:17 by inesdakhlao      ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

SRCS = src/prout.c src/pipes.c src/exec_cmd.c src/redir.c \
		src/signals.c\
		\
		src/builtins/echo.c src/builtins/cd_pwd.c src/builtins/env.c src/builtins/exit.c\
		src/builtins/export.c src/builtins/unset.c src/builtins/builtins.c\
		\
		src/utils/ft_tabdup.c src/utils/ft_tablen.c src/utils/split_pipes.c src/utils/split_quotes.c\
		src/utils/get_big_tab.c src/utils/path_access.c\
		\
		#src/exec_redir_out.c src/exec_redir_in.c \
		src/expand.c 

OBJS_DIR = .objects
OBJS = $(addprefix $(OBJS_DIR)/, $(SRCS:.c=.o))

CFLAGS = -Wall -Wextra -Werror -g3 
LIBFT = ./libft/libft.a
CC = cc
RM = rm -f

all: $(NAME)

$(OBJS_DIR):
	mkdir -p $(OBJS_DIR)

$(OBJS_DIR)/%.o: %.c | $(OBJS_DIR)
	$(CC) $(CFLAGS) -c -o $@ $<

$(NAME): $(OBJS)
	make -C libft all
	$(CC) $(CFLAGS) $(OBJS) -lreadline -o $(NAME) $(LIBFT)

clean:
	$(RM) $(OBJS) $(LIBFT_OBJS)
	make -C libft clean
	find $(OBJS_DIR) -type f -name "*.o" -delete

fclean: clean
	$(RM) $(NAME)
	make -C libft fclean


ac: all clean
	make clean
	make -C libft clean

re: fclean all

.PHONY: all clean fclean re
