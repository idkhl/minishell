/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_open_redir.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afrikach <afrikach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/29 13:00:37 by afrikach          #+#    #+#             */
/*   Updated: 2024/11/12 12:54:24 by afrikach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static	void	skip_spaces(char *line, int *i)
{
	while (line[*i] == ' ' || line[*i] == '\t')
		(*i)++;
}

static	int	end_of_open_operators(char *line, int *i, int *word, t_data *data)
{
	if (line[*i + 1] == '<')
		(*i)++;
	(*i)++;
	skip_spaces(line, i);
	if (line[*i] == '\0' || line[*i] == '<')
	{
		data->exit_status = 2;
		printf("EXIT STATUS =>%d\n", data->exit_status);
		printf("bash: syntax error near unexpected token 'newline'\n");
		return (1);
	}
	*word = 0;
	return (0);
}

int	check_open_operators(char *line, t_data *data)
{
	int	i;
	int	word;

	i = 0;
	word = 0;
	while ((size_t)i < ft_strlen(line) && line[i])
	{
		skip_spaces(line, &i);
		if (line[i] == '<')
		{
			if (end_of_open_operators(line, &i, &word, data))
				return (1);
		}
		else if (line[i] != ' ' && line[i] != '\t' && line[i] != '<')
			word = 1;
		i++;
	}
	return (0);
}
