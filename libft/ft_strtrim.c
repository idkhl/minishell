/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: idakhlao <idakhlao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/10 11:48:40 by idakhlao          #+#    #+#             */
/*   Updated: 2024/03/18 10:59:35 by idakhlao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

char	*ft_strtrim(char*s1, char*set)
{
	size_t	i;
	size_t	j;
	char	*str;

	str = 0;
	if (s1 != 0 && set != 0)
	{
		i = 0;
		j = ft_strlen(s1);
		while (s1[i] && ft_strchr(set, s1[i]))
			i++;
		while (s1[j - 1] && ft_strchr(set, s1[j - 1]) && j > i)
			j--;
		str = (char *)malloc(sizeof(char) * (j - i + 1));
		if (!str)
			return (NULL);
		else
			ft_strlcpy(str, &s1[i], j - i + 1);
	}
	return (str);
}

/*#include <stdlib.h>
#include <unistd.h>

static void		ft_print_result(char*s)
{
	int		len;

	len = 0;
	while (s[len])
		len++;
	write(1, s, len);
}

static void		check_strtrim(char *s1, char *set)
{
	char	*strtrim;

	if (!(strtrim = ft_strtrim(s1, set)))
		ft_print_result("NULL");
	else
		ft_print_result(strtrim);
	if (strtrim == s1)
		ft_print_result("\nA new string was not returned");
	else
		free(strtrim);
}

int				main(int argc,  char *argv[])
{
	char	set [] = "lorem";
	int		arg;

	alarm(5);
	if (argc == 1)
		return (0);
	else if ((arg = atoi(argv[1])) == 1)
	{
		char s1[] = "cyvgyeqgvf166562356jfvbevfbgvyb";
		check_strtrim(s1, set);
	}
	else if (arg == 2)
	{
		char s1[] = "lorem ipsum dolor sit amet \n \t ";
		check_strtrim(s1, set);
	}
	else if (arg == 3)
	{
		char s1[] = " \n \t lorem ipsum dolor sit amet rem";
		check_strtrim(s1, set);
	}
	else if (arg == 4)
	{
		char s1[] = "  \n  \t  lorem \n ipsum \t dolor \n sit \t amet  \t \n ";
		check_strtrim(s1, set);
	}
	else if (arg == 5)
	{
		char s1[] = "          ";
		check_strtrim(s1, set);
	}
	return (0);
}*/