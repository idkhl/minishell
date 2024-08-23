/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_quotes.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: idakhlao <idakhlao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/21 15:20:03 by idakhlao          #+#    #+#             */
/*   Updated: 2024/08/23 19:31:53 by idakhlao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	count_words(char *line, char c)
{
	int		size;
	int		i;
	int		in_quote;
	char	quote;

	size = 0;
	i = 0;
	while (line[i])
	{
		while (line[i] == c && line[i])
			i++;
		if (line[i] == 34 || line[i] == 39)
		{
			in_quote = 1;
			quote = line[i];
			i++;
		}
		size++;
		while ((line[i] != c || in_quote) && line[i])
		{
			if (in_quote && line[i] == quote)
			{
				in_quote = 0;
				i++;
				break ;
			}
			i++;
		}
	}
	return (size);
}

char	**insert_words(char **word, char *line, char c)
{
	int	i;
	int	j;
	int	in_quote;

	i = 0;
	j = 0;
	while (line[i])
	{
		while (line[i] == c && line[i])
			i++;
		if (line[i] == 34 || line[i] == 39)
		{
			in_quote = 1;
		}
	}
}

char	**split_quotes(char *line, char c)
{
	int		size;
	char	**split;

	size = count_words(line, c);
	split = (char **)malloc((size + 1) * sizeof(char *));
	if (!split)
		return (NULL);
	split = insert_words(split, line, c);
	return (ft_split(line, c));
}
