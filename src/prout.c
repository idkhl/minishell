/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prout.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: idakhlao <idakhlao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/14 16:29:31 by idakhlao          #+#    #+#             */
/*   Updated: 2024/10/09 17:58:56 by idakhlao         ###   ########.fr       */
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
}

void	heredoc_input(t_input *input, char *file)
{
	
}

void	heredoc(t_data *data, t_input *input, int nb)
{
	char	*tmp;
	char	*file;
	int		i;
	char	*line;

	tmp = ft_strdup(".heredoc");
	file = ft_strjoin(tmp, ft_itoa(nb));
	data->heredoc = open(file, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (data->heredoc == -1)
		return ;
	line = readline("> ");
	while (line)
	{
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
	heredoc_input(input, file);
}

void	parse_line(t_data *data, t_input *input, char *line)
{
	int		nb_blocks;

	nb_blocks = count_blocks(line);
	if (nb_blocks == 1)
	{
		if (input[0].redir_infile
			&& ft_strcmp(input[0].redir_infile, "<<") == 0)
		{
			heredoc(data, input, 0);
		}
		if (check_builtins(input->cmd) == 0)
			execute_cmd(data, input, input->cmd);
		else
		{
			if (input[0].in_file != NULL || input[0].out_file != NULL)
			{
				data->copy_stdin = dup(STDIN_FILENO);
				data->copy_stdout = dup(STDOUT_FILENO);
				redir(data, input, 0);
			}
			exec_builtins(data, input->cmd);
			dup2(data->copy_stdin, STDIN_FILENO);
			dup2(data->copy_stdout, STDOUT_FILENO);
		}
	}
	else
		pipex(data, input, nb_blocks);
}

int	main(int ac, char **av, char **envp)
{
	char	*line;
	t_data	data;
	t_input	*input = NULL;

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