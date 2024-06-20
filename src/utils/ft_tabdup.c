/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tabdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: idakhlao <idakhlao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/20 17:09:41 by idakhlao          #+#    #+#             */
/*   Updated: 2024/06/20 17:11:14 by idakhlao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	**ft_tabdup(char **tab)
{
	char	**tmp;
	int		i;

	tmp = (char **)malloc(sizeof(char *) * (ft_tablen(tab) + 1));
	if (!tmp)
		return (NULL);
	i = 0;
	while (tab[i])
	{
		tmp[i] = ft_strdup(tab[i]);
		if (!tmp[i])
			return (NULL);
		i++;
	}
	tmp[i] = NULL;
	return (tmp);
}