/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: idakhlao <idakhlao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/26 17:23:01 by idakhlao          #+#    #+#             */
/*   Updated: 2024/11/04 18:43:08 by idakhlao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	check_var_is_valid(char *var)
{
	int	i;

	// if (ft_strchr(var, '=') == 0)
	// 	return (-1);
	if (ft_isdigit(var[0]))
		return (-1);
	if (var[0] == '=')
		return (-1);
	i = 0;
	while (var[i] && var[i] != '=')
	{
		if (!ft_isalnum(var[i]) && var[i] != '_' && var[i] != '"')
			return (-1);
		i++;
	}
	// if (var[i] == '=')
	// 	i++;
	// while (var[i] != '\0')
	// {
	// 	if (!ft_isalnum(var[i]) && var[i] != '_' && var[i] != '"')
	// 		return (-1);
	// 	i++;
	// }
	return (0);
}

char	*var_name(char	*var)
{
	char	*tmp;
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (var[i] && var[i] != '=')
		i++;
	tmp = (char *)malloc(sizeof(char) * (i - j + 2));
	if (!tmp)
		return (NULL);
	while (j < i)
	{
		tmp[j] = var[j];
		j++;
	}
	tmp[j] = '\0';
	return (tmp);
}
