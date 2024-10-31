/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_access.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: idakhlao <idakhlao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/23 02:23:31 by idakhlao          #+#    #+#             */
/*   Updated: 2024/10/30 17:18:47 by idakhlao         ###   ########.fr       */
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

char	*access_cmd(t_data *data, char **tab)
{
	char	*bin;
	char	*tmp;
	char	**path;
	int		i;

	i = 0;
	path = get_path(data);
	if (!path)
		return (NULL);
	if (tab[0] && access(tab[0], F_OK | X_OK) == 0)
		return (ft_strdup(tab[0]));
	while (path && path[i])
	{
		tmp = ft_strjoin(path[i], "/");
		if (!tmp)
			return (malloc_free(path), NULL);
		bin = ft_strjoin(tmp, tab[0]);
		if (!bin)
			return (free(tmp), malloc_free(path), NULL);
		free(tmp);
		if (access(bin, F_OK | X_OK) == 0)
			return (malloc_free(path), bin);
		free(bin);
		i++;
	}
	malloc_free(path);
	return (NULL);
}
