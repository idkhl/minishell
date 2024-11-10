/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: idakhlao <idakhlao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/17 11:21:48 by idakhlao          #+#    #+#             */
/*   Updated: 2024/11/10 21:34:54 by idakhlao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*temp_file()
{
	char	*tmp;
	char	*file;
	char	*nb;
	int		file_index;

	tmp = ft_strdup(".heredoc");
	file_index = 0;
	nb = ft_itoa(file_index);
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

void	add_temp_file(t_data *data, char *filename)
{
	char	**new_files;
	int		i;

	if (!data->temp_files)
	{
		data->temp_files = malloc(sizeof(char *) * 2);
		if (!data->temp_files)
			return ;
		data->temp_files[0] = ft_strdup(filename);
		data->temp_files[1] = NULL;
	}
	else
	{
		new_files = malloc(sizeof(char *) * (data->temp_count + 2));
		if (!new_files)
			return ;
		i = 0;
		while (i < data->temp_count)
		{
			new_files[i] = data->temp_files[i];
			i++;
		}
		new_files[i] = ft_strdup(filename);
		new_files[i + 1] = NULL;
		free(data->temp_files);
		data->temp_files = new_files;
	}
	data->temp_count++;
}


void	count_heredocs(t_data *data, t_input *input, int i)
{
	int	j;

	j = 0;
	while (input[i].tab[j] != NULL)
	{
		if (ft_strcmp(input[i].tab[j], "<<") == 0
			&& input[i].tab[j + 1] != NULL)
			data->temp_count++;
		j++;
	}
}

void	heredoc_loop(t_data *data, t_input *input, int i)
{
	char	*line;
	char	*file;
	int		j;

	(void)data;
	j = 0;
	signal(SIGINT, heredoc_signals);
	signal(SIGQUIT, SIG_IGN);
	// count_heredocs(data, input, i);
	while (input[i].tab[j] != NULL)
	{
		if (ft_strcmp(input[i].tab[j], "<<") == 0
			&& input[i].tab[j + 1] != NULL)
		{
			file = temp_file();
			input[i].heredoc = open(file, O_WRONLY | O_CREAT | O_APPEND, 0644);
			if (input[i].heredoc == -1)
				return (free(file));
			// add_temp_file(data, file);
			line = readline("> ");
			while (line)
			{
				if (g_signal == 130
					|| ft_strcmp(line, input[i].tab[j + 1]) == 0)
				{
					free(line);
					break ;
				}
				if (ft_strcmp(line, input[i].tab[j + 1]) == 0)
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
		j++;
	}
	signal(SIGINT, handle_signals);
	signal(SIGQUIT, SIG_IGN);
}

void	heredoc(t_data *data, t_input *input, int i)
{
	// Appeler heredoc_loop pour traiter toutes les redirections
	heredoc_loop(data, input, i);
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
				heredoc(data, input, i);
				dup2(data->copy_stdin, STDIN_FILENO);
				dup2(data->copy_stdout, STDOUT_FILENO);
				close(data->copy_stdin);
				close(data->copy_stdout);
			}
		}
		i++;
	}
}
