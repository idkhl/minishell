/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_all.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afrikach <afrikach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 15:00:28 by afrikach          #+#    #+#             */
/*   Updated: 2024/10/23 17:09:27 by afrikach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	free_all(t_input *input, char *line)
{
	int	i;
	int	nb;

	i = 0;
	nb = count_blocks(line);
	while (i < nb)
	{
		free(input[i].redir_infile);
		free(input[i].redir_outfile);
		free(input[i].in_file);
		free(input[i].out_file);
		malloc_free(input[i].cmd);
		malloc_free(input[i].tab);
		free(input[i].input);
		i++;
	}
}
