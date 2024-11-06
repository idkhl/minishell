/* ************************************************************************** */
/*                                                                          */
/*                                                        :::      ::::::::   */
/*   split_pipes.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: idakhlao <idakhlao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/27 19:23:30 by idakhlao          #+#    #+#             */
/*   Updated: 2024/08/28 18:37:12 by idakhlao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	count_blocks(char *line)
{
	int		i;
	char	quote;

	i = 0;
	int (size) = 0;
	while (line[i])
	{
		size++;
		while (line[i] && line[i] != '|')
		{
			if (line[i] == 34 || line[i] == 39)
			{
				quote = line[i++];
				while (line[i] && line[i] != quote)
					i++;
				if (line[i])
					i++;
			}
			else
				i++;
		}
		while (line[i] == '|')
			i++;
	}
	return (size);
}

char	*initialize_block(char *line, int start, int len)
{
	char	*bloc;
	int		j;

	bloc = (char *)malloc(sizeof(char) * (len + 1));
	if (!bloc)
		return (NULL);
	j = 0;
	while (j < len)
	{
		bloc[j] = line[start + j];
		j++;
	}
	bloc[len] = '\0';
	return (bloc);
}

char	*malloc_block(char *line, int *i)
{
	int		len;
	int		start;
	char	quote;
	char	*bloc;

	start = *i;
	while (line[*i] && line[*i] != '|')
	{
		if (line[*i] == 34 || line[*i] == 39)
		{
			quote = line[(*i)++];
			while (line[*i] && line[*i] != quote)
				(*i)++;
			if (line[*i])
				(*i)++;
		}
		else
			(*i)++;
	}
	len = *i - start;
	bloc = initialize_block(line, start, len);
	while (line[*i] == '|')
		(*i)++;
	return (bloc);
}

char	**add_blocks(char **bloc, char *line)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (line[i])
	{
		bloc[j] = malloc_block(line, &i);
		if (!bloc[j])
			return (NULL);
		j++;
	}
	bloc[j] = NULL;
	return (bloc);
}

char	**split_pipes(char *line)
{
	int		size;
	char	**split;

	if (!line)
		return (NULL);
	size = count_blocks(line);
	split = (char **)malloc((size + 1) * sizeof(char *));
	if (!split)
		return (NULL);
	split = add_blocks(split, line);
	if (!split)
	{
		malloc_free(split);
		return (NULL);
	}
	return (split);
}
