/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: idakhlao <idakhlao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 12:28:21 by inesdakhlao       #+#    #+#             */
/*   Updated: 2024/11/11 16:52:34 by idakhlao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	do_redir(t_data *data, t_input *input)
{
	data->copy_stdin = dup(STDIN_FILENO);
	data->copy_stdout = dup(STDOUT_FILENO);
	if (input[0].in_file != NULL || input[0].out_file != NULL)
	{
		if (redir(input, 0, data) == 1)
		{
			dup2(data->copy_stdin, STDIN_FILENO);
			dup2(data->copy_stdout, STDOUT_FILENO);
			close(data->copy_stdin);
			close(data->copy_stdout);
			return ;
		}
	}
	exec_builtins(data, input, input->cmd);
	dup2(data->copy_stdin, STDIN_FILENO);
	dup2(data->copy_stdout, STDOUT_FILENO);
	close(data->copy_stdin);
	close(data->copy_stdout);
}

void	unlink_heredoc(void)
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
		unlink(file);
		free(file);
		nb = ft_itoa(++file_index);
		file = ft_strjoin(tmp, nb);
		free(nb);
	}
	free(tmp);
	free(file);
}


int	input_redir(t_input *input, int i)
{
	int	infile;

	if (input[i].redir_infile && ft_strncmp(input[i].redir_infile, "<", 1) == 0)
	{
		infile = open(input[i].in_file, O_RDONLY, 0644);
		if (infile < 0)
			return (1);
		if (dup2(infile, STDIN_FILENO) == -1)
			return (close(infile), perror("dup2"), 1);
		close(infile);
	}
	return (0);
}

int	check_redir(t_input *input, int i, t_data *data)
{
	t_redir	redir;

	redir.j = 0;
	ft_bzero(&redir, sizeof(t_redir));
	while (input[i].tab[redir.j] && redir.j < get_tab_len(input[i].input))
	{
		if (input[i].tab[redir.j]
			&& (ft_strcmp(input[i].tab[redir.j], ">") == 0))
			next_check_redir(input, i, data, redir);
		else if (input[i].tab[redir.j]
			&& (ft_strcmp(input[i].tab[redir.j], ">>") == 0))
			next_check_redir2(input, i, data, redir);
		else if (input[i].tab[redir.j]
			&& (ft_strcmp(input[i].tab[redir.j], "<") == 0))
			next_check_redir3(input, i, data, redir);
		// else if (input[i].tab[redir.j]
		// 	&& (ft_strcmp(input[i].tab[redir.j], "<<") == 0))
		// 	next_check_redir4(input, i, data, redir);
		redir.j++;
	}
	return (0);
}

int	redir(t_input *input, int i, t_data *data)
{
	int		outfile;

	if (check_redir(input, i, data) == 1)
		return (1);
	if (input[i].in_file != NULL)
	{
		if (input_redir(input, i) == 1)
			return (1);
	}
	if (input[i].out_file != NULL)
	{
		if (ft_strcmp(input[i].redir_outfile, ">") == 0)
		outfile = open(input[i].out_file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		if (ft_strcmp(input[i].redir_outfile, ">>") == 0)
			outfile = open(input[i].out_file, \
				O_WRONLY | O_CREAT | O_APPEND, 0644);
		if (outfile < 0)
			return (1);
		if (dup2(outfile, STDOUT_FILENO) == -1)
			return (close(outfile), perror("dup2"), 1);
		close(outfile);
	}
	return (0);
}


		// {
		// 	redir.j++;
		// 	redir.file = add_to_input(input[i].tab[redir.j], data, &quote);
		// 	redir.outfile = open(redir.file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		// 	if (redir.outfile < 0)
		// 		return (perror(redir.file), free(redir.file), 1);
		// 	else
		// 	{
		// 		free(redir.file);
		// 		close(redir.outfile);
		// 	}
		// }
		
		// {
		// 	redir.j++;
		// 	redir.file = add_to_input(input[i].tab[redir.j], data, &quote);
		// 	redir.outfile = open(redir.file, O_WRONLY | O_CREAT | O_APPEND, 0644);
		// 	if (redir.outfile < 0)
		// 		return (perror(redir.file), free(redir.file), 1);
		// 	else
		// 	{
		// 		free(redir.file);
		// 		close(redir.outfile);
		// 	}
		// }
		
		
		// {
		// 	redir.j++;
		// 	redir.file = add_to_input(input[i].tab[redir.j], data, &quote);
		// 	redir.infile = open(redir.file, O_RDONLY, 0644);
		// 	if (redir.infile < 0)
		// 		return (perror(redir.file), free(redir.file), 1);
		// 	else
		// 	{
		// 		free(redir.file);
		// 		close(redir.infile);
		// 	}
		// }
