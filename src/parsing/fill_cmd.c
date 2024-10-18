/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afrikach <afrikach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 10:22:39 by afrikach          #+#    #+#             */
/*   Updated: 2024/10/18 17:36:30 by afrikach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

// fonction qui parcourt le tableau et return l'index des redirections

int	get_index_redir(t_input *input, int j)
{
	int	i;

	i = 0;
	while (input[i].tab)
	{
		while (j < get_tab_len(input[i].input) && input[i].tab[j])
		{
			if (ft_strcmp(input[i].tab[j], "<") == 0
				|| ft_strcmp(input[i].tab[j], ">") == 0
				|| ft_strcmp(input[i].tab[j], "<<") == 0
				|| ft_strcmp(input[i].tab[j], ">>") == 0)
				return (j);
			j++;
		}
		i++;
	}
	return (-1);
}

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
			index_redir = get_index_redir(input, j);
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

void	fill_cmd(t_input *input, t_data *data)
{
	int	i;
	int	j;
	int	index_redir;
	int	k;

	i = 0;
	while (input[i].tab)
	{
		input[i].cmd = malloc(sizeof(char *) * (get_nb_cmd(input) + 1));
		printf("NB CMD = %d\n", get_nb_cmd(input));
		j = 0;
		k = 0;
		while (input[i].tab[j])
		{
			index_redir = get_index_redir(input, j);
			if (index_redir == j)
				j += 2;
			else 
			{
				if (add_to_input(input[i].tab[j], data) == NULL)
				{
					j++;
					continue ;
				}
				else
				{
					input[i].cmd[k] = add_to_input(input[i].tab[j], data);
					printf("**CMD LEN = %zu\n", ft_strlen(input[i].cmd[k]));
					j++;
					k++;
				}
			}
		}
		input[i].cmd[k] = NULL;
		printf("TAB SIZE = %d\n", get_tab_size(input[i].cmd));
		i++;
	}
}

int get_tab_size(char **tab)
{
    int size;
	
	size = 0;
    while (tab[size] != NULL)
        size++;

    return (size);
}
