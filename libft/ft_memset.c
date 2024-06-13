/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: idakhlao <idakhlao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/03 17:33:50 by idakhlao          #+#    #+#             */
/*   Updated: 2024/03/16 12:09:50 by idakhlao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

void	*ft_memset(void *s, int c, size_t n)
{
	size_t			i;
	unsigned char	*str;

	i = 0;
	str = (unsigned char *)s;
	while (i < n)
	{
		*str++ = (unsigned char)c;
		i++;
	}
	return (s);
}

/*
int main()
{
	char stp[] = "1234567";
	ft_memset(stp, 84, 6);
	puts(stp);
	return (0);
}*/