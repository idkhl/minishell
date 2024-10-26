/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: idakhlao <idakhlao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/20 17:34:28 by idakhlao          #+#    #+#             */
/*   Updated: 2024/10/26 17:29:49 by idakhlao         ###   ########.fr       */
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

char	**new_env(t_data *data, char *var, char **newenv)
{
	int	i;

	i = 0;
	while (data->env[i])
	{
		newenv[i] = ft_strdup(data->env[i]);
		if (!newenv[i])
			return (NULL);
		i++;
	}
	newenv[i] = ft_strdup(var);
	if (!newenv[i])
		return (NULL);
	i++;
	newenv[i] = NULL;
	return (newenv);
}

void	add_export(t_data *data, char *var)
{
	char	**newenv;
	int		newsize;

	newsize = ft_tablen(data->env) + 1;
	newenv = (char **)malloc(sizeof(char *) * (newsize + 1));
	if (!newenv)
		return ;
	newenv = new_env(data, var, newenv);
	if (!newenv)
		return ;
	malloc_free(data->env);
	data->env = ft_tabdup(newenv);
	if (!data->env)
		return ;
	malloc_free(newenv);
}

void	check_existing_variable(t_data *data, char *var)
{
	int		j;
	char	*var_to_add;
	char	*var_env;

	j = 0;
	var_to_add = var_name(var);
	if (!var_to_add)
		return ;
	while (data->env[j])
	{
		var_env = var_name(data->env[j]);
		if (var_env)
		{
			if (ft_strcmp(var_to_add, var_env) == 0)
			{
				unset_var(data, j);
				return (free(var_env), free(var_to_add));
			}
			free(var_env);
		}
		j++;
	}
	free(var_to_add);
}

void	build_export(t_data *data, char	**tab)
{
	int	i;

	i = 1;
	if (ft_tablen(tab) == 1)
	{
		data->exp = ft_tabdup(data->env);
		if (!data->exp)
			return ;
		print_export(data);
		malloc_free(data->exp);
	}
	else
	{
		while (tab[i])
		{
			if (check_var_is_valid(tab[i]) == 0)
			{
				check_existing_variable(data, tab[i]);
				add_export(data, tab[i]);
			}
			i++;
		}
	}
}
