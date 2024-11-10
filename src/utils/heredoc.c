/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: idakhlao <idakhlao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/17 11:21:48 by idakhlao          #+#    #+#             */
/*   Updated: 2024/11/10 16:01:54 by idakhlao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*temp_file(int i)
{
	char	*tmp;
	char	*file;
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
	return (file);
}

void	heredoc_loop(t_input *input, int i)
{
	char	*line;
	int j = 0;

	signal(SIGINT, heredoc_signals);
	signal(SIGQUIT, SIG_IGN);
	line = readline("> ");
	while (input[i].tab[j])
	{
		if (input[i].tab[j] && ft_strcmp(input[i].tab[j], "<<") == 0)
		{
			while (line)
			{
				if (g_signal == 130)
				{
					free(line);
					break ;
				}
				if (ft_strcmp(line, input[i].tab[j + 1]) == 0 || line == NULL)
				{
					free(line);
					break ;
				}
				write(input[i].heredoc, line, ft_strlen(line));
				write(input[i].heredoc, "\n", 1);
				free(line);
				line = readline("> ");
			}
			j = j + 2;
		}
		else
			j++;
	}
}

void	heredoc(t_input *input, int i)
{
	char	*file;

	file = temp_file(i);
	input[i].heredoc = open(file, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (input[i].heredoc == -1)
		return (free(file));
	heredoc_loop(input, i);
	// g_signal = 0;
	close(input[i].heredoc);
	signal(SIGINT, handle_signals);
	signal(SIGQUIT, SIG_IGN);
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
