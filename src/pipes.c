/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afrikach <afrikach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/06 18:07:15 by idakhlao          #+#    #+#             */
/*   Updated: 2024/11/07 13:23:03 by afrikach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	exec_pipe(t_data *data, t_input *input, char **tab, int i)
{
	char	*cmd;

	cmd = access_cmd(data, tab);
	if (ft_strcmp(tab[0], "/") == 0)
	{
		ft_putstr_fd(tab[0], 2);
		ft_putendl_fd(": is a directory", 2);
		free_child(data, input, cmd, 126);
	}
	if (exec_builtins(data, input, tab) == 0)
	{
		if (!cmd)
		{
			if ((tab != NULL && *tab != NULL)
				&& (!input[i].in_file
					|| ft_strcmp(input[i].redir_infile, "<<") != 0))
			{
				ft_putstr_fd(tab[0], 2);
				ft_putendl_fd(": command not found", 2);
			}
			free_child(data, input, cmd, 127);
		}
		if (execve(cmd, tab, data->env) == -1)
			free_child(data, input, cmd, 127);
	}
	else
		free_child(data, input, cmd, 0);
}

void	pipe_redir(t_data *data, t_input *input, int i)
{
	if (input[i].in_file != NULL || input[i].out_file != NULL)
	{
		if (redir(input, i, data) == 1)
		{
			malloc_free(data->env);
			free_all(input);
			g_signal = 1;
			exit(1);
		}
	}
}

void	exec_first_pipe(t_data *data, t_input *input, char **tab, int i)
{
	pid_t	pid;
	int		status;

	status = 0;
	signal(SIGINT, exec_signals);
	signal(SIGQUIT, exec_signals);
	pid = fork();
	if (pid == -1)
		return (perror("fork"));
	if (pid == 0)
	{
		if (dup2(data->fd[1], STDOUT_FILENO) == -1)
		{
			perror("dup2 1");
			free_all(input);
			exit(EXIT_FAILURE);
		}
		close(data->fd[0]);
		close(data->fd[1]);
		close(data->copy_stdin);
		pipe_redir(data, input, i);
		exec_pipe(data, input, tab, i);
	}
}

void	exec_middle_pipes(t_data *data, t_input *input, char **tab, int i)
{
	pid_t	pid;
	int		status;

	status = 0;
	signal(SIGINT, exec_signals);
	signal(SIGQUIT, exec_signals);
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
		pipe_redir(data, input, i);
		exec_pipe(data, input, tab, i);
	}
}

void	exec_last_pipe(t_data *data, t_input *input, char **tab, int i)
{
	pid_t	pid;
	int		status;

	status = 0;
	signal(SIGINT, exec_signals);
	signal(SIGQUIT, exec_signals);
	pid = fork();
	if (pid == -1)
		return (perror("fork 3"));
	if (pid == 0)
	{
		close(data->copy_stdin);
		close(data->fd[1]);
		close(data->fd[0]);
		pipe_redir(data, input, i);
		exec_pipe(data, input, tab, i);
	}
	else
	{
		waitpid(pid, &status, 0);
		if (WIFEXITED(status))
			g_signal = WEXITSTATUS(status);
	}
}

void	pipex(t_data *data, t_input	*input, int nb_blocks)
{
	int (i) = 0;
	data->copy_stdin = dup(STDIN_FILENO);
	while (i <= nb_blocks - 1)
	{
		if (pipe(data->fd) == -1)
			return (perror("pipe 1"));
		if (i == 0)
			exec_first_pipe(data, input, input[i].cmd, i);
		else if (i == nb_blocks - 1)
			exec_last_pipe(data, input, input[i].cmd, i);
		else
			exec_middle_pipes(data, input, input[i].cmd, i);
		if (i < nb_blocks - 1)
		{
			if (dup2(data->fd[0], STDIN_FILENO) == -1)
				return (perror("FAIL - IN"));
		}
		close(data->fd[0]);
		close(data->fd[1]);
		i++;
	}
	dup2(data->copy_stdin, STDIN_FILENO);
	close(data->copy_stdin);
	// while (wait(NULL) > 0);
	while (wait(NULL) != -1)
		continue ;
	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, handle_signals);
}
