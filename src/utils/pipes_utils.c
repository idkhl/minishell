/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: idakhlao <idakhlao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 15:37:44 by idakhlao          #+#    #+#             */
/*   Updated: 2024/11/12 11:14:28 by idakhlao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_error_msg(char *s1, char *s2)
{
	ft_putstr_fd(s1, 2);
	ft_putendl_fd(s2, 2);
}

void	pipe_redir(t_data *data, t_input *input, int i)
{
	if (input[i].in_file != NULL || input[i].out_file != NULL)
	{
		if (redir(input, i, data) == 1)
		{
			malloc_free(data->env);
			free_all(input);
			data->exit_status = 1;
			close(data->fd[0]);
			close(data->fd[1]);
			exit(1);
		}
	}
}

void	restore_std_input(t_data *data)
{
	dup2(data->copy_stdin, STDIN_FILENO);
	close(data->copy_stdin);
	while (wait(NULL) != -1)
		continue ;
	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, handle_signals);
}

void	pipex(t_data *data, t_input *input, int nb_blocks)
{
	int	i;

	i = 0;
	data->copy_stdin = dup(STDIN_FILENO);
	while (i < nb_blocks)
		handle_pipe_block(data, input, i++, nb_blocks);
	restore_std_input(data);
}
