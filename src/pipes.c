/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: idakhlao <idakhlao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/06 18:07:15 by idakhlao          #+#    #+#             */
/*   Updated: 2024/10/02 18:03:29 by idakhlao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	exec_first_pipe(t_data *data, t_input *input, char **tab, int i)
{
	char	*cmd;
	pid_t	pid;

	cmd = access_cmd(data, tab);
	if (!cmd)
		return (free(cmd), perror("access_cmd 1"));
	if (pipe(data->fd) == -1)
		return (perror("pipe 1"));
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
		if (input[i].in_file != NULL || input[i].out_file != NULL)
			redir(data, input, i);
		if (check_builtins(data, tab) == 0)
		{
			if (execve(cmd, tab, data->env) == -1)
			{
				perror("execve 1");
				exit(EXIT_FAILURE);
			}
		}
		else
			exit(EXIT_SUCCESS);
	}
	close(data->fd[1]);
	free(cmd);
}

void	exec_middle_pipes(t_data *data, t_input *input, char **tab, int i)
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
		if (input[i].in_file != NULL || input[i].out_file != NULL)
			redir(data, input, i);
		if (check_builtins(data, tab) == 0)
		{
			if (execve(cmd, tab, data->env) == -1)
			{
				perror("execve 1");
				exit(EXIT_FAILURE);
			}
		}
		else
			exit(EXIT_SUCCESS);
	}
	close(data->fd[0]);
	close(data->fd[1]);
	free(cmd);
}

void	exec_last_pipe(t_data *data, t_input *input, char **tab, int i)
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
		if (input[i].in_file != NULL || input[i].out_file != NULL)
			redir(data, input, i);
		if (check_builtins(data, tab) == 0)
		{
			if (execve(cmd, tab, data->env) == -1)
			{
				perror("execve 1");
				exit(EXIT_FAILURE);
			}
		}
		else
			exit(EXIT_SUCCESS);
	}
	close(data->fd[0]);
	free(cmd);
}

void	pipex(t_data *data, t_input	*input, int nb_blocks)
{
	int	i;

	i = 0;
	while (i <= nb_blocks - 1)
	{
		// printf("cmd : %s\n", input[i].cmd[0]);
		if (i == 0)
			exec_first_pipe(data, input, input[i].cmd, i);
		else if (i == nb_blocks - 1)
			exec_last_pipe(data, input, input[i].cmd, i);
		else
			exec_middle_pipes(data, input, input[i].cmd, i);
		i++;
	}
	while (wait(NULL) != -1)
		continue ;
}
