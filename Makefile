# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: idakhlao <idakhlao@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/09/16 15:38:17 by afrikach          #+#    #+#              #
#    Updated: 2024/11/14 10:58:48 by idakhlao         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

SRCS = src/prout.c src/signals.c src/pipes.c src/exec_cmd.c src/redir.c\
		\
		src/builtins/echo.c src/builtins/cd_pwd.c src/builtins/env.c src/builtins/exit.c src/builtins/pwd.c \
		src/builtins/export.c src/builtins/unset.c src/builtins/builtins.c\
		\
		src/utils/ft_tabdup.c src/utils/ft_tablen.c src/utils/split_pipes.c\
		src/utils/path_access.c src/utils/handle_len.c src/utils/free_all.c src/utils/heredoc.c\
		src/utils/builtins_utils.c src/utils/pipes_utils.c src/utils/redir_utils.c\
		\
		src/parsing/util.c src/parsing/syntax_quotes.c src/parsing/syntax_pipes.c \
		src/parsing/syntax_open_redir.c src/parsing/syntax_close_redir.c src/parsing/get_big_tab.c \
		src/parsing/fill_struct.c src/parsing/ft_structcpy.c src/parsing/fill_cmd.c src/parsing/is_expand.c\
		src/parsing/fill_redirections.c src/parsing/divide_input.c src/parsing/utils2.c src/parsing/expand.c\
	
OBJS_DIR = .objects
OBJS = $(addprefix $(OBJS_DIR)/, $(SRCS:.c=.o))

CFLAGS = -Wall -Wextra -Werror -g3 
LIBFT = ./libft/libft.a
CC = cc
RM = rm -f

$(OBJS_DIR):
	mkdir -p $(OBJS_DIR) $(OBJS_DIR)/src $(OBJS_DIR)/src/utils $(OBJS_DIR)/src/builtins $(OBJS_DIR)/src/parsing

all: $(NAME)

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
