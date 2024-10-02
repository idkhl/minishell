/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: idakhlao <idakhlao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 15:21:23 by idakhlao          #+#    #+#             */
/*   Updated: 2024/06/04 15:22:05 by idakhlao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

char	*ft_strncat(char *dest, char *src, int nb)
{
	int		end_dest;
	int		i;

	i = 0;
	end_dest = ft_strlen(dest);
	while (i < nb && src[i] != '\0')
	{
		dest[end_dest + i] = src[i];
		i++;
	}
	dest[end_dest + i] = '\0';
	return (dest);
}

char	*ft_strcpy(char *dest, char *src)
{
	int		index;

	index = 0;
	while (src[index] != '\0')
	{
		dest[index] = src[index];
		index++;
	}
	dest[index] = '\0';
	return (dest);
}

int	found_newlines(char *all_read)
{
	int	i;

	i = 0;
	if (!all_read)
		return (0);
	while (all_read[i])
	{
		if (all_read[i] == '\n')
			return (1);
		i++;
	}
	return (0);
}
