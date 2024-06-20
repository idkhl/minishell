/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: idakhlao <idakhlao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/20 17:15:27 by idakhlao          #+#    #+#             */
/*   Updated: 2024/06/20 17:16:22 by idakhlao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	check_echo(char *str)
{
	int	i;

	i = 1;
	while (str[i])
	{
		if (str[i] != 'n')
		{
			printf("%s ", str);
			return (0);
		}
		i++;
	}
	return (1);
}

void	build_echo(t_data *data)
{
	int	i;
	int	nl;

	i = 0;
	nl = 0;
	if (ft_strcmp(data->input[i], "echo") == 0)
		i++;
	while (data->input[i] && ft_strncmp(data->input[i], "-n", 2) == 0)
	{
		nl = check_echo(data->input[i]);
		i++;
	}
	if (data->input[i])
	{
		while (data->input[i])
		{
			printf("%s", data->input[i]);
			if (data->input[i + 1])
				printf(" ");
			i++;
		}
	}
	if (nl == 0)
		printf("\n");
}
