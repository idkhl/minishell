/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: idakhlao <idakhlao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/05 16:36:50 by idakhlao          #+#    #+#             */
/*   Updated: 2024/09/30 15:41:24 by idakhlao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	execute_cmd(t_data *data, t_input *input, char **tab)
{
	char	*cmd;
	pid_t	pid;

	cmd = access_cmd(data, tab);
	if (!cmd)
		return (perror("access_cmd"));
	pid = fork();
	if (pid < 0)
		return (free(cmd), perror("fork"));
	if (pid == 0)
	{
		// handle_signals();
		redir(data, input, 0);
		if (execve(cmd, tab, data->env) == -1)
			return (free(cmd), exit(EXIT_FAILURE));
	}
	else
	{
		waitpid(pid, NULL, 0);
		free(cmd);
	}
}
