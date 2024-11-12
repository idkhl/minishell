/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prout.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afrikach <afrikach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/14 16:29:31 by idakhlao          #+#    #+#             */
/*   Updated: 2024/11/12 13:22:02 by afrikach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	g_signal = 0;

void	init_struct(t_data *data, t_input *input, char **envp)
{
	data->env = ft_tabdup(envp);
	if (!data->env)
		return ;
	data->exp = NULL;
	data->copy_stdin = -1;
	data->copy_stdout = -1;
	data->exit_status = 0;
	if (input == NULL)
		return ;
	input->input = NULL;
	input->cmd = NULL;
	input->tab = NULL;
	input->in_file = NULL;
	input->out_file = NULL;
	input->redir_infile = NULL;
	input->redir_outfile = NULL;
	input->fd_in = -1;
	input->fd_out = -1;
	input->heredoc = 0;
}

void	no_pipe(t_data *data, t_input *input)
{
	if (input[0].in_file)
	{
		if (ft_strcmp(input[0].redir_infile, "<<") == 0)
			heredoc(input, 0);
		if (g_signal == 130)
		{
			unlink_heredoc();
			return ;
		}
	}
	if (check_builtins(input->cmd) == 0)
		execute_cmd(data, input, input->cmd);
	else
		do_redir(data, input);
}

void	parse_line(t_data *data, t_input *input, char *line)
{
	int		nb_blocks;

	nb_blocks = count_blocks(line);
	if (nb_blocks)
		g_signal = 0;
	if (nb_blocks == 1)
		no_pipe(data, input);
	else
	{
		pipe_heredoc(data, input, nb_blocks);
		if (g_signal == 130)
		{
			printf("1\n");
			unlink_heredoc();
			return ;
		}
		pipex(data, input, nb_blocks);
	}
	unlink_heredoc();
}

void	loop(t_data *data, t_input *input, char *line)
{
	while (line)
	{
		data->exit_status = g_signal;
		add_history(line);
		if (check_syntax(line, data) == 1)
		{
			free(line);
			line = readline("\001\e[1;32m\002minishell $> \001\e[0m\002");
			continue ;
		}
		allocate_new_struct(&input, line);
		fill_struct(input, line, data);
		parse_line(data, input, line);
		free_all(input);
		free(line);
		line = readline("\001\e[1;32m\002minishell $> \001\e[0m\002");
	}
}

int	main(int ac, char **av, char **envp)
{
	char	*line;
	t_data	data;
	t_input	*input;

	if (isatty(0) != 1)
		return (1);
	input = NULL;
	signal(SIGINT, handle_signals);
	signal(SIGQUIT, SIG_IGN);
	line = readline("\001\e[1;32m\002minishell $> \001\e[0m\002");
	init_struct(&data, input, envp);
	loop(&data, input, line);
	(void)av;
	(void)ac;
	if (data.env)
		malloc_free(data.env);
	rl_clear_history();
}
