/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afrikach <afrikach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/20 17:15:27 by idakhlao          #+#    #+#             */
/*   Updated: 2024/11/07 17:40:03 by afrikach         ###   ########.fr       */
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

void	build_echo(char **tab)
{
	int	i;
	int	nl;

	i = 1;
	nl = 0;
	while (tab [i] && ft_strncmp(tab[i], "-n", 2) == 0)
	{
		nl = check_echo(tab[i]);
		i++;
	}
	if (tab[i])
	{
		while (tab[i])
		{
			printf("%s", tab[i]);
			if (tab[i + 1])
				printf(" ");
			i++;
		}
	}
	if (nl == 0)
		printf("\n");
	g_signal = 0;
}
