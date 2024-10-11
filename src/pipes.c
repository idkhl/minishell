/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: idakhlao <idakhlao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/06 18:07:15 by idakhlao          #+#    #+#             */
/*   Updated: 2024/10/11 18:39:24 by idakhlao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	exec_first_pipe(t_data *data, t_input *input, char **tab, int i)
{
	char	*cmd;
	pid_t	pid;

	cmd = access_cmd(data, tab);
	// if (!cmd)
	// 	return (free(cmd), perror("access_cmd 1"));
	pid = fork();
	if (pid == -1)
		return (perror("fork 1"));
	if (pid == 0)
	{
		if (input[i].in_file != NULL || input[i].out_file != NULL)
			redir(data, input, i);
		if (dup2(data->fd[1], STDOUT_FILENO) == -1)
		{
			perror("dup2 1");
			exit(EXIT_FAILURE);
		}
		close(data->fd[0]);
		close(data->fd[1]);
		close(data->copy_stdin);
		if (exec_builtins(data, tab) == 0)
		{
			if (cmd)
			{
				if (execve(cmd, tab, data->env) == -1)
				{
					perror("execve 1");
					exit(EXIT_FAILURE);
				}
			}
		}
		else
			exit(EXIT_SUCCESS);
	}
	free(cmd);
}

void	exec_middle_pipes(t_data *data, t_input *input, char **tab, int i)
{
	char	*cmd;
	pid_t	pid;

	cmd = access_cmd(data, tab);
	// if (!cmd)
	// 	return (free(cmd), perror("access_cmd 2"));
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
			if (cmd)
			{
				if (execve(cmd, tab, data->env) == -1)
				{
					perror("execve 2");
					exit(EXIT_FAILURE);
				}
			}
		}
		else
			exit(EXIT_SUCCESS);
	}
	free(cmd);
}

void	exec_last_pipe(t_data *data, t_input *input, char **tab, int i)
{
	char	*cmd;
	pid_t	pid;

	cmd = access_cmd(data, tab);
	// if (!cmd)
	// 	return (free(cmd), perror("access_cmd 3"));
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
			if (cmd)
			{
				if (execve(cmd, tab, data->env) == -1)
				{
					perror("execve 3");
					exit(EXIT_FAILURE);
				}
			}
		}
		else
			exit(EXIT_SUCCESS);
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
		printf("1\n");
		if (pipe(data->fd) == -1)
			return (perror("pipe 1"));
		if (input[i].redir_infile
			&& ft_strcmp(input[i].redir_infile, "<<") == 0)
		{
			heredoc(input, i);
		}
		printf("pipe 0 = %d | pipe 1 = %d\n", data->fd[0], data->fd[1]);
		if (i == 0)
			exec_first_pipe(data, input, input[i].cmd, i);
		else if (i == nb_blocks - 1)
			exec_last_pipe(data, input, input[i].cmd, i);
		else
			exec_middle_pipes(data, input, input[i].cmd, i);
		i++;
		printf("fd 0 = %d\n", data->fd[0]);
		if (dup2(data->fd[0], STDIN_FILENO) == -1)
			perror("FAIL - IN");
		close(data->fd[0]);
		close(data->fd[1]);
	}
	dup2(data->copy_stdin, STDIN_FILENO);
	close(data->copy_stdin);
	while (wait(NULL) != -1)
		continue ;
}
