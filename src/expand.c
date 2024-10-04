/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afrikach <afrikach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/22 22:09:40 by idakhlao          #+#    #+#             */
/*   Updated: 2024/10/03 11:07:48 by afrikach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	expand_variable(t_data *data, char *var_env, char *word, int i)
{
	char	*new;
	int		size;

	size = ft_strlen(var_env) - ft_strlen(word);
	new = ft_substr(var_env, ft_strlen(word), size);
	if (!new)
		return ;
	free(data->input[i]);
	data->input[i] = ft_strdup(new);
	free(new);
}

void	check_expand(t_data *data, char **tab, int i, int j)
{
	char	*var;

	var = ft_substr(tab[i], 1, (ft_strlen(tab[i]) - 1));
	if (!var)
		return ;
	if (ft_strncmp(var, data->env[j], ft_strlen(tab[i]) - 1) == 0)
		expand_variable(data, data->env[j], tab[i], i);
	free(var);
}

void	expand(t_data *data, char **tab)
{
	int		i;
	int		j;

	i = 0;
	while (tab[i])
	{
		j = 0;
		while (data->env[j])
		{
			if (*tab[i] == '$')
				check_expand(data, tab, i, j);
			j++;
		}
		i++;
	}
}

//expand var qui n'existe pas -> = null
