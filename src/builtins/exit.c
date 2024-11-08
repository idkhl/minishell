/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: idakhlao <idakhlao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/23 02:20:49 by idakhlao          #+#    #+#             */
/*   Updated: 2024/11/08 12:38:10 by idakhlao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	check_exit_args(char *arg)
{
	int	i;

	i = 0;
	while (arg[i])
	{
		if (arg[i] == '-' || arg[i] == '+')
			i++;
		if (ft_isdigit(arg[i]) == 0)
			return (1);
		i++;
	}
	return (0);
}

int	exit_code(int nb, int neg)
{
	if (neg == 0)
	{
		if (nb >= 0 && nb <= 255)
			return (nb);
		if (nb > 255)
			return (nb % 256);
	}
	else
	{
		if (nb > 0 && nb <= 256)
			return (256 - nb);
		if (nb > 256)
		{
			printf ("[%d]\n", nb);
			nb = 256 - nb;
			return (nb % 256);
		}
	}
	return (0);
}

void	clean_exit(t_data *data, t_input *input, int nb)
{
	if (data->env)
		malloc_free(data->env);
	dup2(data->copy_stdin, STDIN_FILENO);
	dup2(data->copy_stdout, STDOUT_FILENO);
	close(data->copy_stdin);
	close(data->copy_stdout);
	free_all(input);
	exit(nb);
}

void	check_num_arg(t_data *data, t_input *input, char **tab, \
			unsigned long long nb)
{
	nb = ft_atoll(tab[1]);
	if ((check_exit_args(tab[1]) == 1)
		|| ((tab[1][0] == '-' && nb > (unsigned long long)(-LLONG_MIN))
			|| (tab[1][0] != '-' && nb > LLONG_MAX)
				|| ft_strlen(tab[1]) > 20))
	{
		printf("exit: %s: numeric argument required\n", tab[1]);
		clean_exit(data, input, 2);
	}
}

void	build_exit(t_data *data, t_input *input, char **tab)
{
	unsigned long long	nb;
	int					neg;

	nb = 0;
	if (tab[1])
		check_num_arg(data, input, tab, nb);
	if (ft_tablen(tab) > 2)
	{
		printf("exit: too many arguments\n");
		g_signal = 1;
		return ;
	}
	if (tab[1] && tab[1][0] == '-')
		neg = 1;
	else
		neg = 0;
	nb = exit_code(nb, neg);
	clean_exit(data, input, nb);
}
