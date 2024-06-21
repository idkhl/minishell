/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: idakhlao <idakhlao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/20 17:36:46 by idakhlao          #+#    #+#             */
/*   Updated: 2024/06/21 13:32:27 by idakhlao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	build_unset(t_data *data)
{
	int	i;
	int	j;

	j = 1;
	while (j < ft_tablen(data->input))
	{
		i = 0;
		while (data->env[i])
		{
			if (ft_strncmp(data->input[j], data->env[i], \
				ft_strlen(data->input[j])) == 0
				&& data->env[i][ft_strlen(data->input[j])] == '=')
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
			i++;
		}
		j++;
	}
}
