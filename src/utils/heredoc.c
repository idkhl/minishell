/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afrikach <afrikach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/17 11:21:48 by idakhlao          #+#    #+#             */
/*   Updated: 2024/10/23 16:36:47 by afrikach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	heredoc(t_input *input, int i)
{
	char	*tmp;
	char	*file;
	char	*line;
	char	*nb;
	int		file_index;

	tmp = ft_strdup(".heredoc");
	file_index = i;
	nb = ft_itoa(i);
	file = ft_strjoin(tmp, nb);
	free(nb);
	while (access(file, F_OK) == 0)
	{
		free(file);
		nb = ft_itoa(++file_index);
		file = ft_strjoin(tmp, nb);
		free(nb);
	}
	free(tmp);
	input[i].heredoc = open(file, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (input[i].heredoc == -1)
		return (free(file));
	signal(SIGINT, heredoc_sigint);
	signal(SIGQUIT, SIG_IGN);
	line = readline("> ");
	while (line)
	{
		signal(SIGINT, heredoc_sigint);
		signal(SIGQUIT, heredoc_sigquit);
		if (ft_strcmp(line, input[i].in_file) == 0)
		{
			free(line);
			break ;
		}
		write(input[i].heredoc, line, ft_strlen(line));
		write(input[i].heredoc, "\n", 1);
		free(line);
		line = readline("> ");
	}
	close(input[i].heredoc);
	free(input[i].in_file);
	input[i].in_file = ft_strdup(file);
	free(file);
}

void	pipe_heredoc(t_data *data, t_input *input, int nb)
{
	int		i;

	i = 0;
	while (i < nb)
	{
		if (input[i].in_file)
		{
			if (ft_strcmp(input[i].redir_infile, "<<") == 0)
			{
				data->copy_stdin = dup(STDIN_FILENO);
				data->copy_stdout = dup(STDOUT_FILENO);
				heredoc(input, i);
				dup2(data->copy_stdin, STDIN_FILENO);
				dup2(data->copy_stdout, STDOUT_FILENO);
				close(data->copy_stdin);
				close(data->copy_stdout);
			}
		}
		i++;
	}
}