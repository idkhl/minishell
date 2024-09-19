/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_close_redir.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afrikach <afrikach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/29 15:03:21 by afrikach          #+#    #+#             */
/*   Updated: 2024/09/09 15:59:37 by afrikach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void ignore_spaces(char *line, int *i)
{
    while (line[*i] == ' ' || line[*i] == '\t')
        (*i)++;
}
static int end_of_close_operators(char *line, int *i, int *word)
{
    if (*word == 0)
    {
        printf("CLOSE operator non precede par un mot\n");
        return (1);
    }
    if (line[*i + 1] == '>')
        (*i)++;
    (*i)++;
    ignore_spaces(line, i);
    if (line[*i] == '\0' || line[*i] == '>')
    {
        printf("CLOSE bash: syntax error near unexpected token 'newline'\n");
        return (1);
    }
    *word = 0;
    return (0);
}

int check_close_operators(char *line)
{
    int i;
    int word;

	i = 0;
	word = 0;
    while (line[i])
    {
        ignore_spaces(line, &i);
        if (line[i] == '>')
        {
            if (end_of_close_operators(line, &i, &word))
                return (1);
        }
        else if (line[i] != ' ' && line[i] != '\t' && line[i] != '>')
            word = 1;
        i++;
    }
    return (0);
}
