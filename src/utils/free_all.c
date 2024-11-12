/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_all.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: idakhlao <idakhlao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 15:00:28 by afrikach          #+#    #+#             */
/*   Updated: 2024/11/12 10:37:25 by idakhlao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	free_all(t_input *input)
{
	int	i;

	i = 0;
	if (input == NULL)
		return ;
	while (input[i].input)
	{
		free(input[i].input);
		malloc_free(input[i].tab);
		malloc_free(input[i].cmd);
		free(input[i].in_file);
		free(input[i].out_file);
		free(input[i].redir_infile);
		free(input[i].redir_outfile);
		i++;
	}
	free(input);
}

void	free_child(t_data *data, t_input *input, char *cmd, int EXIT_CODE)
{
	malloc_free(data->env);
	free_all(input);
	free(cmd);
	data->exit_status = EXIT_CODE;
	exit(EXIT_CODE);
}
