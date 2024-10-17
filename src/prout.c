/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prout.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: idakhlao <idakhlao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/14 16:29:31 by idakhlao          #+#    #+#             */
/*   Updated: 2024/10/17 17:33:03 by idakhlao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	init_struct(t_data *data, t_input *input, char **envp)
{
	int	i;

	i = 0;
	data->env = ft_tabdup(envp);
	if (!data->env)
		return ;
	data->exp = NULL;
	data->path = get_path(data);
	if (input == NULL)
		return ;
	input->input = NULL;
	input->cmd = NULL;
	input->in_file = NULL;
	input->out_file = NULL;
	input->redir_infile = NULL;
	input->redir_outfile = NULL;
	input->fd_in = -1;
	input->fd_out = -1;
	input->heredoc = 0;
}

void	parse_line(t_data *data, t_input *input, char *line)
{
	int		nb_blocks;
	int		j;

	nb_blocks = count_blocks(line);
	if (nb_blocks == 1)
	{
		if (input[0].in_file)
		{
			if (ft_strcmp(input[0].redir_infile, "<<") == 0)
				heredoc(input, 0);
		}
		if (check_builtins(input->cmd) == 0)
			execute_cmd(data, input, input->cmd);
		else
		{
			data->copy_stdin = dup(STDIN_FILENO);
			data->copy_stdout = dup(STDOUT_FILENO);
			if (input[0].in_file != NULL || input[0].out_file != NULL)
			{
				redir(data, input, 0);
			}
			exec_builtins(data, input->cmd);
			dup2(data->copy_stdin, STDIN_FILENO);
			dup2(data->copy_stdout, STDOUT_FILENO);
			close(data->copy_stdin);
			close(data->copy_stdout);
		}
	}
	else
	{
		pipe_heredoc(data, input, nb_blocks);
		pipex(data, input, nb_blocks);
	}
	j = 0;
	while (j < nb_blocks)
	{
		if (input[j].in_file && ft_strcmp(input[j].redir_infile, "<<") == 0)
			unlink(input[j].in_file);
		j++;
	}
}

int	main(int ac, char **av, char **envp)
{
	char	*line;
	t_data	data;
	t_input	*input;

	input = NULL;
	handle_signals(); // a refaire->ne marche bien que si tout est ok et que dans le parent
	line = readline("minishell $> ");
	init_struct(&data, input, envp);
	while (line)
	{
		add_history(line);
		if (check_syntax(line) == 1)
		{
			free(line);
			line = readline("minishell $> ");
			continue ;
		}
		allocate_new_struct(&input, line);
		fill_struct(input, line);
		parse_line(&data, input, line);
		free(line);
		line = readline("minishell $> ");
	}
	(void)av;
	(void)ac;
	if (data.env)
		malloc_free(data.env);
	malloc_free(data.path);
}

// rajouter l'export modifié
// rajouter cd
// ==121132==    at 0x4848899: malloc (in /usr/libexec/valgrind/vgpreload_memcheck-amd64-linux.so)
// ==121132==    by 0x405498: allocate_new_struct (get_big_tab.c:61)
// ==121132==    by 0x40184E: main (prout.c:150)
// redir_infile pas init?