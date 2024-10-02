/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_struct.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afrikach <afrikach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/13 15:19:09 by afrikach          #+#    #+#             */
/*   Updated: 2024/10/02 11:00:55 by afrikach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	find_quotes(char *s, int index)
{
	int simple_quote;
	int	double_quote;
	int i;
	
	i = 0;
	simple_quote = 0;
	double_quote = 0;
	while (i < index)
	{
		if (s[i] == '\'' && !double_quote)
			simple_quote = !simple_quote;
		else if (s[i] == '\"' && !simple_quote)
			double_quote = !double_quote;
		i++;
	}
	if (simple_quote || double_quote)
		return (1);
	return (0);
}

int get_redirection_length(char *s) 
{
    int i;
    int length;

	i = 0;
	length = 0;
    while (s[i])
	{
        if (!find_quotes(s, i) && (s[i] == '<' || s[i] == '>'))
		{
			if ((s[i + 1] == '<' && s[i] == '<') || (s[i + 1] == '>' && s[i] == '>'))
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
				{
					length++;
					i++;
				}
			}
			return (length);
		}
		i++;
	}
	return 0;
}

int		find_redirection(char *s, int i)
{
	while (s[i])
	{
		if (!find_quotes(s, i) && (s[i] == '<' || s[i] == '>'))
			return (i);
		i++;
	}
	return (-1);
}
char	*get_redir_type(char *s, int index)
{
	if (s[index] == '<')
	{
        if (s[index + 1] == '<')
            return ft_strdup("<<");
        else
            return ft_strdup("<");
    } 
	else if (s[index] == '>')
	{
        if (s[index + 1] == '>')
            return ft_strdup(">>");
        else
            return ft_strdup(">");
    }
    return (NULL);
}
int get_redirection_start(char *s)
{
    int i;

	i = 0;
    while (s[i])
	{
        if (!find_quotes(s, i) && (s[i] == '<' || s[i] == '>'))
		{
			if ((s[i + 1] == '<' && s[i] == '<') || (s[i + 1] == '>' && s[i] == '>'))
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
					return(i);
			}
		}
		i++;
	}
	return (-1);
}
void	store_redir_symbols(t_input *input)
{
	int i;
	int j;

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
	int i;
	int j;

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
	int i;
	int j;

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
				input[i].in_file = malloc(sizeof(char) * (get_redirection_length(&input[i].input[j]) + 1));
				ft_structcpy(input[i].in_file, &input[i].input[j], get_redirection_start(&input[i].input[j]));
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
				input[i].out_file = malloc(sizeof(char) * (get_redirection_length(&input[i].input[j]) + 1));
				ft_structcpy(input[i].out_file, &input[i].input[j], get_redirection_start(&input[i].input[j]));
				if (input[i].input[j + 1] == '>')
					j++;
			}
			j++;
		}
		i++;
	}
}

void	fill_struct(t_input *input, char *line)
{
		fill_input(input, line);
		fill_cmd(input);
		store_redir_symbols(input);
		store_redir_symbols2(input);
		store_redirection(input);
		store_redirection2(input);
		// printf("infile : %s, symbole : %s\n", input[0].in_file, input[0].redir_infile);
		// printf("cmd : %s\n", input[0].cmd[0]);
}

