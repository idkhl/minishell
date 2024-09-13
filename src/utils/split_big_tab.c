/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_big_tab.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afrikach <afrikach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/13 15:19:09 by afrikach          #+#    #+#             */
/*   Updated: 2024/09/13 17:51:25 by afrikach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	allocate_and_copy_redir(t_input *input, char *line)
{
	int		i;
	int		j;
	int		nb_blocks;
	
	i = 0;
	nb_blocks = count_blocks(line);
	while (i < nb_blocks)
	{
		while (input[i].tab)
		{
			j = 0;
			if (ft_strcmp(input[i].tab[j], "<"))
				input[i].in_file = ft_strdup(input[i].tab[j + 1]);
			j++;
		}
		i++;
	}
}
