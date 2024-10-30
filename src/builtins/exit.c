/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: idakhlao <idakhlao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/23 02:20:49 by idakhlao          #+#    #+#             */
/*   Updated: 2024/10/30 12:38:03 by idakhlao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	build_exit(t_data *data, t_input *input, char **tab)
{
	unsigned long long	nb;

	nb = 0;
	(void)input;
	printf("exit\n");
	if (tab[1] && ft_isalpha(tab[1][0]) == 1)
		printf("exit: %s: numeric argument required\n", tab[1]);
	else if (tab[1] && tab[1][1] && ft_isdigit(tab[1][1]) != 1)
		printf("exit: %s: numeric argument required\n", tab[1]);
	else if (ft_tablen(tab) > 2)
	{
		printf("exit: too many arguments\n");
		return ;
	}
	// if (tab[1])
	// 	nb = ft_atoll(tab[1]);
	// if (tab[1])
	// 	printf("[%llu]\n", nb);
	// if (tab[1] && (nb > LLONG_MAX))
	// 	printf("exit: %s numeric argument requiredddd\n", tab[1]);
	if (tab[1])
	{
		nb = ft_atoll(tab[1]);
		printf("[%llu]\n", nb);
		printf("TEST[%llu]\n", (unsigned long long)(-LLONG_MIN));
		if (tab[1][0] == '-' && nb > (unsigned long long)(-LLONG_MIN))
		{
			printf("En dessous erreur\n");
		}
		else if (tab[1][0] != '-' && nb > LLONG_MAX)
		{
			printf("Au dessus erreur\n");
		}
		else
		{
			printf("RAS\n");
		}
		return ;
	}
	if (data->env)
		malloc_free(data->env);
	malloc_free(data->path);
	dup2(data->copy_stdin, STDIN_FILENO);
	dup2(data->copy_stdout, STDOUT_FILENO);
	close(data->copy_stdin);
	close(data->copy_stdout);
	free_all(input);
	exit(nb);
}
