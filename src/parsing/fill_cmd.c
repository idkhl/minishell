/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: idakhlao <idakhlao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 10:22:39 by afrikach          #+#    #+#             */
/*   Updated: 2024/11/06 14:32:44 by idakhlao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"


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
	char	*str;

	j = 0;
	k = 0;
	while (input[i].tab[j])
	{
		if (get_index_redir(input, j, i) == j)
			j += 2;
		else
		{
			str = add_to_input(input[i].tab[j], data, quote);
			if (str == NULL)
				free(str);
			else
				input[i].cmd[k++] = str;
			j++;
		}
	}
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
// 					input[i].cmd[k] 
// 						= add_to_input(input[i].tab[j], data, quote);
// 					j++;
// 					k++;
// 				}
// 			}
// 		}
// 		input[i].cmd[k] = NULL;
// 		i++;
// 	}
// }
