/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: idakhlao <idakhlao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/20 17:34:28 by idakhlao          #+#    #+#             */
/*   Updated: 2024/08/30 19:36:50 by idakhlao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	print_export(t_data *data)
{
	int		i;
	int		j;
	char	*temp;

	i = 0;
	while (data->exp[i] != 0)
	{
		j = i;
		while (data->exp[j] != 0)
		{
			if (ft_strcmp(data->exp[i], data->exp[j]) > 0)
			{
				temp = data->exp[i];
				data->exp[i] = data->exp[j];
				data->exp[j] = temp;
			}
			j++;
		}
		i++;
	}
	i = -1;
	while (data->exp[++i])
		printf("export %s\n", data->exp[i]);
}

char	**new_env(t_data *data, char **tab, char **newenv)
{
	int	i;
	int	j;

	i = 0;
	while (data->env[i])
	{
		newenv[i] = ft_strdup(data->env[i]);
		if (!newenv[i])
			return (NULL);
		i++;
	}
	j = 1;
	while (tab[j])
	{
		newenv[i] = ft_strdup(tab[j]);
		if (!newenv[i])
			return (NULL);
		i++;
		j++;
	}
	newenv[i] = NULL;
	return (newenv);
}

void	add_export(t_data *data, char **tab)
{
	char	**newenv;
	int		newsize;

	newsize = ft_tablen(data->env) + ft_tablen(tab);
	newenv = (char **)malloc(sizeof(char *) * (newsize));
	if (!newenv)
		return ;
	newenv = new_env(data, tab, newenv);
	malloc_free(data->env);
	data->env = ft_tabdup(newenv);
	if (!data->env)
		return ;
	malloc_free(newenv);
}

// void	replace_var(t_data *data)
// {
// 	char	*newvar;
// }

int	check_export(t_data *data, char **tab)
{
	int	i;
	int	j;

	i = 0;
	while (data->env[i])
	{
		j = 1;
		while (tab[j])
		{
			// if (ft_strncmp(var, tab[j]), ft_strlen(var) == 0)
			// 	unset;
			if (ft_strcmp(data->env[i], tab[j]) == 0
				|| ft_strchr(tab[1], '=') == 0)
				return (1);
			j++;
		}
		i++;
	}
	return (0);
}

void	build_export(t_data *data, char **tab)
{
	if (ft_tablen(tab) > 1)
	{
		if (check_export(data, tab) == 1)
			return ;
		add_export(data, tab);
	}
	if (ft_tablen(tab) == 1)
	{
		data->exp = ft_tabdup(data->env);
		if (!data->exp)
			return ;
		print_export(data);
		malloc_free(data->exp);
	}
}
