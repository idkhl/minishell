/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: idakhlao <idakhlao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/20 17:36:46 by idakhlao          #+#    #+#             */
/*   Updated: 2024/08/30 19:38:53 by idakhlao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	unset_var(t_data *data, int i)
{
	if (data->env[i + 1] == NULL)
	{
		free(data->env[i]);
		data->env[i] = NULL;
	}
	while (data->env[i + 1])
	{
		free(data->env[i]);
		data->env[i] = ft_strdup(data->env[i + 1]);
		i++;
	}
	data->env[i + 1] = NULL;
}

void	build_unset(t_data *data, char **tab)
{
	int	i;
	int	j;

	j = 1;
	while (j < ft_tablen(tab))
	{
		i = 0;
		while (data->env[i])
		{
			if (ft_strncmp(tab[j], data->env[i], \
				ft_strlen(tab[j])) == 0
				&& data->env[i][ft_strlen(tab[j])] == '=')
				unset_var(data, i);
			i++;
		}
		j++;
	}
}
