/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prout.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afrikach <afrikach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/14 16:29:31 by idakhlao          #+#    #+#             */
/*   Updated: 2024/11/07 15:52:42 by afrikach         ###   ########.fr       */
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

void	parse_line(t_data *data, t_input *input, char *line)
{
	int		nb_blocks;

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
			do_redir(data, input);
	}
	else
	{
		pipe_heredoc(data, input, nb_blocks);
		pipex(data, input, nb_blocks);
	}
	unlink_heredoc(input, nb_blocks);
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
	line = readline("\033[1;32mminishell $> \033[0m");
	init_struct(&data, input, envp);
	while (line)
	{
		add_history(line);
		if (check_syntax(line) == 1)
		{
			free(line);
			line = readline("\033[1;32mminishell $> \033[0m");
			continue ;
		}
		allocate_new_struct(&input, line);
		fill_struct(input, line, &data);
		//printf("tab_len = %d\n", get_tab_len(input[0].input));
		parse_line(&data, input, line);
		free_all(input);
		free(line);
		line = readline("\033[1;32mminishell $> \033[0m");
	}
	(void)av;
	(void)ac;
	if (data.env)
		malloc_free(data.env);
	exit(g_signal);
}
