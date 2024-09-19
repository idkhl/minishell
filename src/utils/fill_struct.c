/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_struct.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afrikach <afrikach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/13 15:19:09 by afrikach          #+#    #+#             */
/*   Updated: 2024/09/19 12:26:25 by afrikach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	find_quotes(char *s, int index)
{
	int simple_quote;
	int	double_quote;
	int i;
	
	i = 0;
	simple_quote = 0;
	double_quote = 0;
	while (i < index)
	{
		if (s[i] == '\'' && !double_quote)
			simple_quote = !simple_quote;
		else if (s[i] == '\"' && !simple_quote)
			double_quote = !double_quote;
		i++;
	}
	if (simple_quote || double_quote)
		return (1);
	return (0);
}
int get_redirection_length(char *s) 
{
    int i;
    int length;

	i = 0;
	length = 0;
    while (s[i])
	{
        if (!find_quotes(s, i) && (s[i] == '<' || s[i] == '>'))
		{
			i++;
			while (s[i] && ft_isspace(s[i]))
				i++;
			while (s[i] && !ft_isspace(s[i]) && s[i] != '<' && s[i] != '>') 
			{
				if (s[i] && s[i] == '\"')
					i++;
				else
				{
					length++;
					i++;
				}
			}
			return (length);
		}
		i++;
	}
	return 0;
}

// int		find_redirection(char *s)
// {
// 	int i;

// 	i = 0;
// 	while (s[i])
// 	{
		
// 	}
	
// }


// int allocate_and_copy_redir(char *s)
// {
//     int i;
// 	int	length;
	
// 	i = find_redirection(s);
// 	printf("I = %d\n", i);
// 	length = 0;
// 	while (s[i])
// 	{
// 		if (s[i] == '<' && s[i] == '>')
// 			i++;
// 		length = get_redirection_length(s);
// 		return (length);
// 		i++;
// 	}
// 	return (-1);
// }


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
	return (count);
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

