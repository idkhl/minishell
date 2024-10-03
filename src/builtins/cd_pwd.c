/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: idakhlao <idakhlao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/20 17:26:34 by idakhlao          #+#    #+#             */
/*   Updated: 2024/10/03 15:46:16 by idakhlao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	build_pwd(void)
{
	char	buf[1000];
	char	*s;

	s = "error";
	if (getcwd(buf, 1000) == NULL)
		return (perror(s));
	printf("%s\n", buf);
}

void	build_cd(char **tab)
{
	char	*s;

	s = "error";
	if (ft_tablen(tab) == 1)
	{
		chdir("/home/idakhlao");
		return ;
	}
	if (chdir(tab[1]) != 0)
		return (perror(s));
}


// cd .. / ls