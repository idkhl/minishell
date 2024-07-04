/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prout.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: idakhlao <idakhlao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/14 16:29:31 by idakhlao          #+#    #+#             */
/*   Updated: 2024/07/04 17:30:25 by idakhlao         ###   ########.fr       */
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

void	output_redir(t_data *data)
{
	int	outfile;

	if (data->input[1] && ft_strcmp(data->input[1], ">") == 0)
		outfile = open(data->input[2], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (data->input[1] && ft_strcmp(data->input[1], ">>") == 0)
		outfile = open(data->input[2], O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (outfile < 0)
		return (perror("Open"));
	if (dup2(outfile, STDOUT_FILENO) == -1)
		return (close(outfile), perror("dup2"));
	close(outfile);
}

void	execute_cmd(t_data *data)
{
	int		i;
	char	*cmd;
	char	**tmp;
	pid_t	pid;

	i = 0;
	data->path = get_path(data);
	cmd = access_cmd(data);
	tmp = ft_split(data->input[0], ' ');
	if (!tmp)
		return ;
	if (!cmd)
		return (malloc_free(tmp), perror("access_cmd"));
	pid = fork();
	if (pid < 0)
		return (malloc_free(tmp), free(cmd), perror("fork"));
	if (pid == 0)
	{
		if (execve(cmd, data->input, data->env) == -1)
		{
			malloc_free(data->path);
			return (free(cmd), malloc_free(tmp), exit(EXIT_FAILURE));
		}
	}
	else
	{
		waitpid(pid, NULL, 0);
		free(cmd);
		malloc_free(tmp);
	}
}

void	here_doc(t_data *data)
{
	char	*line;
	char	*lim;

	lim = ft_strjoin(data->input[2], "\n");
	if (!lim)
		return ;
	line = readline("> ");
	data->heredoc = open(".tmp_doc", O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (data->heredoc == -1)
		return (free(lim));
	while (line)
	{
		if (ft_strcmp(line, data->input[2]) == 0)
		{
			free(line);
			break ;
		}
		write(data->heredoc, line, ft_strlen(line));
		write(data->heredoc, "\n", 1);
		free(line);
		line = readline("> ");
	}
	free(lim);
	close(data->heredoc);
}

void	input_redir(t_data *data)
{
	int	infile;
	int	heredoc_infile;

	if (data->input[1] && ft_strcmp(data->input[1], "<") == 0)
	{
		infile = open(data->input[2], O_RDONLY, 0644);
		if (infile < 0)
			return (perror("Open"));
		if (dup2(infile, STDIN_FILENO) == -1)
			return (close(infile), perror("dup2"));
		close(infile);
	}
	if (data->input[1] && ft_strcmp(data->input[1], "<<") == 0)
	{
		here_doc(data);
		heredoc_infile = open(".tmp_doc", O_RDONLY);
		if (heredoc_infile < 0)
			return (perror("heredoc read open"));
		if (dup2(heredoc_infile, STDIN_FILENO) == -1)
			return (close(heredoc_infile), perror("dup2"));
		close(heredoc_infile);
		unlink(".tmp_doc");
	}
}

void	execute_cmd_in(t_data *data)
{
	char	*cmd;
	char	**tmp;
	pid_t	pid;

	data->path = get_path(data);
	cmd = access_cmd(data);
	if (!cmd)
		return (perror("access_cmd"));
	tmp = ft_split(data->input[0], ' ');
	if (!tmp)
		return (free(cmd));
	pid = fork();
	if (pid < 0)
		return (malloc_free(tmp), free(cmd), perror("fork"));
	if (pid == 0)
	{
		input_redir(data);
		if (execve(cmd, tmp, data->env) == -1)
		{
			// printf("\n\ntest\n\n");
			malloc_free(data->path);
			return (free(cmd), malloc_free(tmp), perror("exec"));
		}
	}
	else
	{
		waitpid(pid, NULL, 0);
		free(cmd);
		malloc_free(tmp);
	}
}

void	execute_cmd_out(t_data *data)
{
	char	*cmd;
	char	**tmp;
	pid_t	pid;

	data->path = get_path(data);
	cmd = access_cmd(data);
	if (!cmd)
		return (perror("access_cmd"));
	tmp = ft_split(data->input[0], ' ');
	if (!tmp)
		return (free(cmd));
	pid = fork();
	if (pid < 0)
		return (malloc_free(tmp), free(cmd), perror("fork"));
	if (pid == 0)
	{
		output_redir(data);
		if (execve(cmd, tmp, data->env) == -1)
		{
			malloc_free(data->path);
			return (free(cmd), malloc_free(tmp), exit(EXIT_FAILURE));
		}
	}
	else
	{
		waitpid(pid, NULL, 0);
		free(cmd);
		malloc_free(tmp);
	}
}

void	parse_line(t_data *data, char *line)
{
	if (ft_strlen(line) == 0)
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
	malloc_free(data->input);
}

void	handle_sigint(int sig)
{
	if (sig == SIGINT)
	{
		printf("^C\n");
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
}

void	handle_signals()
{
	rl_catch_signals = 0;
	signal(SIGINT, handle_sigint);
	// signal(SIGINT, handle_sigint);
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