/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_redirections.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afrikach <afrikach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/04 15:34:50 by afrikach          #+#    #+#             */
/*   Updated: 2024/10/04 16:07:14 by afrikach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	get_redirection_start(char *s)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (!find_quotes(s, i) && (s[i] == '<' || s[i] == '>'))
		{
			if ((s[i + 1] == '<' && s[i] == '<')
				|| (s[i + 1] == '>' && s[i] == '>'))
				i += 2;
			else
				i++;
			while (s[i] && ft_isspace(s[i]))
				i++;
			while (s[i] && !ft_isspace(s[i]) && s[i] != '<' && s[i] != '>')
			{
				if (s[i] && s[i] == '\"')
					i++;
				else
					return (i);
			}
		}
		i++;
	}
	return (-1);
}

void	store_redir_symbols(t_input *input)
{
	int	i;
	int	j;

	i = 0;
	while (input[i].input)
	{
		j = 0;
		while (find_redirection(input[i].input, j) != -1)
		{
			if (input[i].input[j] == '<' && input[i].input[j + 1] == '<')
			{
				input[i].redir_infile = get_redir_type(input[i].input, j);
				j += 2;
			}
			else if (input[i].input[j] == '<')
			{
				input[i].redir_infile = get_redir_type(input[i].input, j);
				j++;
			}
			else
				j++;
		}
		i++;
	}
}

void	store_redir_symbols2(t_input *input)
{
	int	i;
	int	j;

	i = 0;
	while (input[i].input)
	{
		j = 0;
		while ((find_redirection(input[i].input, j)) != -1)
		{
			if (input[i].input[j] == '>' && input[i].input[j + 1] == '>')
			{
				input[i].redir_outfile = get_redir_type(input[i].input, j);
				j += 2;
			}
			else if (input[i].input[j] == '>')
			{
				input[i].redir_outfile = get_redir_type(input[i].input, j);
				j++;
			}
			else
				j++;
		}
		i++;
	}
}

void	store_redirection(t_input *input)
{
	int	i;
	int	j;

	i = 0;
	while (input[i].input)
	{
		input[i].in_file = NULL;
		j = 0;
		while (find_redirection(input[i].input, j) != -1)
		{
			j = find_redirection(input[i].input, j);
			if (input[i].input[j] == '<')
			{
				if (input[i].in_file != NULL)
					free(input[i].in_file);
				input[i].in_file = malloc(sizeof(char)
						* (get_redirection_length(&input[i].input[j]) + 1));
				ft_structcpy(input[i].in_file, &input[i].input[j],
					get_redirection_start(&input[i].input[j]));
				if (input[i].input[j + 1] == '<')
					j++;
			}
			j++;
		}
		i++;
	}
}

void	store_redirection2(t_input *input)
{
	int	i;
	int	j;

	i = 0;
	while (input[i].input)
	{
		input[i].out_file = NULL;
		j = 0;
		while (find_redirection(input[i].input, j) != -1)
		{
			j = find_redirection(input[i].input, j);
			if (input[i].input[j] == '>')
			{
				if (input[i].out_file != NULL)
					free(input[i].out_file);
				input[i].out_file = malloc(sizeof(char)
						* (get_redirection_length(&input[i].input[j]) + 1));
				ft_structcpy(input[i].out_file, &input[i].input[j],
					get_redirection_start(&input[i].input[j]));
				if (input[i].input[j + 1] == '>')
					j++;
			}
			j++;
		}
		i++;
	}
}