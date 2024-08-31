/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_big_tab.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: idakhlao <idakhlao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/31 16:13:38 by idakhlao          #+#    #+#             */
/*   Updated: 2024/08/31 16:14:49 by idakhlao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	***get_big_tab(char *line)
{
	char	***result;
	int		i;
	int		nb_blocks;
	char	**tab;

	i = 0;
	tab = split_pipes(line);
	if (!tab)
		return (NULL);
	nb_blocks = count_blocks(line);
	result = (char ***)malloc((nb_blocks + 1) * sizeof(char **));
	if (!result)
	{
		perror("allocation failed\n");
		return (free(tab), NULL);
	}
	while (i < nb_blocks)
	{
		result[i] = split_quotes(tab[i], ' ');
		if (!result[i])
			return (malloc_free(tab), NULL);
		i++;
	}
	malloc_free(tab);
	return (result);
}
