/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_redir_in.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: idakhlao <idakhlao@student.42.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/05 16:34:44 by idakhlao          #+#    #+#             */
/*   Updated: 2024/07/08 16:17:42 by idakhlao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	here_doc(t_data *data)
{
	char	*line;

	line = readline("> ");
	data->heredoc = open(".tmp_doc", O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (data->heredoc == -1)
		return ;
	while (line)
	{
		// heredoc_signals();
		if (ft_strcmp(line, data->input[2]) == 0)
		{
			free(line);
			break ;
		}
		write(data->heredoc, line, ft_strlen(line));
		write(data->heredoc, "\n", 1); 
		free(line);
		line = readline("> ");
	}
	close(data->heredoc);
}

void	input_redir(t_data *data)
{
	int	infile;
	int	heredoc_infile;

	if (data->input[1] && ft_strcmp(data->input[1], "<") == 0)
	{
		infile = open(data->input[2], O_RDONLY, 0644);
		if (infile < 0)
			return (perror("Open"));
		if (dup2(infile, STDIN_FILENO) == -1)
			return (close(infile), perror("dup2"));
		close(infile);
	}
	if (data->input[1] && ft_strcmp(data->input[1], "<<") == 0)
	{
		here_doc(data);
		heredoc_infile = open(".tmp_doc", O_RDONLY);
		if (heredoc_infile < 0)
			return (perror("heredoc read open"));
		if (dup2(heredoc_infile, STDIN_FILENO) == -1)
			return (close(heredoc_infile), perror("dup2"));
		close(heredoc_infile);
		unlink(".tmp_doc");
	}
}

void	execute_cmd_in(t_data *data)
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
		heredoc_signals();
		input_redir(data);
		if (execve(cmd, tmp, data->env) == -1)
			return (free(cmd), malloc_free(tmp), perror("exec"));
	}
	else
	{
		waitpid(pid, NULL, 0);
		free(cmd);
		malloc_free(tmp);
	}
}

	// else if (ft_tablen(data->input) > 1 && *data->input[1] == '>')
	// {
	// 	execute_cmd_out(data);
	// 	malloc_free(data->path);
	// }
	// else if (ft_tablen(data->input) > 1 && *data->input[1] == '<')
	// {
	// 	execute_cmd_in(data);
	// 	malloc_free(data->path);
	// }
