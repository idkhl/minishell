/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_enum.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afrikach <afrikach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/03 15:59:18 by afrikach          #+#    #+#             */
/*   Updated: 2024/09/09 15:59:33 by afrikach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

enum e_token identify_tokens(char *line, int i)
{
	if (((line[i] > 8 && line[i] < 14) || line[i] == ' '))
		return (SPACES);
	else if (line[i] == '<' && line[i + 1] == '<')
		return (HEREDOC);
	else if (line[i] == '>' && line[i + 1] == '>')
		return (APPEND);
	else if (line[i] == '|')
		return (PIPE);
	else if (line[i] == '<' && line[i + 1] != '<')
		return (INPUT);
	else if (line[i] == '>' && line[i + 1] != '>')
		return (TRUNC);
	else if (line[i] == '\0')
		return (END);
	else if (line[i] == '-')
		return(OPT);
	else
		return (0);
}
void	get_index(char *line, int i)
{
	i = 0;
	enum e_token token_type = identify_tokens(line, i);
	while (line[i])
	{
		if (token_type == SPACES)
			SPACES == i;
		else if (token_type == HEREDOC)
			HEREDOC == i;
	}
}
