/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_quotes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afrikach <afrikach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/21 15:50:34 by afrikach          #+#    #+#             */
/*   Updated: 2024/09/12 12:51:16 by afrikach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	empty_string(char *line)
{
	int i;

	i = 0;
	if (line[i] == '\0')
		return (1);
	return (0);
}
//fonction qui va checker s il y a uniquement des pipes, des redirections ou des /
int	no_word_string(char *line)
{
	int	i;
	int	redir;
	int	doc;
	int	slash;

	i = 0;
	redir = 1;
	doc = 1;
	slash = 0;
	while (line[i])
	{
		if (line[i] != '|' && line[i] != '<' && line[i] != '>' 
			&& line[i] != '&')
				redir = 0;
		if (line[i] == '/')
			slash = 1;
		if (slash && line[i] != '/' && line[i] != '.')
            doc = 0;
		i++;
	}
	if (redir && empty_string(line) == 0)
		return (printf("no word bash: syntax error near unexpected token\n"), 1);
	else if (doc && slash && empty_string(line) == 0)
		return (printf("bash: /: Is a directory\n"), 1);
	return (0);
}

int	check_quotes(char *line)
{
	int i;
	int simple_quote;
	int	double_quote;
	
	i = 0;
	simple_quote = 0;
	double_quote = 0;
	while (line[i])
	{
		if (line[i] == '\'' && double_quote == 0)
		{
			simple_quote = !simple_quote;
		}
		else if (line[i] == '"' && simple_quote == 0)
		{
			double_quote = !double_quote;
		}
		i++;
	}
	if (simple_quote || double_quote)
	{
		printf("bash: syntax error\n");
		return (1);
	}
	return (0);
}
int	check_syntax(char *line)
{
	if (no_word_string(line) == 1)
		return (1);
	if (check_quotes(line) == 1)
		return (1);
	if (check_open_operators(line) == 1)
		return (1);
	if (check_close_operators(line) == 1)
		return (1);
	if (check_begin_pipes(line) == 1)
		return (1);
	if (check_end_pipes(line) == 1)
		return (1);
	return (0);
}
