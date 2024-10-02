/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_quotes.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: idakhlao <idakhlao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/21 15:20:03 by idakhlao          #+#    #+#             */
/*   Updated: 2024/08/30 17:12:16 by idakhlao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	count_words(char *line, char c)
{
	int		i;
	char	quote;

	int (size) = 0;
	i = 0;
	int (in_quote) = 0;
	while (line[i])
	{
		while (line[i] == c && line[i])
			i++;
		if (line[i] == 34 || line[i] == 39)
		{
			in_quote = 1;
			quote = line[i++];
		}
		if (line[i])
			size++;
		while (line[i] && (in_quote || line[i] != c))
		{
			if (in_quote && line[i] == quote)
				in_quote = 0;
			i++;
		}
	}
	return (size);
}

char	*double_quote(char *line, char quote, int i)
{
	char	*word;
	int		start;
	int		len;
	int		j;

	start = i;
	len = 0;
	j = 0;
	while (line[i] != quote && line[i])
	{
		len++;
		i++;
	}
	word = (char *)malloc((len + 1) * sizeof(char));
	if (!word)
		return (NULL);
	while (j < len)
	{
		word[j] = line[start + j];
		j++;
	}
	word[len] = '\0';
	return (word);
}

char	*single_quote(char *line, char quote, int i)
{
	char	*word;
	int		start;
	int		len;
	int		j;

	start = i;
	len = 0;
	j = 0;
	while (line[i] != quote && line[i])
	{
		len++;
		i++;
	}
	len = len + 2;
	start--;
	word = (char *)malloc((len + 1) * sizeof(char));
	if (!word)
		return (NULL);
	while (j < len)
	{
		word[j] = line[start + j];
		j++;
	}
	word[len] = '\0';
	return (word);
}

char	*malloc_quote(char *line, char quote, int i)
{
	char	*word;

	if (quote == 34)
		word = double_quote(line, quote, i);
	else
		word = single_quote(line, quote, i);
	return (word);
}

char	*malloc_word(char *line, char c, int i)
{
	char	*word;
	int		start;
	int		len;
	int		j;

	start = i;
	len = 0;
	j = 0;
	while (line[i] && line[i] != c)
	{
		len++;
		i++;
	}
	word = (char *)malloc((len + 1) * sizeof(char));
	if (!word)
		return (NULL);
	while (j < len)
	{
		word[j] = line[start + j];
		j++;
	}
	word[len] = '\0';
	return (word);
}

char	**insert_words(char **word, char *line, char c)
{
	int		i;
	int		j;
	char	quote;

	i = 0;
	j = 0;
	while (line[i])
	{
		while (line[i] == c && line[i])
			i++;
		if (line[i] == 34 || line[i] == 39)
		{
			quote = line[i];
			i++;
			word[j] = malloc_quote(line, quote, i);
			if (!word[j])
				return (malloc_free(word));
			j++;
			while (line[i] && line[i] != quote)
				i++;
			if (line[i] == quote)
				i++;
		}
		else if (line[i])
		{
			word[j] = malloc_word(line, c, i);
			if (!word[j])
				return (malloc_free(word));
			j++;
			while (line[i] && line[i] != c)
				i++;
		}
	}
	word[j] = NULL;
	return (word);
}

char	**split_quotes(char *line, char c)
{
	int		size;
	char	**split;

	if (!line)
		return (NULL);
	size = count_words(line, c);
	split = (char **)malloc((size + 1) * sizeof(char *));
	if (!split)
		return (NULL);
	split = insert_words(split, line, c);
	return (split);
}
