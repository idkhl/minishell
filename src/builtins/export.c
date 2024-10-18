/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: idakhlao <idakhlao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/20 17:34:28 by idakhlao          #+#    #+#             */
/*   Updated: 2024/10/18 15:56:13 by idakhlao         ###   ########.fr       */
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

int	check_var_is_valid(t_data *data, char **tab)
{
	int	i;
	int	j;

	i = 0;
	while (data->env[i])
	{
		j = 1;
		while (tab[j])
		{
			if (ft_strchr(tab[j], '=') == 0)
				return (-1);
			j++;
		}
		i++;
	}
	return (0);
}

char	*var_name(char	*var)
{
	char	*tmp;
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (var[i] && var[i] != '=')
		i++;
	tmp = (char *)malloc(sizeof(char) * (i - j + 2));
	if (!tmp)
		return (NULL);
	while (j < i)
	{
		tmp[j] = var[j];
		j++;
	}
	tmp[j] = '\0';
	return (tmp);
}

void	check_existing_variable(t_data *data, char **tab)
{
	int		i;
	int		j;
	char	*var_to_add;
	char	*var_env;

	i = 1;
	while (tab[i])
	{
		var_to_add = var_name(tab[i]);
		j = 0;
		while (data->env[j])
		{
			var_env = var_name(data->env[j]);
			if (ft_strcmp(var_to_add, var_env) == 0)
			{
				unset_var(data, j);
				break ;
			}
			free(var_env);
			j++;
		}
		free(var_to_add);
		// add_export(data, tab);
		i++;
	}
}

void	build_export(t_data *data, char	**tab)
{
	int	i;

	i = 1;
	if (ft_tablen(tab) == 1 || tab[1] == NULL)
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
			
		}
	}
}


// void	build_export(t_data *data, char **tab)
// {
// 	if (ft_tablen(tab) > 1)
// 	{
// 		if (check_var_is_valid(data, tab) == -1)
// 			return ;
// 		else
// 			check_existing_variable(data, tab);
// 		add_export(data, tab);
// 	}
// 	if (ft_tablen(tab) == 1)
// 	{
// 		data->exp = ft_tabdup(data->env);
// 		if (!data->exp)
// 			return ;
// 		print_export(data);
// 		malloc_free(data->exp);
// 	}
// }

// export -> mettre ntre guillemets le contenu de la var
