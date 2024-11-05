/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_struct.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afrikach <afrikach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/13 15:19:09 by afrikach          #+#    #+#             */
/*   Updated: 2024/11/05 17:32:40 by afrikach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	find_quotes(char *s, int index)
{
	int	simple_quote;
	int	double_quote;
	int	i;

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

int	get_index_redir(t_input *input, int j, int i)
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
	return (-1);
}

void	fill_struct(t_input *input, char *line, t_data *data)
{
	t_quote	quote;

	fill_input(input, line);
	fill_tab(input);
	fill_cmd(input, data, &quote);
	store_redir_symbols(input);
	store_redirection(input, data, &quote);
}
