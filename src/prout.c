/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prout.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: idakhlao <idakhlao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/14 16:29:31 by idakhlao          #+#    #+#             */
/*   Updated: 2024/08/22 19:24:35 by idakhlao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	init_struct(t_data *data, char **envp)
{
	data->env = ft_tabdup(envp);
	if (!data->env)
		return ;
	data->input = NULL;
	data->exp = NULL;
	data->path = NULL;
}

void	pipex(t_data *data)
{
	int	infile;

	execute_cmd(data);
	infile = open(data->input[4], O_RDONLY, 0644);
	if (dup2(infile, STDIN_FILENO) == -1)
		return (close(infile), perror("dup2"));
}

void	parse_line(t_data *data, char *line)
{
	if (ft_strlen(line) == 0)
		return ;
	split_quotes(line, ' ');
	return ;
	data->input = ft_split(line, ' ');
	if (!data->input)
		return ;
	expand(data);
	if (ft_strcmp(*data->input, "exit") == 0)
		build_exit(data);
	else if (ft_strcmp(*data->input, "echo") == 0)
		build_echo(data);
	else if (ft_strcmp(*data->input, "pwd") == 0)
		build_pwd();
	else if (ft_strcmp(*data->input, "cd") == 0)
		build_cd(data);
	else if (ft_strcmp(*data->input, "env") == 0)
		build_env(data);
	else if (ft_strcmp(*data->input, "export") == 0)
		build_export(data);
	else if (ft_strcmp(*data->input, "unset") == 0)
		build_unset(data);
	else if (ft_tablen(data->input) > 1 && *data->input[1] == '>')
	{
		execute_cmd_out(data);
		malloc_free(data->path);
	}
	else if (ft_tablen(data->input) > 1 && *data->input[1] == '<')
	{
		execute_cmd_in(data);
		malloc_free(data->path);
	}
	else
	{
		execute_cmd(data);
		malloc_free(data->path);
	}
	if (ft_tablen(data->input) > 3 && *data->input[2] == '|')
	{
		pipex(data);
	}
	malloc_free(data->input);
}

int	main(int ac, char **av, char **envp)
{
	char	*line;
	t_data	data;

	init_struct(&data, envp);
	handle_signals();
	line = readline("minishell $> ");
	while (line)
	{
		add_history(line);
		parse_line(&data, line);
		free(line);
		line = readline("minishell $> ");
	}
	(void)av;
	(void)ac;
	if (data.env)
		malloc_free(data.env);
}

// export a b -> export X env
//			pas de chiffres  symboles avant =
//			export les autres var si la 1ere existe deja
// echo var qui n'existe pas -> \n 
// var sans commandes

// line = /n || isspace
// sigignore dans le parent