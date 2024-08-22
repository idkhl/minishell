/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_quotes.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: idakhlao <idakhlao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/21 15:20:03 by idakhlao          #+#    #+#             */
/*   Updated: 2024/08/22 19:20:00 by idakhlao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	count_words(char *line, char c)
{
	int		size;
	int		i;
	// char	j;

	size = 0;
	i = 0;
	while (line[i])
	{
		if (line[i] == 34 || line[i] == 39)
		{
			i++;
			size++;
			while (line[i] != 34 && line[i] != 39)
				i++;
			printf("[%c]\n", line[i]);
			printf("i = %d\n", i);
		}
		i++;
		while (line[i] == c && line[i])
			i++;
		if (line[i] != c && line[i])
		{
			size++;
			i++;
		}
		while (line[i] != c && line[i])
			i++;
	}
	return (size);
}

char	**split_quotes(char *line, char c)
{
	int	size;

	size = count_words(line, c);
	printf("%d\n", size);
	return (ft_split(line, c));
}
