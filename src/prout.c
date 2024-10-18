/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prout.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afrikach <afrikach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/14 16:29:31 by idakhlao          #+#    #+#             */
/*   Updated: 2024/10/18 11:23:14 by afrikach         ###   ########.fr       */
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
	input->tab = NULL;
	input->in_file = NULL;
	input->out_file = NULL;
	input->redir_infile = NULL;
	input->redir_outfile = NULL;
	input->fd_in = -1;
	input->fd_out = -1;
}

void	parse_line(t_data *data, t_input *input, char *line)
{
	int	nb_blocks;

	nb_blocks = count_blocks(line);
	if (nb_blocks == 1)
	{
		if (check_builtins(data, input->cmd) == 0)
			execute_cmd(data, input, input->cmd);
	}
	else
		pipex (data, input, nb_blocks);
	// free_tab(big_tab, nb_blocks);
}

int	main(int ac, char **av, char **envp)
{
	char	*line;
	t_data	data;
	t_input	*input;

	input = NULL;
	// handle_signals(); // a refaire->ne marche bien que si tout est ok et que dans le parent
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
		// printf("redir in file : %s | %s\n", input[0].redir_infile, input[0].in_file);
		// printf("redir out file : %s | %s\n", input[0].redir_outfile, input[0].out_file);
		// printf("var in env ===== %s ===== \n", return_var_name(line));
		// char * str = add_to_input(line, &data);
		// printf(" input = %s\n", str);
		int	i;
		int	j;
		i = 0;
		while (input[i].input)
		{
			j = 0;
			// printf("=============== struct [%d]================\n", i);
			// printf("Analyzing input[%d]: %s\n", i, input[i].input);
			// while (input[i].tab[j])
			// {
			// 	printf("Index redir = %d\n", get_index_redir(input, &j));
			// 	printf("TAB [%d]: %s\n", j, input[i].tab[j]);
			// 	j++;
			// }
			while (input[i].cmd[j])
			{
				printf("CMD [%d]: %s\n", j, input[i].cmd[j]);
				j++;
			}
			i++;
		}
		parse_line(&data, input, line);
		free(line);
		line = readline("\033[1;32mminishell $> \033[0m");
	}
	(void)av;
	(void)ac;
	if (data.env)
		malloc_free(data.env);
	malloc_free(data.path);
}

