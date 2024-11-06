/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afrikach <afrikach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 12:28:21 by inesdakhlao       #+#    #+#             */
/*   Updated: 2024/11/06 11:57:28 by afrikach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	do_redir(t_data *data, t_input *input)
{
	data->copy_stdin = dup(STDIN_FILENO);
	data->copy_stdout = dup(STDOUT_FILENO);
	if (input[0].in_file != NULL || input[0].out_file != NULL)
		redir(input, 0);
	exec_builtins(data, input, input->cmd);
	dup2(data->copy_stdin, STDIN_FILENO);
	dup2(data->copy_stdout, STDOUT_FILENO);
	close(data->copy_stdin);
	close(data->copy_stdout);
}

void	unlink_heredoc(t_input *input, int nb)
{
	int		i;

	i = 0;
	while (i < nb)
	{
		if (input[i].in_file && ft_strcmp(input[i].redir_infile, "<<") == 0)
			unlink(input[i].in_file);
		i++;
	}
}

void	input_redir(t_input *input, int i)
{
	int	infile;

	if (input[i].redir_infile && ft_strncmp(input[i].redir_infile, "<", 1) == 0)
	{
		infile = open(input[i].in_file, O_RDONLY, 0644);
		if (infile < 0)
			return (perror(input[i].in_file), exit(1));
		if (dup2(infile, STDIN_FILENO) == -1)
			return (close(infile), perror("dup2"));
		close(infile);
	}
}

void	check_redir(t_input *input, int i)
{
	int	j;
	int	infile;

	j = 0;
	while (input[i].tab[j] && j < get_tab_len(input[i].input))
	{
		if (input[i].tab[j]
			&& (ft_strcmp(input[i].tab[j], "<") == 0
				|| ft_strcmp(input[i].tab[j], ">") == 0
				|| ft_strcmp(input[i].tab[j], ">>") == 0))
		{
			infile = open(input[i].tab[j + 1], O_RDONLY, 0644);
			if (infile < 0)
			{
				printf("HEEEERE\n");
				return (perror(input[i].tab[j + 1]));
			}
			else
				close(infile);
		}
		j++;
	}
}

void	redir(t_input *input, int i)
{
	int	outfile;

	check_redir(input, i);
	if (input[i].in_file != NULL)
		input_redir(input, i);
	if (input[i].out_file != NULL)
	{
		if (ft_strcmp(input[i].redir_outfile, ">") == 0)
		outfile = open(input[i].out_file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		if (ft_strcmp(input[i].redir_outfile, ">>") == 0)
			outfile = open(input[i].out_file, \
				O_WRONLY | O_CREAT | O_APPEND, 0644);
		if (outfile < 0)
			return (perror("Open"));
		if (dup2(outfile, STDOUT_FILENO) == -1)
			return (close(outfile), perror("dup2"));
		close(outfile);
	}
}
