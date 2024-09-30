/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: idakhlao <idakhlao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 12:28:21 by inesdakhlao       #+#    #+#             */
/*   Updated: 2024/09/30 15:50:14 by idakhlao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	here_doc(t_data *data, t_input *input, int i)
{
	char	*line;

	line = readline("> ");
	data->heredoc = open(".tmp_doc", O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (data->heredoc == -1)
		return ;
	while (line)
	{
		// heredoc_signals();
		if (ft_strcmp(line, input[i].in_file) == 0)
		{
			free(line);
			break ;
		}
		write(data->heredoc, line, ft_strlen(line));
		write(data->heredoc, "\n", 1); 
		free(line);
		line = readline("> ");
	}
	close(data->heredoc);
}

void	input_redir(t_data *data, t_input *input, int i)
{
	int	infile;
	int	heredoc_infile;

	if (ft_strcmp(input[i].redir_infile, "<") == 0)
	{
		infile = open(input[i].in_file, O_RDONLY, 0644);
		if (infile < 0)
			return (perror("Open"));
		if (dup2(infile, STDIN_FILENO) == -1)
			return (close(infile), perror("dup2"));
		close(infile);
	}
	else if (ft_strcmp(input[i].redir_infile, "<<") == 0)
	{
		here_doc(data, input, i);
		heredoc_infile = open(".tmp_doc", O_RDONLY);
		if (heredoc_infile < 0)
			return (perror("heredoc read open"));
		if (dup2(heredoc_infile, STDIN_FILENO) == -1)
			return (close(heredoc_infile), perror("dup2"));
		close(heredoc_infile);
		unlink(".tmp_doc");
	}
	// printf("[[[%d]]]\n\n", i);
}

void	redir(t_data *data, t_input *input, int i)
{
	int	outfile;

	if (input[i].in_file != NULL)
		input_redir(data, input, i);
	if (input[i].out_file != NULL)
	{
		if (ft_strcmp(input[i].redir_infile, "<") == 0)
		outfile = open(input[i].out_file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		if (ft_strcmp(input[i].redir_infile, "<<") == 0)
			outfile = open(input[i].out_file, O_WRONLY | O_CREAT | O_APPEND, 0644);
		if (outfile < 0)
			return (perror("Open"));
		if (dup2(outfile, STDOUT_FILENO) == -1)
			return (close(outfile), perror("dup2"));
		close(outfile);
	}
}
