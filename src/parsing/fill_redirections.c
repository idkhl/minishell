/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_redirections.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afrikach <afrikach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/04 15:34:50 by afrikach          #+#    #+#             */
/*   Updated: 2024/10/15 14:11:58 by afrikach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	store_redirection(t_input *input)
{
	int	i;
	int	j;

	i = 0;
	while (input[i].tab)
	{
		j = 0;
		while (input[i].tab[j])
		{
			if (ft_strcmp(input[i].tab[j], "<<") == 0)
			{
				if (input[i].in_file)
					free(input[i].in_file);
				input[i].in_file = ft_strdup(input[i].tab[j +1]);
			}
			else if (ft_strcmp(input[i].tab[j], ">>") == 0)
			{
				if (input[i].out_file)
					free(input[i].out_file);
				input[i].out_file = ft_strdup(input[i].tab[j +1]);
			}
			else if (ft_strcmp(input[i].tab[j], "<") == 0)
			{
				if (input[i].in_file)
					free(input[i].in_file);
				input[i].in_file = ft_strdup(input[i].tab[j +1]);
			}
			else if (ft_strcmp(input[i].tab[j], ">") == 0)
			{
				if (input[i].out_file)
					free(input[i].out_file);
				input[i].out_file = ft_strdup(input[i].tab[j +1]);
			}
			j++;
		}
		i++;
	}
}

int	find_redirection(char *s, int i)
{
	while (s[i])
	{
		if (!find_quotes(s, i) && (s[i] == '<' || s[i] == '>'))
			return (i);
		i++;
	}
	return (-1);
}

void	store_redir_symbols(t_input *input)
{
	int	i;
	int	j;

	i = 0;
	while (input[i].tab)
	{
		j = 0;
		while (input[i].tab[j])
		{
			if (ft_strcmp(input[i].tab[j], "<<") == 0)
			{
				if (input[i].redir_infile)
					free(input[i].redir_infile);
				input[i].redir_infile = ft_strdup("<<");
			}
			else if (ft_strcmp(input[i].tab[j], ">>") == 0)
			{
				if (input[i].redir_outfile)
					free(input[i].redir_outfile);
				input[i].redir_outfile = ft_strdup(">>");
			}
			else if (ft_strcmp(input[i].tab[j], "<") == 0)
			{
				if (input[i].redir_infile)
					free(input[i].redir_infile);
				input[i].redir_infile = ft_strdup("<");
			}
			else if (ft_strcmp(input[i].tab[j], ">") == 0)
			{
				if (input[i].redir_outfile)
					free(input[i].redir_outfile);
				input[i].redir_outfile = ft_strdup(">");
			}
			j++;
		}
		i++;
	}
}

char	*get_redir_type(char *s, int index)
{
	if (s[index] == '<')
	{
		if (s[index + 1] == '<')
			return (ft_strdup("<<"));
		else
			return (ft_strdup("<"));
	}
	else if (s[index] == '>')
	{
		if (s[index + 1] == '>')
			return (ft_strdup(">>"));
		else
			return (ft_strdup(">"));
	}
	return (NULL);
}

// TO DO LIST

// STOCKER LES COMMANDES si c pas une redir ou le + 1 d'une redir on part du principe aue c une cmd
// CODER L EXPAND si les premieres quotes ouvrante ne sont pas des simple alors expand



//// jinka ////

// int	get_redirection_start(char *s)
// {
// 	int	i;

// 	i = 0;
// 	while (s[i])
// 	{
// 		if (!find_quotes(s, i) && (s[i] == '<' || s[i] == '>'))
// 		{
// 			if ((s[i + 1] == '<' && s[i] == '<')
// 				|| (s[i + 1] == '>' && s[i] == '>'))
// 				i += 2;
// 			else
// 				i++;
// 			while (s[i] && ft_isspace(s[i]))
// 				i++;
// 			while (s[i] && !ft_isspace(s[i]) && s[i] != '<' && s[i] != '>')
// 			{
// 				if (s[i] && s[i] == '\"')
// 					i++;
// 				else
// 					return (i);
// 			}
// 		}
// 		i++;
// 	}
// 	return (-1);
// }
