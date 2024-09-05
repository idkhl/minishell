/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prout.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: idakhlao <idakhlao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/14 16:29:31 by idakhlao          #+#    #+#             */
/*   Updated: 2024/09/05 16:13:20 by idakhlao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	init_struct(t_data *data, char **envp)
{
	data->env = ft_tabdup(envp);
	if (!data->env)
		return ;
	data->exp = NULL;
	data->path = get_path(data);
}

// void	exec_pipes(t_data *data, char **tab, int i, int nb_blocks)
// {
// 	char	*cmd;
// 	char	**tmp;

// 	data->path = get_path(data);
// 	cmd = access_cmd(data, tab);
// 	tmp = ft_split(tab[0], ' ');
// 	if (!tmp)
// 		return ;
// 	if (!cmd)
// 		return (malloc_free(tmp), perror("access_cmd"));
// 	if (i == nb_blocks - 1)
// 	{
// 		if (dup2(data->fd[0], STDIN_FILENO) == -1)
// 			return (perror("dup2 - 4"));
// 		// close(data->fd[0]);
// 		// close(data->fd[1]);
// 	}
// 	else
// 	{
// 		if (dup2(data->fd[1], STDOUT_FILENO) == -1)
// 			return (perror("dup2 - 3"));
// 	}
// 	close(data->fd[0]);
// 	close(data->fd[1]);
// 	if (execve(cmd, tab, data->env) == -1)
// 		return (perror("execve"), _exit(EXIT_FAILURE));
// }

// void	pipex(t_data *data, char ***big_tab, int nb_blocks)
// {
// 	int		i;
// 	pid_t	pid;
// 	int		prev_fd;

// 	i = 0;
// 	prev_fd = -1;
// 	while (i < nb_blocks)
// 	{
// 		if (i < nb_blocks - 1)
// 		{
// 			if (pipe(data->fd) == -1)
// 				return (perror("pipe"));
// 		}
// 		pid = fork();
// 		if (pid == -1)
// 			return (perror("fork"));
// 		if (pid == 0)
// 		{
// 			if (i > 0)
// 			{
// 				if (dup2(prev_fd, STDIN_FILENO) == -1)
// 					return (perror("dup2 - 1"));
// 				close(prev_fd);
// 			}
// 			if (i < nb_blocks - 1)
// 			{
// 				if (dup2(data->fd[1], STDOUT_FILENO) == -1)
// 					return (perror("dup2" - 2));
// 			}
// 			close(data->fd[0]);
// 			close(data->fd[1]);
// 			exec_pipes(data, big_tab[i], i, nb_blocks);
// 		}
// 		else
// 		{
// 			close(data->fd[1]);
// 			if (i > 0)
// 				close(prev_fd);
// 			prev_fd = data->fd[0];
// 		}
// 		i++;
// 	}
// 	while (wait(NULL) != -1)
// 		continue ;
// }

// void	exec_pipes(t_data *data, char **tab)
// {
// 	char	*cmd;
// 	char	**tmp;

// 	data->path = get_path(data);
// 	cmd = access_cmd(data, tab);
// 	tmp = ft_split(tab[0], ' ');
// 	if (!tmp)
// 		return (free(cmd));
// 	if (!cmd)
// 		return (malloc_free(tmp), perror("access_cmd"));
// }

// void	exec_first_pipe(t_data *data, char **tab)
// {
// 	char	*cmd;
// 	char	**tmp;
// 	pid_t	pid;

// 	data->path = get_path(data);
// 	printf("tab 1 = %s\n", tab[0]);
// 	cmd = access_cmd(data, tab);
// 	printf("cmd 1 = %s\n", cmd);
// 	tmp = ft_split(tab[0], ' ');
// 	if (!tmp)
// 		return (free(cmd));
// 	if (!cmd)
// 		return (malloc_free(tmp), perror("access_cmd 1"));
// 	if (pipe(data->fd) == -1)
// 		return (perror("pipe"));
// 	pid = fork();
// 	if (pid == -1)
// 		return (perror("fork"));
// 	if (pid == 0)
// 	{
// 		if (dup2(data->fd[0], STDIN_FILENO) == -1
// 			|| dup2(data->fd[1], STDOUT_FILENO) == -1)
// 			return (perror("dup 1"));
// 		close(data->fd[0]);
// 		close(data->fd[1]);
// 		if (execve(cmd, tab, data->env) == -1)
// 			return (perror("execve"));
// 	}
// 	if (dup2(data->fd[1], STDOUT_FILENO) == -1)
// 		return (perror("dup 2"));
// 	close(data->fd[0]);
// 	close(data->fd[1]);
// 	if (dup2(data->fd[0], STDIN_FILENO) == -1)
// 		return (perror("dup 3"));
// 	close(data->fd[0]);
// 	close(data->fd[1]);
// }

// void	exec_middle_pipes(t_data *data, char **tab)
// {
// 	char	*cmd;
// 	char	**tmp;
// 	pid_t	pid;

// 	data->path = get_path(data);
// 	cmd = access_cmd(data, tab);
// 	tmp = ft_split(tab[0], ' ');
// 	if (!tmp)
// 		return (free(cmd));
// 	if (!cmd)
// 		return (malloc_free(tmp), perror("access_cmd 2"));
// 	if (pipe(data->fd) == -1)
// 		return (perror("pipe"));
// 	pid = fork();
// 	if (pid == -1)
// 		return (perror("fork"));
// 	if (pid == 0)
// 	{
// 		if (dup2(data->fd[1], STDOUT_FILENO) == -1)
// 			return (perror("dup 4"));
// 		close(data->fd[0]);
// 		close(data->fd[1]);
// 		if (execve(cmd, tab, data->env) == -1)
// 			return (perror("execve"));
// 	}
// 	if (dup2(data->fd[1], STDOUT_FILENO) == -1)
// 		return (perror("dup 5"));
// 	close(data->fd[0]);
// 	close(data->fd[1]);
// 	if (dup2(data->fd[0], STDIN_FILENO) == -1)
// 		return (perror("dup 6"));
// 	close(data->fd[0]);
// 	close(data->fd[1]);
// }

// void	exec_last_pipe(t_data *data, char **tab)
// {
// 	char	*cmd;
// 	char	**tmp;
// 	pid_t	pid;

// 	data->path = get_path(data);
// 	cmd = access_cmd(data, tab);
// 	tmp = ft_split(tab[0], ' ');
// 	if (!tmp)
// 		return (free(cmd));
// 	if (!cmd)
// 		return (malloc_free(tmp), perror("access_cmd 3"));
// 	if (pipe(data->fd) == -1)
// 		return (perror("pipe"));
// 	pid = fork();
// 	if (pid == -1)
// 		return (perror("fork"));
// 	if (pid == 0)
// 	{
// 		if (dup2(data->fd[1], STDOUT_FILENO) == -1)
// 			return (perror("dup 7"));
// 		close(data->fd[0]);
// 		close(data->fd[1]);
// 		if (execve(cmd, tab, data->env) == -1)
// 			return (perror("execve"));
// 	}
// 	if (dup2(data->fd[1], STDOUT_FILENO) == -1)
// 		return (perror("dup 8"));
// 	close(data->fd[0]);
// 	close(data->fd[1]);
// 	if (dup2(data->fd[0], STDIN_FILENO) == -1)
// 		return (perror("dup 9"));
// 	close(data->fd[0]);
// 	close(data->fd[1]);
// }

// void	pipex(t_data *data, char ***big_tab, int nb_blocks)
// {
// 	int		i;
// 	// pid_t	pid;
// 	// int		status;

// 	i = 0;
// 	exec_first_pipe(data, big_tab[i]);
// 	while (i < nb_blocks - 1)
// 	{
// 		printf("i = %d\n", i);
// 		printf("[%s]\n", *big_tab[i]);
// 		exec_middle_pipes(data, big_tab[i]);
// 		i++;
// 	}
// 	exec_last_pipe(data, big_tab[i]);
// 	while (wait(NULL) != -1)
// 		continue ;
// }




// void	exec_command(t_data *data, char **tab, int in_fd, int out_fd)
// {
// 	char	*cmd;
// 	char	**tmp;
// 	pid_t	pid;

// 	data->path = get_path(data);
// 	cmd = access_cmd(data, tab);
// 	tmp = ft_split(tab[0], ' ');
// 	if (!tmp)
// 	{
// 		free(cmd);
// 		return ;
// 	}
// 	if (!cmd)
// 	{
// 		malloc_free(tmp);
// 		perror("access_cmd");
// 		return ;
// 	}
// 	pid = fork();
// 	if (pid == -1)
// 	{
// 		perror("fork");
// 		free(cmd);
// 		malloc_free(tmp);
// 		return ;
// 	}
// 	if (pid == 0)
// 	{
// 		if (in_fd != STDIN_FILENO)
// 		{
// 			if (dup2(in_fd, STDIN_FILENO) == -1)
// 			{
// 				perror("dup2 in_fd");
// 				exit(EXIT_FAILURE);
// 			}
// 			close(in_fd);
// 		}
// 		if (out_fd != STDOUT_FILENO)
// 		{
// 			if (dup2(out_fd, STDOUT_FILENO) == -1)
// 			{
// 				perror("dup2 out_fd");
// 				exit(EXIT_FAILURE);
// 			}
// 			close(out_fd);
// 		}
// 		if (execve(cmd, tab, data->env) == -1)
// 		{
// 			perror("execve");
// 			exit(EXIT_FAILURE);
// 		}
// 	}
// 	if (in_fd != STDIN_FILENO)
// 		close(in_fd);
// 	if (out_fd != STDOUT_FILENO)
// 		close(out_fd);
// 	free(cmd);
// 	malloc_free(tmp);
// }

// void	pipex(t_data *data, char ***big_tab, int nb_blocks)
// {
// 	int	i;
// 	int	in_fd;

// 	i = 0;
// 	in_fd = STDIN_FILENO;
// 	while (i < nb_blocks)
// 	{
// 		if (i < nb_blocks - 1)
// 		{
// 			if (pipe(data->fd) == -1)
// 				(perror("pipe"), exit(EXIT_FAILURE));
// 			exec_command(data, big_tab[i], in_fd, data->fd[1]);
// 			close(data->fd[1]);
// 			in_fd = data->fd[0];
// 		}
// 		else
// 			exec_command(data, big_tab[i], in_fd, STDOUT_FILENO);
// 		i++;
// 	}
// 	if (in_fd != STDIN_FILENO)
// 		close(in_fd);
// 	while (wait(NULL) != -1);
// }


void	exec_first_pipe(t_data *data, char **tab)
{
	char	*cmd;
	pid_t	pid;

	cmd = access_cmd(data, tab);
	if (!cmd)
		return (free(cmd), perror("access_cmd 1"));
	if (pipe(data->fd) == -1)
		return (perror("pipe 1"));
	// if (check_builtins(data, tab) == 0)
	pid = fork();
	if (pid == -1)
		return (perror("fork 1"));
	if (pid == 0)
	{
		close(data->fd[0]);
		if (dup2(data->fd[1], STDOUT_FILENO) == -1)
		{
			perror("dup2 1");
			exit(EXIT_FAILURE);
		}
		close(data->fd[1]);
		if (execve(cmd, tab, data->env) == -1)
		{
			perror("execve 1");
			exit(EXIT_FAILURE);
		}
	}
	close(data->fd[1]);
	free(cmd);
}

void	exec_middle_pipes(t_data *data, char **tab)
{
	char	*cmd;
	pid_t	pid;

	cmd = access_cmd(data, tab);
	if (!cmd)
		return (free(cmd), perror("access_cmd 2"));
	if (pipe(data->fd) == -1)
		return (perror("pipe 2"));
	pid = fork();
	if (pid == -1)
		return (perror("fork 2"));
	if (pid == 0)
	{
		close(data->fd[0]);
		if (dup2(data->fd[0], STDIN_FILENO) == -1
			|| dup2(data->fd[1], STDOUT_FILENO) == -1)
		{
			perror("dup2 2");
			exit(EXIT_FAILURE);
		}
		close(data->fd[0]);
		close(data->fd[1]);
		if (execve(cmd, tab, data->env) == -1)
		{
			perror("execve 2");
			exit(EXIT_FAILURE);
		}
	}
	close(data->fd[0]);
	close(data->fd[1]);
	free(cmd);
}

void	exec_last_pipe(t_data *data, char **tab)
{
	char	*cmd;
	pid_t	pid;

	cmd = access_cmd(data, tab);
	if (!cmd)
		return (free(cmd), perror("access_cmd 3"));
	pid = fork();
	if (pid == -1)
		return (perror("fork 3"));
	if (pid == 0)
	{
		if (dup2(data->fd[0], STDIN_FILENO) == -1)
		{
			perror("dup2 3");
			exit(EXIT_FAILURE);
		}
		close(data->fd[0]);
		if (execve(cmd, tab, data->env) == -1)
		{
			perror("execve 3");
			exit(EXIT_FAILURE);
		}
	}
	close(data->fd[0]);
	free(cmd);
}

void	pipex(t_data *data, char ***big_tab, int nb_blocks)
{
	int	i;

	i = 0;
	exec_first_pipe(data, big_tab[i]);
	i++;
	while (i < nb_blocks - 1)
	{
		exec_middle_pipes(data, big_tab[i]);
		i++;
	}
	exec_last_pipe(data, big_tab[i]);
	while (wait(NULL) != -1)
		continue ;
}


void	parse_line(t_data *data, char *line)
{
	int		i;
	int		nb_blocks;
	char	***big_tab;

	if (ft_strlen(line) == 0)
		return ;
	big_tab = get_big_tab(line);
	if (!big_tab)
		return ;
	nb_blocks = count_blocks(line);


	// expand(data);

	if (nb_blocks == 1)
	{
		if (check_builtins(data, *big_tab) == 0)
		{
			execute_cmd(data, *big_tab);
		}
	}
	else
		pipex(data, big_tab, nb_blocks);

	// else if (ft_tablen(data->input) > 1 && *data->input[1] == '>')
	// {
	// 	execute_cmd_out(data);
	// 	malloc_free(data->path);
	// }
	// else if (ft_tablen(data->input) > 1 && *data->input[1] == '<')
	// {
	// 	execute_cmd_in(data);
	// 	malloc_free(data->path);
	// }

	// i = 0;
	// while (i < nb_blocks)
	// {
	// 	int j = 0;
	// 	printf("INDEX I :%d\n", i);
	// 	while (big_tab[i][j])
	// 	{
	// 		printf("Bloc %d: [%s]\n", j + 1, big_tab[i][j]);
	// 		j++;
	// 	}
	// 	i++;
	// }

	i = 0;
	if (big_tab)
	{
		while (i < nb_blocks)
		{
			malloc_free(big_tab[i]);
			i++;
		}
		free(big_tab);
	}
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
	malloc_free(data.path);
}

// export a b -> export X env
//			pas de chiffres  symboles avant =
//			export les autres var si la 1ere existe deja
// echo var qui n'existe pas -> \n 
// var sans commandes

// line = /n || isspace
// sigignore dans le parent