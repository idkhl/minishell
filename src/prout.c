/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prout.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: idakhlao <idakhlao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/14 16:29:31 by idakhlao          #+#    #+#             */
/*   Updated: 2024/10/23 12:58:14 by idakhlao         ###   ########.fr       */
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

	input = NULL;
	signal(SIGINT, handle_signals);
	signal(SIGQUIT, SIG_IGN);
	line = readline("\033[1;33mminishell $> \033[0m");
	init_struct(&data, input, envp);
	while (line)
	{
		add_history(line);
		if (check_syntax(line) == 1)
		{
			free(line);
			line = readline("\033[1;33mminishell $> \033[0m");
			continue ;
		}
		allocate_new_struct(&input, line);
		fill_struct(input, line);
		parse_line(&data, input, line);
		free(line);
		line = readline("\033[1;33mminishell $> \033[0m");
	}
	(void)av;
	(void)ac;
	if (data.env)
		malloc_free(data.env);
	malloc_free(data.path);
}

// ==121132==    at 0x4848899: malloc (in /usr/libexec/valgrind/vgpreload_memcheck-amd64-linux.so)
// ==121132==    by 0x405498: allocate_new_struct (get_big_tab.c:61)
// ==121132==    by 0x40184E: main (prout.c:150)
// redir_infile pas init?
// echo si $ vide -> sauter
// exit dup2 l.55-56
// echo dans /dev/full -> proteger write
// expand dans le heredoc
// command not found 1e pipe
// open les infile/outfile si plusieurs redir
// ./minishel ./minishell

// la
// Invalid read of size 1
// ==168601==    at 0x405152: check_open_operators (syntax_open_redir.c:43)
// ==168601==    by 0x404C50: check_syntax (syntax_quotes.c:88)
// ==168601==    by 0x401607: main (prout.c:95)
// ==168601==  Address 0x4b63df4 is 0 bytes after a block of size 4 alloc'd
// ==168601==    at 0x4848899: malloc (in /usr/libexec/valgrind/vgpreload_memcheck-amd64-linux.so)
// ==168601==    by 0x48AEBAC: xmalloc (in /usr/lib/x86_64-linux-gnu/libreadline.so.8.1)
// ==168601==    by 0x488C694: readline_internal_teardown (in /usr/lib/x86_64-linux-gnu/libreadline.so.8.1)
// ==168601==    by 0x4896D2A: readline (in /usr/lib/x86_64-linux-gnu/libreadline.so.8.1)
// ==168601==    by 0x4015D5: main (prout.c:90)
// ==168601== 
// ==168601== Invalid read of size 1
// ==168601==    at 0x405372: check_close_operators (syntax_close_redir.c:47)
// ==168601==    by 0x404C6E: check_syntax (syntax_quotes.c:90)
// ==168601==    by 0x401607: main (prout.c:95)
// ==168601==  Address 0x4b63df4 is 0 bytes after a block of size 4 alloc'd
// ==168601==    at 0x4848899: malloc (in /usr/libexec/valgrind/vgpreload_memcheck-amd64-linux.so)
// ==168601==    by 0x48AEBAC: xmalloc (in /usr/lib/x86_64-linux-gnu/libreadline.so.8.1)
// ==168601==    by 0x488C694: readline_internal_teardown (in /usr/lib/x86_64-linux-gnu/libreadline.so.8.1)
// ==168601==    by 0x4896D2A: readline (in /usr/lib/x86_64-linux-gnu/libreadline.so.8.1)
// ==168601==    by 0x4015D5: main (prout.c:90)
// ==168601== 
// ==168601== Invalid read of size 1
// ==168601==    at 0x404DED: check_begin_pipes (syntax_pipes.c:48)
// ==168601==    by 0x404C8C: check_syntax (syntax_quotes.c:92)
// ==168601==    by 0x401607: main (prout.c:95)
// ==168601==  Address 0x4b63df4 is 0 bytes after a block of size 4 alloc'd
// ==168601==    at 0x4848899: malloc (in /usr/libexec/valgrind/vgpreload_memcheck-amd64-linux.so)
// ==168601==    by 0x48AEBAC: xmalloc (in /usr/lib/x86_64-linux-gnu/libreadline.so.8.1)
// ==168601==    by 0x488C694: readline_internal_teardown (in /usr/lib/x86_64-linux-gnu/libreadline.so.8.1)
// ==168601==    by 0x4896D2A: readline (in /usr/lib/x86_64-linux-gnu/libreadline.so.8.1)
// ==168601==    by 0x4015D5: main (prout.c:90)
// ==168601== 
// ==168601== Invalid read of size 1
// ==168601==    at 0x404F72: check_end_pipes (syntax_pipes.c:75)
// ==168601==    by 0x404CAA: check_syntax (syntax_quotes.c:94)
// ==168601==    by 0x401607: main (prout.c:95)
// ==168601==  Address 0x4b63df4 is 0 bytes after a block of size 4 alloc'd
// ==168601==    at 0x4848899: malloc (in /usr/libexec/valgrind/vgpreload_memcheck-amd64-linux.so)
// ==168601==    by 0x48AEBAC: xmalloc (in /usr/lib/x86_64-linux-gnu/libreadline.so.8.1)
// ==168601==    by 0x488C694: readline_internal_teardown (in /usr/lib/x86_64-linux-gnu/libreadline.so.8.1)
// ==168601==    by 0x4896D2A: readline (in /usr/lib/x86_64-linux-gnu/libreadline.so.8.1)
// ==168601==    by 0x4015D5: main (prout.c:90)
