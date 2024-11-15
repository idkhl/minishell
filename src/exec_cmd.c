/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: idakhlao <idakhlao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/05 16:36:50 by idakhlao          #+#    #+#             */
/*   Updated: 2024/11/14 11:10:08 by idakhlao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	exec_pid(t_input *input, t_data *data, char **tab, char *cmd)
{
	if (input[0].in_file != NULL || input[0].out_file != NULL)
	{
		if (redir(input, 0, data) == 1)
			return (free_child(data, input, cmd, 1), 1);
	}
	if (tab[0] && ft_strcmp(tab[0], "/") == 0)
	{
		ft_error_msg(tab[0], ": is a directory");
		return (free_child(data, input, cmd, 126), 126);
	}
	if (!tab[0])
		return (free_child(data, input, cmd, 0), 0);
	if (!cmd)
	{
		ft_error_msg(tab[0], ": command not found");
		return (free_child(data, input, cmd, 127), 127);
	}
	if (execve(cmd, tab, data->env) == -1)
		return (free_child(data, input, cmd, 1), 1);
	return (0);
}

void	execute_cmd(t_data *data, t_input *input, char **tab)
{
	char	*cmd;
	pid_t	pid;
	int		status;

	status = 0;
	cmd = access_cmd(data, tab);
	signal(SIGINT, exec_signals);
	signal(SIGQUIT, exec_signals);
	pid = fork();
	if (pid < 0)
		return (free(cmd), perror("fork"));
	if (pid == 0)
		status = exec_pid(input, data, tab, cmd);
	else
	{
		waitpid(pid, &status, 0);
		if (WIFEXITED(status))
			g_signal = WEXITSTATUS(status);
		signal(SIGQUIT, SIG_IGN);
		signal(SIGINT, handle_signals);
		free(cmd);
	}
}
