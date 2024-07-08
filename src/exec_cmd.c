/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: idakhlao <idakhlao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/05 16:36:50 by idakhlao          #+#    #+#             */
/*   Updated: 2024/07/05 16:37:23 by idakhlao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	execute_cmd(t_data *data)
{
	int		i;
	char	*cmd;
	char	**tmp;
	pid_t	pid;

	i = 0;
	data->path = get_path(data);
	cmd = access_cmd(data);
	tmp = ft_split(data->input[0], ' ');
	if (!tmp)
		return ;
	if (!cmd)
		return (malloc_free(tmp), perror("access_cmd"));
	pid = fork();
	if (pid < 0)
		return (malloc_free(tmp), free(cmd), perror("fork"));
	if (pid == 0)
	{
		// handle_signals();
		if (execve(cmd, data->input, data->env) == -1)
		{
			malloc_free(data->path);
			return (free(cmd), malloc_free(tmp), exit(EXIT_FAILURE));
		}
	}
	else
	{
		waitpid(pid, NULL, 0);
		free(cmd);
		malloc_free(tmp);
	}
}