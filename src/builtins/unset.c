/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: idakhlao <idakhlao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/20 17:36:46 by idakhlao          #+#    #+#             */
/*   Updated: 2024/10/24 14:09:47 by idakhlao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	unset_var(t_data *data, int i)
{
	if (data->env[i] == NULL)
		return ;
	free(data->env[i]);
	while (data->env[i + 1])
	{
		data->env[i] = ft_strdup(data->env[i + 1]);
		free(data->env[i + 1]);
		i++;
	}
	data->env[i] = NULL;
}

void	build_unset(t_data *data, char **tab)
{
	int	i;
	int	j;

	j = 1;
	while (tab[j])
	{
		i = 0;
		while (data->env[i])
		{
			if (ft_strncmp(tab[j], data->env[i], ft_strlen(tab[j])) == 0
				&& data->env[i][ft_strlen(tab[j])] == '=')
			{
				unset_var(data, i);
				break ;
			}
			i++;
		}
		j++;
	}
}
