/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   divide_input.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afrikach <afrikach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 12:35:06 by afrikach          #+#    #+#             */
/*   Updated: 2024/10/31 17:09:31 by afrikach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

// Fct pour compter la len a partir d'une quote
// jusqu'a rencontrer un espace ou une redir apres la quote fermante

int	handle_normal_string(t_input *input, int i, int *j, int k)
{
	int	len;

	len = get_len2(input[i].input + *j);
	input[i].tab[k] = malloc(sizeof(char) * (len + 1));
	if (!input[i].tab[k])
	{
		free(input[i].tab[k]);
		return (k);
	}
	ft_strlcpy(input[i].tab[k], input[i].input + *j, len + 1);
	*j += len;
	return (k + 1);
}

int	handle_quoted_string(t_input *input, int i, int *j, int k)
{
	int	len;

	len = len_with_quote(input[i].input + *j);
	input[i].tab[k] = malloc(sizeof(char) * (len + 1));
	if (!input[i].tab[k])
		return (k);
	ft_strlcpy(input[i].tab[k], input[i].input + *j, len + 1);
	*j += len;
	return (k + 1);
}

int	handle_redirection(t_input *input, int i, int *j, int k)
{
	input[i].tab[k] = get_redir_type(input[i].input, *j);
	if (input[i].input[*j + 1] == '<' || input[i].input[*j + 1] == '>')
		*j += 2;
	else
		(*j)++;
	return (k + 1);
}

void	fill_tab_entries(t_input *input, int i)
{
	int	j;
	int	k;

	j = 0;
	k = 0;
	while (input[i].input[j])
	{
		while (input[i].input[j] && ft_isspace(input[i].input[j]))
			j++;
		if (input[i].input[j] == '<' || input[i].input[j] == '>')
			k = handle_redirection(input, i, &j, k);
		else if (input[i].input[j] == '\'' || input[i].input[j] == '"')
			k = handle_quoted_string(input, i, &j, k);
		else if (input[i].input[j] && !ft_isspace(input[i].input[j]))
			k = handle_normal_string(input, i, &j, k);
	}
	input[i].tab[k] = NULL;
}

void	fill_tab(t_input *input)
{
	int	i;
	int	tab_len;

	i = 0;
	while (input[i].input)
	{
		tab_len = get_tab_len(input[i].input);
		input[i].tab = malloc(sizeof(char *) * (tab_len + 1));
		if (!input[i].tab)
			return ;
		fill_tab_entries(input, i);
		i++;
	}
	input[i].tab = NULL;
}
