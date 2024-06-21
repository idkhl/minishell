/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: idakhlao <idakhlao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/10 12:30:24 by idakhlao          #+#    #+#             */
/*   Updated: 2024/06/21 13:14:17 by idakhlao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

static int	count_words(char *s, char c)
{
	int	count;
	int	i;

	count = 0;
	i = 0;
	while (s[i])
	{
		while (s[i] == c && s[i])
			i++;
		if (s[i] != c && s[i])
		{
			count++;
			i++;
		}
		while (s[i] != c && s[i])
			i++;
	}
	return (count);
}

char	**malloc_free(char	**tab)
{
	int	i;

	i = 0;
	if (!tab)
		return (NULL);
	while (tab[i])
	{
		// printf("%s\n\n\n\n\n", tab[i]);
		free(tab[i]);
		i++;
	}
	free(tab);
	tab = NULL;
	return (NULL);
}

static char	*malloc_word(char *s, char c)
{
	int		i;
	int		j;
	char	*word;

	i = 0;
	j = 0;
	while (s[i] != c && s[i])
		i++;
	word = (char *)malloc((i + 1) * sizeof(char));
	if (!word)
		return (NULL);
	while (j < i)
	{
		word[j++] = (char)*s++;
	}
	word[j] = '\0';
	return (word);
}

static char	**insert_words(char **words, char *s, char c)
{
	int	i;

	i = 0;
	while (*s)
	{
		while (*s && (char)*s == c)
			s++;
		if (*s && (char)*s != c)
		{
			words[i] = malloc_word(s, c);
			if (!words[i])
				return (malloc_free(words));
			i++;
		}
		while (*s && (char)*s != c)
			s++;
	}
	words[i] = NULL;
	return (words);
}

char	**ft_split( char *s, char c)
{
	int		count;
	char	**split;

	if (!s)
		return (NULL);
	count = count_words((char *)s, c);
	split = (char **)malloc((count + 1) * sizeof(char *));
	if (!split)
		return (NULL);
	split = insert_words(split, (char *)s, c);
	return (split);
}

/*char	*ft_strnew(size_t size)
{
	char	*temp;

	temp = malloc(sizeof(*temp) * (size + 1));
	if (!temp)
		return (NULL);
	if (temp)
		ft_bzero(temp, size + 1);
	return (temp);
}

size_t	wordcount(char*str, char c)
{
	size_t		i;
	size_t		count;

	i = 0;
	count = 0;
	while (str[i])
	{
		while (str[i] == c)
			i++;
		if (str[i] != c && str[i] != '\0')
			count++;
		while (str[i] != c && str[i] != '\0')
			i++;
	}
	return (count);
}

size_t	wordlen(char*str, char c)
{
	size_t		i;

	i = 0;
	while (str[i] == c)
		i++;
	while (str[i] != c && str[i] != '\0')
	{
		i++;
	}
	return (i);
}

char	**ft_split( char *s, char c)
{
	char	**str;
	size_t	i;
	size_t	j;
	size_t	k;

	str = (char **)malloc(sizeof(*str) * (wordcount(s, c) + 1));
	if (!s || !str)
		return (0);
	i = -1;
	j = 0;
	while (++i < wordcount(s, c))
	{
		k = 0;
		str[i] = ft_strnew(wordlen(&s[j], c) + 1);
		if (!str[i])
			str[i] = NULL;
		while (s[j] == c)
			j++;
		while (s[j] != c && s[j])
			str[i][k++] = s[j++];
		str[i][k] = '\0';
	}
	str[i] = 0;
	return (str);
}*/

/*char	**ft_split( char *s, char c)
{
	char	**str;
	size_t	i;
	size_t	j;
	size_t	k;
	
	str = (char **)malloc(sizeof(*str) * (wordcount(s, c) + 1));
	if (!str || !s)
		return (NULL);
	i = -1;
	j = 0;
	while (++i < wordcount(s, c))
	{
		k = 0;
		str[i] = ft_strnew(wordlen(&s[j], c) + 1);
		if (!str[i])
		{
			while (i >= 0)
				free(str[--i]);
			free(str);
			return (NULL);
		}
		while (s[j] == c)
			j++;
		while (s[j] != c && s[j])
			str[i][k++] = s[j++];
		str[i][k] = '\0';
	}
	str[i] = NULL;
	return (str);
}*/
/*{
		while (i <= size)
		{
			temp[i] = '\0';
			i++;
		}
	}*/

/*#include <stdlib.h>
#include <unistd.h>
#include "../includes/libft.h"

static void			ft_prsize_t_result(char*s)
{
	size_t		len;

	len = 0;
	while (s[len])
		len++;
	write(1, s, len);
}

static void			ft_prsize_t_tabstr(char **tabstr)
{
	size_t		i;

	i = 0;
	while (tabstr[i] != NULL)
	{
		ft_prsize_t_result(tabstr[i]);
		write(1, "\n", 1);
		free(tabstr[i]);
		i++;
	}
	free(tabstr);
}

static void			check_split(char *s, char c)
{
	char	**tabstr;

	if (!(tabstr = ft_split(s, c)))
		ft_prsize_t_result("NULL");
	else
		ft_prsize_t_tabstr(tabstr);
}

int					main(int argc,  char *argv[])
{
	int		arg;

	alarm(5);
	if (argc == 1)
		return (0);
	if ((arg = atoi(argv[1])) == 1)
		check_split("          ", ' ');
	else if (arg == 2)
		check_split("lorem ipsum dolor sit amet, consectetur adipiscing elit. 
		Sed non risus. Suspendisse", ' ');
	else if (arg == 3)
		check_split("   lorem   ipdsum dolor     sit amet, consectetur 
		adipiscing elit. Sed non risus. Suspendisse   ", ' ');
	else if (arg == 4)
		check_split("lorem ipsum dolor sit amet, consectetur adipiscing elit. 
		Sed non risus. Suspendisse lectus tortor, dignissim sit amet, adipiscing 
		nec, ultricies sed, dolor. Cras elementum ultricies diam. Maecenas ligula 
		massa, varius a, semper congue, euismod non, mi.", 'i');
	else if (arg == 5)
		check_split("lorem ipsum dolor sit amet, consectetur adipiscing elit. Sed
		 non risus. Suspendisse lectus tortor, dignissim sit amet, adipiscing nec, 
		 ultricies sed, dolor. Cras elementum ultricies diam. Maecenas ligula massa, 
		 varius a, semper congue, euismod non, mi.", 'z');
	return (0);
}*/
