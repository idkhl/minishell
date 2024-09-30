/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_redir_out.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: idakhlao <idakhlao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/05 16:31:39 by idakhlao          #+#    #+#             */
/*   Updated: 2024/09/04 18:20:29 by idakhlao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	output_redir(t_data *data)
{
	int	outfile;

	if (data->input[1] && ft_strcmp(data->input[1], ">") == 0)
		outfile = open(data->input[2], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (data->input[1] && ft_strcmp(data->input[1], ">>") == 0)
		outfile = open(data->input[2], O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (outfile < 0)
		return (perror("Open"));
	if (dup2(outfile, STDOUT_FILENO) == -1)
		return (close(outfile), perror("dup2"));
	close(outfile);
}

void	execute_cmd_out(t_data *data)
{
	char	*cmd;
	char	**tmp;
	pid_t	pid;

	cmd = access_cmd(data);
	if (!cmd)
		return (perror("access_cmd"));
	tmp = ft_split(data->input[0], ' ');
	if (!tmp)
		return (free(cmd));
	pid = fork();
	if (pid < 0)
		return (malloc_free(tmp), free(cmd), perror("fork"));
	if (pid == 0)
	{
		output_redir(data);
		if (execve(cmd, tmp, data->env) == -1)
			return (free(cmd), malloc_free(tmp), exit(EXIT_FAILURE));
	}
	else
	{
		waitpid(pid, NULL, 0);
		free(cmd);
		malloc_free(tmp);
	}
}
