/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: idakhlao <idakhlao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/06 18:07:15 by idakhlao          #+#    #+#             */
/*   Updated: 2024/11/12 12:58:01 by idakhlao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	exec_pipe(t_data *data, t_input *input, char **tab, int i)
{
	char	*cmd;

	cmd = access_cmd(data, tab);
	if (tab[0] && ft_strcmp(tab[0], "/") == 0)
		return (ft_error_msg(tab[0], ": is a directory"), \
			free_child(data, input, cmd, 126));
	if (exec_builtins(data, input, tab) != 0)
		return (free_child(data, input, cmd, 0));
	if (!tab[0])
		return (free_child(data, input, cmd, 0));
	if (!cmd)
	{
		if (tab[0]
			&& (!input[i].in_file
				|| ft_strcmp(input[i].redir_infile, "<<") != 0))
			ft_error_msg(tab[0], ": command not found");
		close(data->fd[0]);
		close(data->fd[1]);
		return (free_child(data, input, cmd, 127));
	}
	if (execve(cmd, tab, data->env) == -1)
		free_child(data, input, cmd, 127);
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

void	handle_pipe_block(t_data *data, t_input *input, int i, int nb_blocks)
{
	if (pipe(data->fd) == -1)
		return (perror("pipe 1"));
	if (i == 0)
		exec_first_pipe(data, input, input[i].cmd, i);
	else if (i == nb_blocks - 1)
		exec_last_pipe(data, input, input[i].cmd, i);
	else
		exec_middle_pipes(data, input, input[i].cmd, i);
	if (i < nb_blocks - 1 && dup2(data->fd[0], STDIN_FILENO) == -1)
		return (perror("FAIL - IN"));
	close(data->fd[0]);
	close(data->fd[1]);
}
