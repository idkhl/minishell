/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: idakhlao <idakhlao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/30 19:57:35 by idakhlao          #+#    #+#             */
/*   Updated: 2024/08/30 20:14:32 by idakhlao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	check_builtins(t_data *data, char **tab)
{
	if (ft_strcmp(*tab, "exit") == 0)
		return (build_exit(data, tab), 1);
	else if (ft_strcmp(*tab, "echo") == 0)
		return (build_echo(tab), 1);
	else if (ft_strcmp(*tab, "pwd") == 0)
		return (build_pwd(), 1);
	else if (ft_strcmp(*tab, "cd") == 0)
		return (build_cd(tab), 1);
	else if (ft_strcmp(*tab, "env") == 0)
		return (build_env(data), 1);
	else if (ft_strcmp(*tab, "export") == 0)
		return (build_export(data, tab), 1);
	else if (ft_strcmp(*tab, "unset") == 0)
		return (build_unset(data, tab), 1);
	else
		return (0);
}
