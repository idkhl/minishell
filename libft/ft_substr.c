/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: idakhlao <idakhlao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/10 09:44:10 by idakhlao          #+#    #+#             */
/*   Updated: 2024/09/06 16:37:47 by idakhlao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

char	*ft_substr(char*s, unsigned int start, size_t len)
{
	char	*sub;
	size_t	s_len;

	if (!s)
		return (NULL);
	if (ft_strlen(s) < start)
	{
		sub = ft_calloc(1, sizeof(char));
		if (!sub)
			return (NULL);
	}
	else
	{
		s_len = ft_strlen(s + start);
		if (!(s_len < len))
			s_len = len;
		sub = (char *)malloc((s_len + 1) * sizeof(char));
		if (!sub)
			return (NULL);
		sub[s_len] = 0;
		while (s_len-- > 0)
			sub[s_len] = s[start + s_len];
	}
	return (sub);
}

/*char	*ft_substr(char*s, unsigned int start, size_t len)
{
	size_t	i;
	size_t	j;
	char	*str;

	i = 0;
	j = 0;
	if (len > (s - start))
	{
		str = (char *)malloc(sizeof(*s) * (len + 1));
		if (!str)
			return (NULL);
		while (s[i])
		{
			if (i >= start && j < len)
			{
				str[j] = s[i];
				j++;
			}
			i++;
		}
		str[j] = 0;
		return (str);
	}
	else
		
}*/

#include <stdlib.h>
#include <unistd.h>

static void		ft_print_result(char*s)
{
	int		len;

	len = 0;
	while (s[len])
		len++;
	write(1, s, len);
}

static void		check_substr(char *str, int start, int len)
{
	char	*substr;

	if (!(substr = ft_substr(str, start, len)))
		ft_print_result("NULL");
	else
		ft_print_result(substr);
	if (str == substr)
		ft_print_result("\nA new string was not returned");
	else
		free(substr);
}

int				main(int argc,  char *argv[])
{
	char	str[] = "tripouille";
	int		arg;

	alarm(5);
	if (argc == 1)
		return (0);
	else if ((arg = atoi(argv[1])) == 1)
		check_substr(str, 0, 42000);
	else if (arg == 2)
		check_substr(str, 7, 10);
	else if (arg == 3)
		check_substr(str, 7, 0);
	else if (arg == 4)
		check_substr(str, 0, 0);
	return (0);
}