# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: idakhlao <idakhlao@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/11/20 11:40:35 by idakhlao          #+#    #+#              #
#    Updated: 2024/11/12 10:54:57 by idakhlao         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a

SRCS = ft_isalpha.c ft_isdigit.c ft_isalnum.c ft_isascii.c \
		ft_isprint.c ft_strlen.c ft_memset.c ft_bzero.c ft_memcpy.c \
		ft_memmove.c ft_strlcpy.c ft_strlcat.c ft_strchr.c ft_strrchr.c \
		ft_strncmp.c ft_memchr.c ft_memcmp.c ft_strnstr.c ft_atoi.c \
		ft_calloc.c ft_strdup.c ft_substr.c ft_strjoin.c ft_strtrim.c \
		ft_toupper.c ft_tolower.c ft_putchar_fd.c \
		ft_putstr_fd.c ft_putnbr_fd.c ft_strmapi.c ft_striteri.c \
		ft_itoa.c ft_split.c ft_putendl_fd.c ft_lstadd_back_bonus.c ft_lstadd_front_bonus.c ft_lstclear_bonus.c \
		ft_lstdelone_bonus.c ft_lstlast_bonus.c ft_lstnew_bonus.c \
		ft_lstsize_bonus.c ft_lstmap_bonus.c ft_lstiter_bonus.c \
		get_next_line.c ft_strcmp.c ft_strjoin_gnl.c get_next_line_utils.c
		
OBJS = ${SRCS:.c=.o}

CC = cc

CFLAGS = -Wall -Werror -Wextra

RM = rm -f

all : $(NAME)

$(NAME) : $(OBJS)
	ar rc $(NAME) $(OBJS)

%.o : %.c 
	$(CC) $(CFLAGS) -c $< -o ${<:.c=.o}

clean :
	${RM} ${OBJS} 
	
fclean : clean
	${RM} ${NAME}

re : fclean all
