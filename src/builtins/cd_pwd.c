/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: idakhlao <idakhlao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/20 17:26:34 by idakhlao          #+#    #+#             */
/*   Updated: 2024/11/01 16:51:06 by idakhlao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	build_pwd(void)
{
	char	buf[1000];

	if (getcwd(buf, 1000) == NULL)
		return (perror("error"));
	printf("%s\n", buf);
}

void	update_oldpwd(t_data *data)
{
	int		i;
	char	*oldpwd;

	i = 0;
	oldpwd = NULL;
	while (data->env[i])
	{
		if (ft_strncmp(data->env[i], "PWD=", 4) == 0)
		{
			oldpwd = ft_strdup(data->env[i] + 4);
			break ;
		}
		i++;
	}
	if (!oldpwd)
		return ;
	i = 0;
	while (data->env[i])
	{
		if (ft_strncmp(data->env[i], "OLDPWD=", 7) == 0)
		{
			free(data->env[i]);
			data->env[i] = malloc(strlen("OLDPWD=") + strlen(oldpwd) + 1);
			if (data->env[i])
			{
				ft_strcpy(data->env[i], "OLDPWD=");
				ft_strlcat(data->env[i], oldpwd, ft_strlen("OLDPWD=") \
				+ ft_strlen(oldpwd) + 1);
			}
			free(oldpwd);
			return ;
		}
		i++;
	}
	free(oldpwd);
}

void	update_pwd(t_data *data)
{
	char	cwd[1000];
	int		i;

	if (getcwd(cwd, sizeof(cwd)) == NULL)
	{
		perror("getcwd");
		return ;
	}
	i = 0;
	while (data->env[i])
	{
		if (ft_strncmp(data->env[i], "PWD=", 4) == 0)
		{
			free(data->env[i]);
			data->env[i] = malloc(strlen("PWD=") + strlen(cwd) + 1);
			if (data->env[i])
			{
				ft_strcpy(data->env[i], "PWD=");
				ft_strlcat(data->env[i], cwd, strlen("PWD=") + strlen(cwd) + 1);
			}
			return ;
		}
		i++;
	}
}

void	build_cd(t_data *data, char **tab)
{
	update_oldpwd(data);
	if (ft_tablen(tab) == 1)
	{
		chdir("/home/idakhlao");
		update_pwd(data);
		return ;
	}
	if (chdir(tab[1]) != 0)
	{
		g_signal = 1;
		return (perror(tab[1]));
	}
	update_pwd(data);
	g_signal = 0;
}
