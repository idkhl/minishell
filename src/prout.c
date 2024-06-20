/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prout.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: idakhlao <idakhlao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/14 16:29:31 by idakhlao          #+#    #+#             */
/*   Updated: 2024/06/20 17:37:18 by idakhlao         ###   ########.fr       */
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
}

void	parse_line(t_data *data, char *line)
{
	data->input = ft_split(line, ' ');
	if (!data->input)
		return ;
	if (ft_strcmp(*data->input, "echo") == 0)
		build_echo(data);
	if (ft_strcmp(*data->input, "pwd") == 0)
		build_pwd();
	if (ft_strcmp(*data->input, "cd") == 0)
		build_cd(data);
	if (ft_strcmp(*data->input, "env") == 0)
		build_env(data);
	if (ft_strcmp(*data->input, "export") == 0)
		build_export(data);
	if (ft_strcmp(*data->input, "unset") == 0)
		build_unset(data);
	malloc_free(data->input);
}

int	main(int ac, char **av, char **envp)
{
	char	*line;
	t_data	data;

	init_struct(&data, envp);
	line = readline("minishell $> ");
	while (line)
	{
		parse_line(&data, line);
		if (ft_strcmp(line, "exit") == 0)
		{
			if (data.env)
				malloc_free(data.env);
			return (0);
		}
		free(line);
		line = readline("minishell $> ");
	}
	(void)av;
	(void)ac;
	if (data.input)
		malloc_free(data.input);
	if (data.exp)
		malloc_free(data.exp);
	if (data.env)
		malloc_free(data.env);
}

//plusieurs export
//unset avnat d'export
