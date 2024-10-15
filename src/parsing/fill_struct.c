/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_struct.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afrikach <afrikach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/13 15:19:09 by afrikach          #+#    #+#             */
/*   Updated: 2024/10/15 12:33:17 by afrikach         ###   ########.fr       */
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

void	fill_struct(t_input *input, char *line)
{
	fill_input(input, line);
	fill_tab(input);
	fill_cmd(input);
	store_redir_symbols(input);
	store_redirection(input);
}

// int	get_redirection_length(char *s)
// {
// 	int	i;
// 	int	length;

// 	i = 0;
// 	length = 0;
// 	while (s[i])
// 	{
// 		if (!find_quotes(s, i) && (s[i] == '<' || s[i] == '>'))
// 		{
// 			if ((s[i + 1] == '<' && s[i] == '<')
// 				|| (s[i + 1] == '>' && s[i] == '>'))
// 				i += 2;
// 			else
// 				i++;
// 			while (s[i] && ft_isspace(s[i]))
// 				i++;
// 			while (s[i] && !ft_isspace(s[i]) && s[i] != '<' && s[i] != '>')
// 			{
// 				if (s[i] && s[i] == '\"')
// 					i++;
// 				else
// 				{
// 					length++;
// 					i++;
// 				}
// 			}
// 			return (length);
// 		}
// 		i++;
// 	}
// 	return (0);
// }


