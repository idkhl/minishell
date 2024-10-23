/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afrikach <afrikach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 10:22:39 by afrikach          #+#    #+#             */
/*   Updated: 2024/10/23 15:38:06 by afrikach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

// fonction qui parcourt le tableau et return l'index des redirections

int	get_nb_cmd(t_input *input)
{
	int	i;
	int	j;
	int	index_redir;
	int	len;

	i = 0;
	len = 0;
	while (input[i].tab)
	{
		j = 0;
		while (input[i].tab[j])
		{
			index_redir = get_index_redir(input, j, i);
			if (index_redir == j)
				j += 2;
			else
			{
				len++;
				j++;
			}
		}
		i++;
	}
	return (len);
}

void	fill_cmd_next(t_input *input, t_data *data, t_quote *quote, int i)
{
	int		j;
	int		k;
	char	*input_add;

	j = 0;
	k = 0;
	while (input[i].tab[j])
	{
		input_add = add_to_input(input[i].tab[j], data, quote);
		if (get_index_redir(input, j, i) == j)
			j += 2;
		else
		{
			if (input_add == NULL)
			{
				j++;
				continue ;
			}
			else
			{
				input[i].cmd[k] = input_add;
				j++;
				k++;
			}
		}
	}
	free(input_add);
	input[i].cmd[k] = NULL;
}

void	fill_cmd(t_input *input, t_data *data, t_quote *quote)
{
	int	i;

	i = 0;
	while (input[i].tab)
	{
		input[i].cmd = malloc(sizeof(char *) * (get_nb_cmd(input) + 1));
		fill_cmd_next(input, data, quote, i);
		i++;
	}
}

int	get_tab_size(char **tab)
{
	int	size;

	size = 0;
	while (tab[size] != NULL)
		size++;
	return (size);
}


// void	fill_cmd(t_input *input, t_data *data, t_quote *quote)
// {
// 	int	i;
// 	int	j;
// 	int	index_redir;
// 	int	k;

// 	i = 0;
// 	while (input[i].tab)
// 	{
// 		input[i].cmd = malloc(sizeof(char *) * (get_nb_cmd(input) + 1));
// 		j = 0;
// 		k = 0;
// 		while (input[i].tab[j])
// 		{
// 			index_redir = get_index_redir(input, j);
// 			if (index_redir == j)
// 				j += 2;
// 			else 
// 			{
// 				if (add_to_input(input[i].tab[j], data, quote) == NULL)
// 				{
// 					j++;
// 					continue ;
// 				}
// 				else
// 				{
// 					input[i].cmd[k] = add_to_input(input[i].tab[j], data, quote);
// 					j++;
// 					k++;
// 				}
// 			}
// 		}
// 		input[i].cmd[k] = NULL;
// 		i++;
// 	}
// }

