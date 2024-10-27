/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prout.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inesdakhlaoui <inesdakhlaoui@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/14 16:29:31 by idakhlao          #+#    #+#             */
/*   Updated: 2024/10/27 14:09:30 by inesdakhlao      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	init_struct(t_data *data, t_input *input, char **envp)
{
	data->env = ft_tabdup(envp);
	if (!data->env)
		return ;
	data->exp = NULL;
	data->path = get_path(data);
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
		// int	i;
		// int	j;
		// int	k;
		// i = 0;
		// while (input[i].input)
		// {
		// 	k = 0;
		// 	j = 0;
		// 	while (input[i].tab[k])
		// 	{
		// 		printf("TAB [%d]: %s", k, input[i].tab[k]);
		// 		printf("\n");
		// 		k++;
		// 	}
		// 	while (input[i].cmd[j])
		// 	{
		// 		printf("CMD [%d]: %s\n", j, input[i].cmd[j]);
		// 		j++;
		// 	}
		// 	i++;
		// }
		parse_line(&data, input, line);
		free_all(input);
		free(line);
		line = readline("\033[1;32mminishell $> \033[0m");
	}
	(void)av;
	(void)ac;
	if (data.env)
		malloc_free(data.env);
	malloc_free(data.path);
}
