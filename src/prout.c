/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prout.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: idakhlao <idakhlao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/14 16:29:31 by idakhlao          #+#    #+#             */
/*   Updated: 2024/08/31 18:07:41 by idakhlao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	init_struct(t_data *data, char **envp)
{
	data->env = ft_tabdup(envp);
	if (!data->env)
		return ;
	data->exp = NULL;
	data->path = NULL;
}

void	exec_pipes(t_data *data, char **tab, int i, int nb_blocks)
{
	char	*cmd;
	char	**tmp;

	data->path = get_path(data);
	cmd = access_cmd(data, tab);
	tmp = ft_split(tab[0], ' ');
	if (!tmp)
		return ;
	if (!cmd)
		return (malloc_free(tmp), perror("access_cmd"));
	if (i == nb_blocks - 1)
	{
		if (dup2(data->fd[0], STDIN_FILENO) == -1)
			return (perror("dup2 - 4"));
		close(data->fd[0]);
		close(data->fd[1]);
	}
	else
	{
		if (dup2(data->fd[1], STDOUT_FILENO) == -1)
			return (perror("dup2 - 3"));
		close(data->fd[0]);
		close(data->fd[1]);
	}
	if (execve(cmd, tab, data->env) == -1)
		return (perror("execve"), _exit(EXIT_FAILURE));
}

void	pipex(t_data *data, char ***big_tab, int nb_blocks)
{
	int		i;
	pid_t	pid;
	int		prev_fd;

	i = 0;
	prev_fd = -1;
	while (i < nb_blocks - 1)
	{
		if (i < nb_blocks - 1)
		{
			if (pipe(data->fd) == -1)
			return (perror("pipe"));
		}
		pid = fork();
		if (pid == -1)
			return (perror("fork"));
		if (pid == 0)
		{
			if (i > 0)
			{
				if (dup2(prev_fd, STDIN_FILENO) == -1)
					return (perror("dup2 - 1"));
				close(prev_fd);
			}
			if (i < nb_blocks - 1)
			{
				if (dup2(data->fd[1], STDOUT_FILENO) == -1)
					return (perror("dup2" - 2));
			}
			close(data->fd[0]);
			close(data->fd[1]);
			exec_pipes(data, big_tab[i], i, nb_blocks);
		}
		else
		{
			close(data->fd[1]);
			if (i != 0)
				close(prev_fd);
			prev_fd = data->fd[0];
		}
		i++;
	}
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

	i = 0;
	if (nb_blocks == 1)
	{
		if (check_builtins(data, big_tab[i]) == 0)
		{
			execute_cmd(data, big_tab[i]);
			malloc_free(data->path);
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

// void	exec_pipes(t_data *data, char **tab)
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
// 	if (execve(cmd, tab, data->env) == -1)
// 		return (perror("execve"), _exit(EXIT_FAILURE));
// 	(void)data;
// }

// void	pipex(t_data *data, char ***big_tab, int nb_blocks)
// {
// 	int		i;
// 	pid_t	pid;
// 	int		status;

// 	i = 0;
// 	while (i < nb_blocks - 1)
// 	{
// 		if (pipe(data->fd) == -1)
// 			return (perror("pipe"));
// 		pid = fork();
// 		if (pid == -1)
// 			return (perror("fork"));
// 		if (pid == 0)
// 		{
// 			close(data->fd[0]);
// 			if (dup2(data->fd[1], STDOUT_FILENO) == -1)
// 				return (perror("dup2"), _exit(EXIT_FAILURE));
// 			close(data->fd[1]);
// 			exec_pipes(data, big_tab[i]);
// 		}
// 		else
// 		{
// 			close(data->fd[1]);
// 			if (dup2(data->fd[0], STDIN_FILENO) == -1)
// 				return (perror("dup2"));
// 			close(data->fd[0]);
// 			waitpid(pid, &status, 0);
// 		}
// 		i++;
// 	}
// 	exec_pipes(data, big_tab[i]);
// 	while (waitpid(-1, &status, WUNTRACED) > 0);
// }

int	main(int ac, char **av, char **envp)
{
	char	*line;
	t_data	data;

	init_struct(&data, envp);
	handle_signals();
	// signal(SIGPIPE, SIG_IGN);
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