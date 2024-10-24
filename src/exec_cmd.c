/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: idakhlao <idakhlao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/05 16:36:50 by idakhlao          #+#    #+#             */
/*   Updated: 2024/10/24 14:10:20 by idakhlao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	execute_cmd(t_data *data, t_input *input, char **tab)
{
	char	*cmd;
	pid_t	pid;

	cmd = access_cmd(data, tab);
	signal(SIGINT, exec_signals);
	signal(SIGQUIT, exec_signals);
	pid = fork();
	if (pid < 0)
		return (free(cmd), perror("fork"));
	if (pid == 0)
	{
		if (input[0].in_file != NULL || input[0].out_file != NULL)
			redir(data, input, 0);
		if (!cmd)
		{
			if (!input[0].in_file || ft_strcmp(input[0].redir_infile, "<<") != 0)
				printf("%s: command not found\n", tab[0]);
			return (exit(127));
		}
		if (execve(cmd, tab, data->env) == -1)
			return (free(cmd), exit(EXIT_FAILURE));
	}
	else
	{
		signal(SIGQUIT, SIG_IGN);
		waitpid(pid, NULL, 0);
		signal(SIGINT, handle_signals);
		free(cmd);
	}
}
