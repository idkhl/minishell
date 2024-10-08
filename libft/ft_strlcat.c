/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: idakhlao <idakhlao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 18:03:10 by idakhlao          #+#    #+#             */
/*   Updated: 2024/04/11 09:31:08 by idakhlao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

size_t	ft_strlcat(char *dst, char *src, size_t size)
{
	size_t	i;
	size_t	d_len;
	size_t	s_len;

	s_len = ft_strlen(src);
	if (size == 0)
		return (s_len);
	i = 0;
	d_len = ft_strlen(dst);
	if (size < d_len + 1)
		return (size + s_len);
	if (size > d_len + 1)
	{
		while (src[i] != '\0' && d_len + 1 + i < size)
		{
			dst[d_len + i] = src[i];
			i++;
		}
	}
	dst[d_len + i] = '\0';
	return (d_len + s_len);
}

/*size_t	ft_strlcat(char *dst,  char *src, size_t size)
{
	size_t	i;
	size_t	j;
	size_t	dst_len;
	size_t	src_len;

	dst_len = 0;
	src_len = 0;
	while (src[src_len] != '\0')
		src_len++;
	while (dst[dst_len] != '\0')
		dst_len++;
	j = dst_len;
	i = 0;
	if (dst_len < size - 1 && size > 0)
	{
		while (src[i] && dst_len + i < size - 1)
		{
			dst[j++] = src[i++];
		}
		dst[j] = 0;
	}
	if (dst_len >= size)
		dst_len = size;
	return (dst_len + src_len);
}*/

//src_len = ft_strlen((char *)src);
	//dst_len = ft_strlen(dst);
/*
int	main()
{
	char *dst = " World";
	 char *src = "Hello";
	unsigned int i;
	i = (unsigned int)ft_strlcat(dst, src, 7);
	printf("%d\n", i);
	printf("dest --> %s\n", dst);
	printf("src -- > %s\n", src);
}*/