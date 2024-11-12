/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afrikach <afrikach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 12:28:21 by inesdakhlao       #+#    #+#             */
/*   Updated: 2024/11/12 10:14:49 by afrikach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	next_check_redir(t_input *input, int i, t_data *data, t_redir redir)
{
	t_quote	quote;

	redir.j++;
	redir.file = add_to_input(input[i].tab[redir.j], data, &quote);
	redir.outfile = open(redir.file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (redir.outfile < 0)
		return (perror(redir.file), free(redir.file), 1);
	else
	{
		free(redir.file);
		close(redir.outfile);
	}
	return (0);
}

int	next_check_redir2(t_input *input, int i, t_data *data, t_redir redir)
{
	t_quote	quote;

	redir.j++;
	redir.file = add_to_input(input[i].tab[redir.j], data, &quote);
	redir.outfile = open(redir.file, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (redir.outfile < 0)
		return (perror(redir.file), free(redir.file), 1);
	else
	{
		free(redir.file);
		close(redir.outfile);
	}
	return (0);
}

int	next_check_redir3(t_input *input, int i, t_data *data, t_redir redir)
{
	t_quote	quote;

	redir.j++;
	redir.file = add_to_input(input[i].tab[redir.j], data, &quote);
	redir.infile = open(redir.file, O_RDONLY, 0644);
	if (redir.infile < 0)
		return (perror(redir.file), free(redir.file), 1);
	else
	{
		free(redir.file);
		close(redir.infile);
	}
	return (0);
}

int	next_check_redir4(t_input *input, int i, t_data *data, t_redir redir)
{
	t_quote	quote;

	redir.j++;
	redir.file = add_to_input(input[i].tab[redir.j], data, &quote);
	redir.infile = open(redir.file, O_RDONLY, 0644);
	if (redir.infile < 0)
		return (perror(redir.file), free(redir.file), 1);
	else
	{
		free(redir.file);
		close(redir.infile);
	}
	return (0);
}