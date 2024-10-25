/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_all.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: idakhlao <idakhlao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 15:00:28 by afrikach          #+#    #+#             */
/*   Updated: 2024/10/25 20:20:05 by idakhlao         ###   ########.fr       */
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
		// printf("input.input : %s\n", input[i].input);
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
