/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_expand.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afrikach <afrikach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 13:27:28 by afrikach          #+#    #+#             */
/*   Updated: 2024/10/08 10:43:02 by afrikach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

// $USER"frwwr" -> USER;
// f(USER) -> afrikach;
// f(USER) -> "";


// si guillemets simple ouvert on n'interprete pas (on return direct le nom de la variable)
// else on interprete et on appelle look_for_expand.

void add_to_input(char *line, t_data *data)
{
	int		i;
	int		open_quote;
	char	quote_type;

	i = 0;
	open_quote = 0;
	quote_type = 0;
	while (line[i])
	{
		if ((line[i] == '\'' || line[i] == '"') && open_quote == 0)
		{
			quote_type = line[i];
			open_quote = !open_quote;
			printf("VAR NAME = %s\n", return_var_name(line));
		}
		else if (line[i] == quote_type && open_quote == 1)
		{
			quote_type = 0;
			open_quote = !open_quote;
		}
		else
		{
			// (void)data;
			// printf("%c", line[i]);
			printf("INDEX = %d\n", i);
			if (quote_type == '\'' && open_quote == 1)
				printf("%s\n", return_var_name(line));
			else
				printf("%s\n", look_for_expand(line, data));
		}
		i++;
	}
}

//on parcours et on ajoute au fur et a mesure si ce n'est pas un guillemet
// si c'est un guillemets on appel la fonction
/////////FONCTION QUI VA REMPLACER LE NOM DE LA VARIABLE PAR SA VALEUR////////////
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
//des que str[i] == $ et que la fonction pour interpreter l'expand me renvoie true
//elle doit me return ce par quoi je dois remplacer la variable $USER (afrikach)

char	*return_var_name(char *line)
{
	int		i;
	char	*variable;
	int		len;
	int		start;

	i = 0;
	len = 0;
	start = -1;
	variable = NULL;
	while (line[i])
	{
		if (line[i] == '$' && line [i + 1] != ' ')
		{
			i++;
			start = i;
			while (line[i] && line[i] != ' ')
			{
				len++;
				i++;
			}
		}
		i++;
	}
	if (start != -1)
		variable = ft_substr(line, start, len);
	if (!variable)
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
// faire une fonction qui parcours l'env et cherche une variable pour savoir si elle existe
// si elle existe elle return le nom de la variable sans le $ sinon elle return NULL.

//input[i].input : [< in"$USER" cat]

