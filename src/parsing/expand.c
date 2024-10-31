/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afrikach <afrikach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 16:41:55 by afrikach          #+#    #+#             */
/*   Updated: 2024/10/31 12:50:18 by afrikach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

// si guillemets simple ouvert on n'interprete pas
// (on return direct le nom de la variable)
// else on interprete et on appelle look_for_expand.

void	next_add_to_input(char *line, t_quote *quote, t_data *data)
{
	char	*var_name;
	char	*sig;

	var_name = NULL;
	sig = NULL;
	if (quote->open_quote == 1 && quote->quote_type == '\'')
		quote->str = join_char(quote->str, line[quote->i]);
	else
	{
		sig = ft_itoa(g_signal);
		if (line[quote->i] && line[quote->i] == '$'
			&& line[quote->i + 1] == '?')
		{
			quote->str = join_str(quote->str, sig);
			quote->i += 2;
		}
		if (line[quote->i] == '$' && !ft_isalpha(line[quote->i + 1]))
			quote->str = join_char(quote->str, line[quote->i]);
		else if (line[quote->i] == '$')
		{
			quote->str = (join_str(quote->str,
						look_for_expand(&line[quote->i], data)));
			var_name = return_var_name(&line[quote->i]);
			quote->i += ft_strlen(var_name);
		}
		else
			quote->str = join_char(quote->str, line[quote->i]);
	}
	free(sig);
	free(var_name);
}

char	*add_to_input(char *line, t_data *data, t_quote	*quote)
{
	ft_bzero(quote, sizeof(t_quote));
	while ((size_t)quote->i < ft_strlen(line) && line[quote->i])
	{
		if ((line[quote->i] == '\'' || line[quote->i] == '"')
			&& quote->open_quote == 0)
		{
			quote->quote_type = line[quote->i];
			quote->open_quote = !quote->open_quote;
		}
		else if (line[quote->i] == quote->quote_type && quote->open_quote == 1)
		{
			quote->quote_type = 0;
			quote->open_quote = !quote->open_quote;
		}
		else
			next_add_to_input(line, quote, data);
		quote->i++;
	}
	if (quote->str == NULL && (line[0] == '"' || line[0] == '\''))
	{
		quote->str = malloc(sizeof(char) * 1);
		quote->str[0] = '\0';
	}
	return (quote->str);
}
