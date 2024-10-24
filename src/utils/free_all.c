/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_all.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afrikach <afrikach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 15:00:28 by afrikach          #+#    #+#             */
/*   Updated: 2024/10/23 15:04:35 by afrikach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	free_all(t_input *input)
{
	free(input->redir_infile);
	free(input->redir_outfile);
	free(input->in_file);
	free(input->out_file);
	malloc_free(input->cmd);
	malloc_free(input->tab);
	free(input->input);
}
