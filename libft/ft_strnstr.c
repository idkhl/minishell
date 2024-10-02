/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: idakhlao <idakhlao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/09 09:59:51 by idakhlao          #+#    #+#             */
/*   Updated: 2024/04/11 09:31:26 by idakhlao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

char	*ft_strnstr( char *big, char *little, size_t len)
{
	size_t	i;
	size_t	j;

	if (!big && len == 0)
		return (NULL);
	j = ft_strlen(little);
	if (j == 0)
		return ((char *)big);
	i = 0;
	while (*big && i < len)
	{
		if ((ft_strncmp((char *)big, (char *)little, j) == 0)
			&& i + j <= len)
		{
			return ((char *)big);
		}
		big++;
		i++;
	}
	return (0);
}

/*char	*ft_strnstr( char *big,  char *little, size_t len)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	if (big == NULL || little == NULL)
		return (NULL);
	if (little[i] == '\0')
		return ((char *)big);
	while (big[i] && i < len)
	{
		j = 0;
		while (big[i + j] == little[j])
		{
			j++;
			if (little[j] == '\0' || j >= len)
			{
				return ((char *)big + i);
			}
		}
		i++;
	}
	return (NULL);
}*/

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

static void		check_strnstr(char *big, char *little, int len)
{
	 char *str;

	if (!(str = ft_strnstr(big, little, len)))
		ft_print_result("NULL");
	else
		ft_print_result(str);
}

int				main(int argc,  char *argv[])
{
	int			arg;

	alarm(5);
	if (argc == 1)
		return (0);
	else if ((arg = atoi(argv[1])) == 1)
		check_strnstr("lorem ipsum dolor sit amet", "lorem", 15);
	else if (arg == 2)
		check_strnstr("lorem ipsum dolor sit amet", "ipsum", 15);
	else if (arg == 3)
		check_strnstr("lorem ipsum dolor sit lorem ipsum dolor", "ipsum", 35);
	else if (arg == 4)
		check_strnstr("lorem ipsum dolor sit amet", "", 10);
	else if (arg == 5)
		check_strnstr("lorem ipsum dolor sit amet", "ipsumm", 30);
	else if (arg == 6)
		check_strnstr("lorem ipsum dolor sit amet", "dol", 30);
	else if (arg == 7)
		check_strnstr("lorem ipsum dolor sit amet", "consectetur", 30);
	else if (arg == 8)
		check_strnstr("lorem ipsum dolor sit amet", "sit", 10);
	else if (arg == 9)
		check_strnstr("lorem ipsum dolor sit amet", "dolor", 15);
	else if (arg == 10)
		check_strnstr("lorem ipsum dolor sit amet", "dolor", 0);
	return (0);
}*/