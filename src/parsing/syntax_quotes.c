/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_quotes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afrikach <afrikach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/21 15:50:34 by afrikach          #+#    #+#             */
/*   Updated: 2024/11/14 10:28:00 by afrikach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	empty_string(char *line, t_data *data)
{
	int	i;

	i = 0;
	if (line[i] == '\0')
		return (1);
	while (ft_isspace(line[i]))
		i++;
	if (line[i] == '!' && (ft_isspace(line[i + 1]) || line[i + 1] == '\0'))
	{
		data->exit_status = 1;
		return (1);
	}
	if (line[i] == ':' && (ft_isspace(line[i + 1]) || line[i + 1] == '\0'))
	{
		data->exit_status = 2;
		return (1);
	}
	return (0);
}

int	no_word_string(char *line, t_data *data)
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
		i++;
	}
	if (redir && empty_string(line, data) == 0)
	{
		data->exit_status = 2;
		return (printf("bash: syntax error near unexpected token\n"), 1);
	}
	return (0);
}

int	check_quotes(char *line, t_data *data)
{
	int	i;
	int	simple_quote;
	int	double_quote;

	i = 0;
	simple_quote = 0;
	double_quote = 0;
	while (line[i])
	{
		if (line[i] == '\'' && double_quote == 0)
			simple_quote = !simple_quote;
		else if (line[i] == '"' && simple_quote == 0)
			double_quote = !double_quote;
		i++;
	}
	if (simple_quote || double_quote)
	{
		data->exit_status = 2;
		printf("bash: syntax error\n");
		return (1);
	}
	return (0);
}

int	check_syntax(char *line, t_data *data)
{
	if (empty_string(line, data) == 1)
		return (1);
	if (no_word_string(line, data) == 1)
		return (1);
	if (check_quotes(line, data) == 1)
		return (1);
	if (check_open_operators(line, data) == 1)
		return (1);
	if (check_close_operators(line, data) == 1)
		return (1);
	if (check_begin_pipes(line, data) == 1)
		return (1);
	if (check_end_pipes(line, data) == 1)
		return (1);
	return (0);
}
