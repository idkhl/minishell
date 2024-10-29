/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_pipes.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afrikach <afrikach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/27 12:45:48 by afrikach          #+#    #+#             */
/*   Updated: 2024/10/29 11:29:43 by afrikach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static	void	ignore_spaces(char *line, int *i)
{
	while (line[*i] == ' ' || line[*i] == '\t')
		(*i)++;
}

int	handle_quotes(char *line, int *i, int *quotes, char *quote_char)
{
	if ((line[*i] == '\'' || line[*i] == '\"')
		&& (!(*quotes) || *quote_char == line[*i]))
	{
		if (*quotes && *quote_char == line[*i])
			*quotes = 0;
		else
		{
			*quote_char = line[*i];
			*quotes = 1;
		}
		(*i)++;
		return (1);
	}
	return (0);
}

int	check_begin_pipes(char *line)
{
	t_pipe	pipe;

	ft_bzero(&pipe, sizeof(t_pipe));
	while ((size_t)pipe.i < ft_strlen(line) && line[pipe.i])
	{
		ignore_spaces(line, &pipe.i);
		handle_quotes(line, &pipe.i, &pipe.quotes, &pipe.quote_char);
		if (line[pipe.i] == '|' && !pipe.quotes)
		{
			if (pipe.word == 0)
			{
				printf("bash: syntax error near unexpected token '|'\n");
				return (1);
			}
			pipe.word = 0;
		}
		else if (line[pipe.i] != ' '
			&& line[pipe.i] != '\t' && line[pipe.i] != '|')
			pipe.word = 1;
		pipe.i++;
	}
	return (0);
}

int	check_end_pipes(char *line)
{
	int	i;

	i = 0;
	while (line[i])
	{
		while (line[i] == ' ' || line[i] == '\t')
			i++;
		if (line[i] == '|')
		{
			while (line[i]
				&& (line[i] == ' ' || line[i] == '\t' || line[i] == '|'))
				i++;
			if (line[i] == '\0')
				return (printf("bash: syntax error\n"), 1);
		}
		else if (line[i] != '\0')
		i++;
	}
	return (0);
}

int	check_nb_pipes(char *line)
{
	int	i;
	int	pipe;

	i = 0;
	pipe = 0;
	while (line[i])
	{
		if (line[i] == '|')
		{
			pipe++;
		}
		i++;
	}
	return (pipe);
}
