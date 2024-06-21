/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prout.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: idakhlao <idakhlao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/14 16:29:31 by idakhlao          #+#    #+#             */
/*   Updated: 2024/06/21 18:15:43 by idakhlao         ###   ########.fr       */
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

char	*get_pathline(t_data *data)
{
	int	i;

	i = 0;
	while (data->env[i])
	{
		if (ft_strncmp(data->env[i], "PATH=", 5) == 0)
			return (data->env[i]);
		i++;
	}
	return (NULL);
}

char	**get_path(t_data *data)
{
	char	*tmp;
	char	**path;

	tmp = get_pathline(data);
	if (!tmp)
		return (NULL);
	tmp += 5;
	path = ft_split(tmp, ':');
	if (!path)
		return (NULL);
	// printf("[%s]\n", path[1]);
	return (path);
}

char	*access_cmd(t_data *data)
{
	char	*bin;
	char	*tmp;
	int		i;

	i = 0;
	if (data->input[0] && access(data->input[0], F_OK | X_OK) == 0)
		return (ft_strdup(data->input[0]));
	while (data->path && data->path[i])
	{
		tmp = ft_strjoin(data->path[i], "/");
		if (!tmp)
			return (NULL);
		bin = ft_strjoin(tmp, data->input[0]);
		if (!bin)
			return (free(tmp), NULL);
		// printf("%s\n", bin);
		free(tmp);
		if (access(bin, F_OK | X_OK) == 0)
			return (bin);
		free(bin);
		i++;
	}
	return (NULL);
}

void	output_redir(t_data *data)
{
	int	outfile;

	outfile = open(data->input[2], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (dup2(outfile, STDOUT_FILENO) == -1)
		return ;
	close(outfile);
}

void	execute_cmd(t_data *data)
{
	int		i;
	char	*cmd;
	pid_t	pid;

	i = 0;
	data->path = get_path(data);
	cmd = access_cmd(data);
	if (!cmd)
		return ;
	pid = fork();
	if (pid < 0)
		return ;
	if (pid == 0)
	{
		if (*data->input[1] == '>')
			output_redir(data);
		if (execve(cmd, data->input, data->env) == -1)
		{
			malloc_free(data->path);
			return (free(cmd), exit(EXIT_FAILURE));
		}
	}
	else
	{
		waitpid(pid, NULL, 0);
		free(cmd);
	}
	malloc_free(data->path);
}

void	parse_line(t_data *data, char *line)
{
	data->input = ft_split(line, ' ');
	if (!data->input)
		return ;
	check_expand(data);
	if (ft_strcmp(*data->input, "echo") == 0)
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
	// if (*data->input[1] == '>')
	// 	output_redir(data);
	else
		execute_cmd(data);
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
		if (ft_strcmp(line, "exit") == 0)
		{
			if (data.env)
				malloc_free(data.env);
			if (data.path)
				malloc_free(data.path);
			return (0);
		}
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


// line = /n || isspace
