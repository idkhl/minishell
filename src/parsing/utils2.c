/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afrikach <afrikach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/18 17:41:15 by afrikach          #+#    #+#             */
/*   Updated: 2024/10/18 17:41:49 by afrikach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	free_tab(char ***big_tab, int size)
{
	int	i;

	i = 0;
	if (big_tab)
	{
		while (i < size)
		{
			malloc_free(big_tab[i]);
			i++;
		}
		free(big_tab);
	}
}
