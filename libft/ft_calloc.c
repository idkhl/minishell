/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: idakhlao <idakhlao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/09 13:52:38 by idakhlao          #+#    #+#             */
/*   Updated: 2024/04/08 18:22:15 by idakhlao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"
#include <stdint.h>

void	*ft_calloc(size_t count, size_t size)
{
	void	*ptr;

	if (size > 0 && (SIZE_MAX / size) < count)
		return (NULL);
	ptr = malloc(count * size);
	if (ptr == NULL)
	{
		return (NULL);
	}
	ft_bzero(ptr, size * count);
	return (ptr);
}

/*#include <stdlib.h>
#include <unistd.h>
#include "../includes/libft.h"

int		main(int argc,  char *argv[])
{
	char	*str;

	alarm(5);
	if (argc == 1)
		return (0);
	else if (atoi(argv[1]) == 1)
	{
		str = (char *)ft_calloc(30, sizeof(char));
		if (!str)
			write(1, "NULL", 4);
		else
			write(1, str, 30);
		free(str);
	}
	return (0);
}
*/