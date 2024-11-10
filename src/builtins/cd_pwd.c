/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: idakhlao <idakhlao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/20 17:26:34 by idakhlao          #+#    #+#             */
/*   Updated: 2024/11/10 22:30:41 by idakhlao         ###   ########.fr       */
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

char	*get_home(t_data *data)
{
	int		i;
	char	*home;

	i = 0;
	while (data->env[i])
	{
		if (ft_strncmp(data->env[i], "HOME=", 5) == 0)
		{
			home = ft_strdup(data->env[i] + 5);
			return (home);
		}
		i++;
	}
	return (NULL);
}

void	build_cd(t_data *data, char **tab)
{
	char	*home;

	update_oldpwd(data);
	if (ft_tablen(tab) == 1)
	{
		home = get_home(data);
		if (!home)
		{
			g_signal = 1;
			ft_error_msg(tab[0], ": HOME not set");
			return ;
		}
		chdir(home);
		update_pwd(data);
		free(home);
		data->exit_status = 0;
		return ;
	}
	if (chdir(tab[1]) != 0)
	{
		data->exit_status = 1;
		return (perror(tab[1]));
	}
	update_pwd(data);
	data->exit_status = 0;
}
