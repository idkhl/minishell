/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prout.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: idakhlao <idakhlao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/14 16:29:31 by idakhlao          #+#    #+#             */
/*   Updated: 2024/06/20 19:36:11 by idakhlao         ###   ########.fr       */
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

void	expand_variable(t_data *data, char *var, char *input, int i)
{
	char	*new;
	int		size;

	size = ft_strlen(var) - ft_strlen(input);
	new = ft_substr(var, ft_strlen(input), size);
	if (!new)
		return ;
	free(data->input[i]);
	data->input[i] = ft_strdup(new);
	free(new);
}

void	check_expand(t_data *data)
{
	int		i;
	int		j;
	char	*var;

	i = 0;
	while (data->input[i])
	{
		j = 0;
		while (data->env[j])
		{
			if (*data->input[i] == '$')
			{
				var = ft_substr(data->input[i], 1, (ft_strlen(data->input[i]) - 1));
				if (!var)
					return ;
				if (ft_strncmp(var, data->env[j], ft_strlen(data->input[i]) - 1) == 0)
				{
					expand_variable(data, data->env[j], data->input[i], i);
				}
				free(var);
			}
			j++;
		}
		i++;
	}
}

void	parse_line(t_data *data, char *line)
{
	data->input = ft_split(line, ' ');
	if (!data->input)
		return ;
	check_expand(data);
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
		add_history(line);
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
