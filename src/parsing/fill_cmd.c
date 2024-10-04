/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afrikach <afrikach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 10:22:39 by afrikach          #+#    #+#             */
/*   Updated: 2024/10/04 17:44:43 by afrikach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

//fonction principale a appeler
void	fill_cmd(t_input *input)
{
	int	i;

	i = 0;
	while (input[i].input)
	{
		allocate_cmds(input, i);
		if (!input[i].cmd)
			return ;
		process_input(input, i);
		i++;
	}
}

// Fonction pour allouer la memoire pour les cmd
void	allocate_cmds(t_input *input, int i)
{
	input[i].cmd = malloc(sizeof(char *) * (count_cmd(input[i].input) + 1));
}

// Fonction pour traiter chaque input et remplir cmd
void	process_input(t_input *input, int i)
{
	int	j;
	int	k;

	j = 0;
	k = 0;
	while (input[i].input[j])
	{
		if (input[i].input[j] == '<' || input[i].input[j] == '>')
			j = skip_redir(input[i].input, j);
		else if (input[i].input[j] == '"' || input[i].input[j] == '\'')
			j = handle_quotes_in_cmd(input, i, &k, j);
		else if (!ft_isspace(input[i].input[j]))
			j = handle_word(input, i, &k, j);
		j++;
	}
	input[i].cmd[k] = NULL;
}

// Fonction pour traiter les guillemets et copier les str entre guillemets
int	handle_quotes_in_cmd(t_input *input, int i, int *k, int j)
{
	char	quote;
	int		len;

	quote = input[i].input[j];
	len = get_len_in_quotes(&input[i].input[j]);
	j++;
	input[i].cmd[*k] = malloc(sizeof(char) * (len + 1));
	if (!input[i].cmd[*k])
		return (j);
	quotecpy(input[i].cmd[*k], &input[i].input[j], len, quote);
	(*k)++;
	return (j + len);
}

// Fonction pour traiter les mots normaux (sans guillemets)
int	handle_word(t_input *input, int i, int *k, int j)
{
	int	len;

	len = get_len(&input[i].input[j]);
	input[i].cmd[*k] = malloc(sizeof(char) * (len + 1));
	if (!input[i].cmd[*k])
		return (j);
	ft_strncpy(input[i].cmd[*k], &input[i].input[j], len);
	input[i].cmd[*k][len] = '\0';
	(*k)++;
	return (j + len);
}