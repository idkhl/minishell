/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: idakhlao <idakhlao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 17:57:54 by idakhlao          #+#    #+#             */
/*   Updated: 2024/04/11 09:31:14 by idakhlao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

size_t	ft_strlcpy(char *dest, char *src, size_t size)
{
	size_t	i;
	size_t	src_len;		

	i = 0;
	src_len = 0;
	while (src[src_len] != '\0')
		src_len++;
	if (size == 0)
		return (src_len);
	while (src[i] != '\0' && i < size - 1)
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
	return (src_len);
}
//src_len = ft_strlen((char *)src);
/*
int main()
{
	char dest[10];
	 char *src = "Hel";
	unsigned int i;
	i = (unsigned int)ft_strlcpy(dest, src, 5);
	printf("%d\n", i);
	printf("dest --> %s\n", dest);
	printf("src -- > %s\n", src);
}*/