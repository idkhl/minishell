/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: idakhlao <idakhlao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/20 17:26:34 by idakhlao          #+#    #+#             */
/*   Updated: 2024/11/06 15:59:17 by idakhlao         ###   ########.fr       */
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

void	update_env_var(char **env, char *var_name, char *new_value)
{
	int		i;
	size_t	name_len;

	i = 0;
	name_len = ft_strlen(var_name);
	while (env[i])
	{
		if (ft_strncmp(env[i], var_name, name_len) == 0)
		{
			free(env[i]);
			env[i] = malloc(name_len + ft_strlen(new_value) + 1);
			if (env[i])
			{
				ft_strcpy(env[i], var_name);
				ft_strlcat(env[i], new_value, name_len + \
				ft_strlen(new_value) + 1);
			}
			return ;
		}
		i++;
	}
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
	update_env_var(data->env, "OLDPWD=", oldpwd);
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
