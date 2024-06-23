/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: idakhlao <idakhlao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/23 02:20:49 by idakhlao          #+#    #+#             */
/*   Updated: 2024/06/23 02:22:03 by idakhlao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	build_exit(t_data *data)
{
	if (data->input[1] && ft_isalpha(data->input[1][0]) == 1)
		return (perror("error"));
	if (ft_tablen(data->input) > 2)
		return (perror("error"));
	printf("exit\n");
	if (data->env)
		malloc_free(data->env);
	if (data->input)
		malloc_free(data->input);
	exit(0);
	return ;
}
