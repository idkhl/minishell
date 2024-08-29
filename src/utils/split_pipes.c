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
	int	size;
	int	i;

	size = 0;
	i = 0;
	while (line[i])
	{
        size++;
        while (line[i] && line[i] != '|')
		{
			if (line[i] == 34 || line[i] == 39)
			{
				char (quote) = line[i++];
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

char	*malloc_block(char *line, int *i)
{
	int		len;
	int 	start;
	char	*bloc;
	int		j;

	start = *i;
	j = 0;
	while (line[*i] && line[*i] != '|')
	{
		if (line[*i] == 34 || line[*i] == 39)
		{
			char quote = line[(*i)++];
			while (line[*i] && line[*i] != quote)
				(*i)++;
			if (line[*i])
				(*i)++;
		}
		else
			(*i)++;
	}
	len = *i - start;
	bloc = (char *)malloc(sizeof(char) * (len + 1));
	if (!bloc)
		return (NULL);
	while (j < len)
	{
		bloc[j] = line[start + j];
		j++;
	}
	bloc[len] = '\0';
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
	printf("%d\n", size);
	split = (char **)malloc((size + 1) * sizeof(char *));
	if (!split)
		return (NULL);
	split = add_blocks(split, line);
	for (int i = 0; split[i]; i++)
		printf("[%s]\n", split[i]);
	return (split);
}
