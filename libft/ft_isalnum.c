/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalnum.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: idakhlao <idakhlao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/03 17:00:57 by idakhlao          #+#    #+#             */
/*   Updated: 2024/03/18 10:56:38 by idakhlao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

int	ft_isalnum(int i)
{
	if (ft_isalpha(i) == 1 || ft_isdigit(i) == 1)
		return (1);
	return (0);
}
/*
#include <stdlib.h>
#include <unistd.h>
#include <ctype.h>

static void		ft_print_result(int n)
{
	if (n)
		write(1, "1", 1);
	else
		write(1, "0", 1);
}

static void		check_isalnum(int start, int end)
{
	while (start <= end)
	{
		ft_print_result(ft_isalnum(start));
		start++;
	}
}

int				main(int argc,  char *argv[])
{
	int		arg;

	alarm(5);
	if (argc == 1)
		return (0);
	else if ((arg = atoi(argv[1])) == 1)
		check_isalnum(0, 47);
	else if (arg == 2)
		check_isalnum('0', '9');
	else if (arg == 3)
		check_isalnum(58, 64);
	else if (arg == 4)
		check_isalnum('A', 'Z');
	else if (arg == 5)
		check_isalnum(91, 96);
	else if (arg == 6)
		check_isalnum('a', 'z');
	else if (arg == 7)
		check_isalnum(123, 127);
	return (0);
}*/