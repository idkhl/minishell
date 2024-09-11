/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inesdakhlaoui <inesdakhlaoui@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/05 16:36:50 by idakhlao          #+#    #+#             */
/*   Updated: 2024/09/11 10:29:40 by inesdakhlao      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	execute_cmd(t_data *data, char **tab)
{
	char	*cmd;
	pid_t	pid;

	redir(data, tab);
	cmd = access_cmd(data, tab);
	if (!cmd)
		return (perror("access_cmd"));
	pid = fork();
	if (pid < 0)
		return (free(cmd), perror("fork"));
	if (pid == 0)
	{
		if (execve(cmd, tab, data->env) == -1)
			return (free(cmd), exit(EXIT_FAILURE));
	}
	else
	{
		waitpid(pid, NULL, 0);
		free(cmd);
	}
}
