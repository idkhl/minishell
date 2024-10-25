/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: idakhlao <idakhlao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/06 18:07:15 by idakhlao          #+#    #+#             */
/*   Updated: 2024/10/25 20:25:55 by idakhlao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	free_child(t_data *data, t_input *input, char *cmd, int EXIT_CODE)
{
	malloc_free(data->env);
	malloc_free(data->path);
	free_all(input);
	free(cmd);
	exit(EXIT_CODE);
}
void	exec_first_pipe(t_data *data, t_input *input, char **tab, int i)
{
	char	*cmd;
	pid_t	pid;

	cmd = access_cmd(data, tab);
	pid = fork();
	if (pid == -1)
		return (perror("fork"));
	if (pid == 0)
	{
		if (input[i].in_file != NULL || input[i].out_file != NULL)
			redir(data, input, i);
		if (dup2(data->fd[1], STDOUT_FILENO) == -1)
		{
			perror("dup2 1");
			free_child(data, input, cmd, EXIT_FAILURE);
			// exit(EXIT_FAILURE);
		}
		close(data->fd[0]);
		close(data->fd[1]);
		close(data->copy_stdin);
		if (exec_builtins(data, tab) == 0)
		{
			if (!cmd)
			{
				printf("%s: command not found\n", tab[0]);
				free_child(data, input, cmd, 127);
				// exit(127);
			}
			if (execve(cmd, tab, data->env) == -1)
				free_child(data, input, cmd, 127);
				// exit(127);
		}
		else
			free_child(data, input, cmd, 0);
			// exit(0);
	}
	free(cmd);
}

void	exec_middle_pipes(t_data *data, t_input *input, char **tab, int i)
{
	char	*cmd;
	pid_t	pid;

	cmd = access_cmd(data, tab);
	pid = fork();
	if (pid == -1)
		return (perror("fork 2"));
	if (pid == 0)
	{
		close(data->copy_stdin);
		if (dup2(data->fd[1], STDOUT_FILENO) == -1)
		{
			perror("dup2 2");
			exit(EXIT_FAILURE);
		}
		close(data->fd[0]);
		close(data->fd[1]);
		if (input[i].in_file != NULL || input[i].out_file != NULL)
			redir(data, input, i);
		if (exec_builtins(data, tab) == 0)
		{
			if (!cmd)
			{
				printf("%s: command not found\n", tab[0]);
				free_child(data, input, cmd, 127);
				// exit(127);
			}
			if (execve(cmd, tab, data->env) == -1)
				free_child(data, input, cmd, 127);
				// exit(127);
		}
		else
			free_child(data, input, cmd, 0);
			// exit(0);
	}
	free(cmd);
}

void	exec_last_pipe(t_data *data, t_input *input, char **tab, int i)
{
	char	*cmd;
	pid_t	pid;

	cmd = access_cmd(data, tab);
	pid = fork();
	if (pid == -1)
		return (perror("fork 3"));
	if (pid == 0)
	{
		close(data->copy_stdin);
		close(data->fd[1]);
		close(data->fd[0]);
		if (input[i].in_file != NULL || input[i].out_file != NULL)
			redir(data, input, i);
		if (exec_builtins(data, tab) == 0)
		{
			if (!cmd)
			{
				printf("%s: command not found\n", tab[0]);
				free_child(data, input, cmd, 127);
				// exit(127);
			}
			if (execve(cmd, tab, data->env) == -1)
				free_child(data, input, cmd, 127);
				// exit(127);
		}
		else
			free_child(data, input, cmd, 0);

			// exit(0);
	}
	free(cmd);
}

void	pipex(t_data *data, t_input	*input, int nb_blocks)
{
	int	i;

	i = 0;
	data->copy_stdin = dup(STDIN_FILENO);
	while (i <= nb_blocks - 1)
	{
		if (pipe(data->fd) == -1)
			return (perror("pipe 1"));
		// int fd = open("out", O_CREAT | O_WRONLY);
		// dup2(fd, STDOUT_FILENO);
		// printf("%p\n", input);
		if (i == 0)
			exec_first_pipe(data, input, input[i].cmd, i);
		else if (i == nb_blocks - 1)
			exec_last_pipe(data, input, input[i].cmd, i);
		else
			exec_middle_pipes(data, input, input[i].cmd, i);
		if (dup2(data->fd[0], STDIN_FILENO) == -1)
			perror("FAIL - IN");
		close(data->fd[0]);
		close(data->fd[1]);
		i++;
	}
	dup2(data->copy_stdin, STDIN_FILENO);
	close(data->copy_stdin);
	while (wait(NULL) != -1)
		continue ;
}
