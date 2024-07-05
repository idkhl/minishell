/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: idakhlao <idakhlao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/22 22:09:40 by idakhlao          #+#    #+#             */
/*   Updated: 2024/07/04 17:41:42 by idakhlao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	expand_variable(t_data *data, char *var, char *input, int i)
{
	char	*new;
	int		size;

	size = ft_strlen(var) - ft_strlen(input);
	new = ft_substr(var, ft_strlen(input), size);
	if (!new)
		return ;
	free(data->input[i]);
	data->input[i] = ft_strdup(new);
	free(new);
}

void	check_expand(t_data *data, int i, int j)
{
	char	*var;

	var = ft_substr(data->input[i], 1, (ft_strlen(data->input[i]) - 1));
	if (!var)
		return ;
	if (ft_strncmp(var, data->env[j], ft_strlen(data->input[i]) - 1) == 0)
		expand_variable(data, data->env[j], data->input[i], i);
	free(var);
}

void	expand(t_data *data)
{
	int		i;
	int		j;

	i = 0;
	while (data->input[i])
	{
		j = 0;
		while (data->env[j])
		{
			if (*data->input[i] == '$')
				check_expand(data, i, j);
			j++;
		}
		i++;
	}
}

//expand var qui n'existe pas -> = null
