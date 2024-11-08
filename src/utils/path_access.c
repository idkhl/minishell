/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_access.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: idakhlao <idakhlao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/23 02:23:31 by idakhlao          #+#    #+#             */
/*   Updated: 2024/11/08 13:33:57 by idakhlao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*get_pathline(t_data *data)
{
	int	i;

	i = 0;
	while (data->env[i])
	{
		if (ft_strncmp(data->env[i], "PATH=", 5) == 0)
			return (data->env[i]);
		i++;
	}
	return (NULL);
}

char	**get_path(t_data *data)
{
	char	*tmp;
	char	**path;

	tmp = get_pathline(data);
	if (!tmp)
		return (NULL);
	tmp += 5;
	path = ft_split(tmp, ':');
	if (!path)
		return (NULL);
	return (path);
}

char	*join_path_cmd(char *dir, char *cmd)
{
	char	*tmp;
	char	*full_cmd;

	tmp = ft_strjoin(dir, "/");
	full_cmd = NULL;
	if (tmp)
	full_cmd = ft_strjoin(tmp, cmd);
	free(tmp);
	return (full_cmd);
}

char	*access_cmd(t_data *data, char **tab)
{
	char	*bin;
	char	**path;
	int		i;

	i = 0;
	if (tab[0] && access(tab[0], F_OK | X_OK) == 0)
		return (ft_strdup(tab[0]));
	path = get_path(data);
	if (!path)
		return (NULL);
	while (path && path[i])
	{
		bin = join_path_cmd(path[i], tab[0]);
		if (!bin)
			return (malloc_free(path), NULL);
		if (access(bin, F_OK | X_OK) == 0)
			return (malloc_free(path), bin);
		free(bin);
		i++;
	}
	return (malloc_free(path), NULL);
}
