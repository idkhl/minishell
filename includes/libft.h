/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: idakhlao <idakhlao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 16:56:48 by idakhlao          #+#    #+#             */
/*   Updated: 2024/10/30 12:17:40 by idakhlao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <string.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <limits.h>

typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}	t_list;

int					ft_isalnum(int i);
int					ft_isalpha(int i);
int					ft_isascii(int i);
int					ft_isdigit(int i);
int					ft_tolower(int i);
int					ft_toupper(int i);
int					ft_isprint(int i);
void				*ft_memset(void *s, int c, size_t n);
void				ft_bzero(void *s, size_t n);
void				*ft_memcpy(void *dest, void *src, size_t n);
void				*ft_memmove(void *dest, void *src, size_t n);
size_t				ft_strlcpy(char *dest, char *src, size_t size);
size_t				ft_strlcat(char *dst, char *src, size_t size);
size_t				ft_strlen(char *str);
char				*ft_strchr(char *s, int c);
char				*ft_strrchr(char *s, int c);
int					ft_strcmp(char *s1, char *s2);
int					ft_strncmp(char *s1, char *s2, size_t n);
void				*ft_memchr(void *s, int c, size_t n);
int					ft_memcmp(void *s1, void *s2, size_t n);
char				*ft_strnstr(char *big, char *little, size_t len);
int					ft_atoi(char *str);
unsigned long long	ft_atoll(char *str);
void				*ft_calloc(size_t count, size_t size);
char				*ft_strdup(char *s);
char				*ft_substr(char *s, unsigned int start, size_t len);
char				*ft_strtrim(char *s1, char *set);
char				**ft_split(char *s, char c);
void				ft_putchar_fd(char c, int fd);
void				ft_putstr_fd(char *s, int fd);
void				ft_putnbr_fd(int nb, int fd);
char				*ft_strmapi(char *s, char (*f)(unsigned int, char));
void				ft_striteri(char *s, void (*f)(unsigned int, char *));
char				**ft_split(char *s, char c);
char				*ft_itoa(int n);
void				ft_putendl_fd(char *s, int fd);
char				*ft_strjoin(char *s1, char *s2);
char				*ft_strjoin_gnl(char *s1, char *s2);
char				**malloc_free(char	**tab);

t_list				*ft_lstnew(void *content);
void		ft_lstadd_front(t_list **lst, t_list *new);
t_list		*ft_lstlast(t_list *lst);
int			ft_lstsize(t_list *lst);
void		ft_lstdelone(t_list *lst, void (*del)(void *));
void		ft_lstadd_back(t_list **lst, t_list *new);
void		ft_lstclear(t_list **lst, void (*del)(void*));
t_list		*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *));
void		ft_lstiter(t_list *lst, void (*f)(void *));

int			found_newlines(char *all_read);
char		*ft_strcpy2(char *dest, char *src);
char		*ft_strncat(char *dest, char *src, int nb);

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 5
# endif

char		*get_next_line(int fd);
char		*ft_get_line(char *stash);
char		*ft_stash(char *stash);
char		*ft_read_and_stash(int fd, char *stash);

#endif