/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: idakhlao <idakhlao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/10 09:44:10 by idakhlao          #+#    #+#             */
/*   Updated: 2024/10/19 17:20:21 by idakhlao         ###   ########.fr       */
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
