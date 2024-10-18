/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: idakhlao <idakhlao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/23 02:20:49 by idakhlao          #+#    #+#             */
/*   Updated: 2024/10/18 18:56:38 by idakhlao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	build_exit(t_data *data, char **tab)
{
	if (tab[1] && ft_isalpha(tab[1][0]) == 1)
		return (perror("error"));
	if (ft_tablen(tab) > 2)
		return (perror("error"));
	printf("exit\n");
	if (data->env)
		malloc_free(data->env);
	if (tab)
		malloc_free(tab);
	exit(0);
	return ;
}
