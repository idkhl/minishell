/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_expand.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afrikach <afrikach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 13:27:28 by afrikach          #+#    #+#             */
/*   Updated: 2024/10/22 16:42:39 by afrikach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

// on parcours et on ajoute au fur et a mesure si ce n'est pas un guillemet
// si c'est un guillemets on appel la fonction
////FONCTION QUI VA REMPLACER LE NOM DE LA VARIABLE PAR SA VALEUR////

char	*look_for_expand(char *line, t_data *data)
{
	int		i;
	int		j;
	char	*env_var;
	char	*var_value;

	i = 0;
	while (line[i])
	{
		j = 0;
		while (data->env[j])
		{
			env_var = find_variable_in_env(&line[i], data);
			if (env_var != NULL)
			{
				var_value = ft_strchr(env_var, '=');
				if (var_value)
					return (var_value + 1);
			}
			j++;
		}
		i++;
	}
	return (NULL);
}

// elle est appelee dans add_to_input
//des que str[i] == $ et que la fonction pour interpreter
//l'expand me renvoie true
//elle doit me return ce par quoi je dois remplacer la variable $USER (afrikach)
void	find_var_position(char *line, int *start, int *len)
{
	int	i;

	i = 0;
	*start = -1;
	*len = 0;
	while (line[i])
	{
		if (line[i] == '$')
		{
			i++;
			*start = i;
			while (line[i] && (ft_isalnum(line[i]) || line[i] == '_'))
			{
				(*len)++;
				i++;
			}
			break ;
		}
		i++;
	}
}

char	*return_var_name(char *line)
{
	int		start;
	int		len;
	char	*variable;

	variable = NULL;
	find_var_position(line, &start, &len);
	if (start != -1 && len > 0)
		variable = ft_substr(line, start, len);
	else
		return (NULL);
	return (variable);
}

char	*find_variable_in_env(char *line, t_data *data)
{
	int		j;
	char	*var_name;

	j = 0;
	var_name = return_var_name(line);
	if (!var_name)
		return (NULL);
	while (data->env[j])
	{
		if (ft_strncmp(data->env[j], var_name, ft_strlen(var_name)) == 0 &&
			data->env[j][ft_strlen(var_name)] == '=')
		{
			free(var_name);
			return (data->env[j]);
		}
		j++;
	}
	free(var_name);
	return (NULL);
}
