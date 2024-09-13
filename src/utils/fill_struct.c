/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_struct.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afrikach <afrikach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/13 15:19:09 by afrikach          #+#    #+#             */
/*   Updated: 2024/09/13 20:02:54 by afrikach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	allocate_and_copy_redir(t_input *input, char *line)
{
	int		i;
	int		j;
	int		nb_blocks;
	
	i = 0;
	nb_blocks = count_blocks(line);
	while (i < nb_blocks)
	{
		j = 0;
		while (input[i].tab[j])
		{
			if (ft_strcmp(input[i].tab[j], "<") == 0)
				input[i].in_file = ft_strdup(input[i].tab[j + 1]);
			else if (ft_strcmp(input[i].tab[j], ">") == 0)
				input[i].out_file = ft_strdup(input[i].tab[j + 1]);
			j++;
		}
		i++;
	}
}
int count_cmds(char **tab)
{
	int i = 0;
	int count = 0;

	while (tab[i])
	{
		if (ft_strcmp(tab[i], "<") != 0 && ft_strcmp(tab[i], ">") != 0
			&& ft_strcmp(tab[i], ">>") != 0 && ft_strcmp(tab[i], "<<") != 0)
		{
			count++;
		}
		else
		{
			i++;
		}
		i++;
	}
	return count;
}

void	skip_redir(t_input *input, char *line)
{
	int		i;
	int		j;
	int		k;
	int		nb_blocks;
	
	i = 0;
	nb_blocks = count_blocks(line);
	while (i < nb_blocks)
	{
		j = 0;
		k = 0;
		input[i].cmd = malloc(sizeof(char *) * (count_cmds(input[i].tab) + 1));
		if (!input[i].cmd)
			return ;
		
		while (input[i].tab[j])
		{
			
			if (ft_strcmp(input[i].tab[j], "<") == 0 
				|| ft_strcmp(input[i].tab[j], ">") == 0 
				|| ft_strcmp(input[i].tab[j], ">>") == 0 
				|| ft_strcmp(input[i].tab[j], "<<") == 0)
			{
				j += 2;
				continue;
			}
			input[i].cmd[k] = ft_strdup(input[i].tab[j]);
			k++;
			j++;
		}
		input[i].cmd[k] = NULL;
		i++;
	}
}

