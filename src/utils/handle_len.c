/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_len.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afrikach <afrikach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 09:47:39 by afrikach          #+#    #+#             */
/*   Updated: 2024/11/07 15:49:35 by afrikach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	len_with_quote(char *str)
{
	t_vars	vars;

	ft_bzero(&vars, sizeof(t_vars));
	while (str[vars.i] != '\0')
	{
		if (vars.in_quote == 0 && (str[vars.i] == '\'' || str[vars.i] == '"'))
		{
			vars.in_quote = 1;
			vars.quote_char = str[vars.i++];
			vars.len++;
		}
		if (vars.in_quote == 1)
		{
			vars.len++;
			if (str[vars.i] == vars.quote_char)
				vars.in_quote = 0;
		}
		else if ((vars.in_quote == 0)
			&& (str[vars.i] == ' ' || str[vars.i] == '<' || str[vars.i] == '>'))
			break ;
		else if (vars.in_quote == 0)
			vars.len++;
		vars.i++;
	}
	return (vars.len);
}

int	get_len2(char *s)
{
	int	i;

	i = 0;
	while (s[i] && ft_isspace(s[i]) == 0 && (s[i] != '<' && s[i] != '>'))
	{
		if (s[i] && (s[i] == '\'' || s[i] == '"'))
			i += len_with_quote(s + i);
		else
			i++;
	}
	return (i);
}

int	handle_redirections(char *s, int *i)
{
	(*i)++;
	if (s[*i] == '<' || s[*i] == '>')
		(*i)++;
	return (1);
}

int	get_tab_len(char *s)
{
	int	i;
	int	len;

	i = 0;
	len = 0;
	while (s[i])
	{
		while (s[i] && ft_isspace(s[i]) == 1)
			i++;
		while (s[i] && ft_isspace(s[i]) == 0 && (s[i] != '<' && s[i] != '>'))
		{
			if (s[i] && (s[i] == '\'' || s[i] == '"'))
				i += len_with_quote(s + i);
			else
				i++;
		}
		if (s[i] && (s[i] == '<' || s[i] == '>'))
		{
			i++;
			len++;
		}
		len++;
	}
	return (len);
}

//return 3 //echo "hello yy"gg
//return 2 //echo hh"hello yy"gg
//return 4 //echo ff<"infile"
//

// int	get_tab_len(char *s)
// {
// 	int	i;
// 	int	len;

// 	i = 0;
// 	len = 0;
// 	while (s[i])
// 	{
// 		while (s[i] && ft_isspace(s[i]) == 1)
// 			i++;
// 		if (s[i] && (s[i] == '\'' || s[i] == '"'))
// 		{
// 			len++;
// 			i += len_with_quote(s + i);
// 		}
// 		else if (s[i] && (s[i] == '<' || s[i] == '>'))
// 			len += handle_redirections(s, &i);
// 		else if (s[i] && ft_isspace(s[i]) == 0)
// 		{
// 			len++;
// 			while (s[i] && ft_isspace(s[i]) == 0 && s[i] != '<' && s[i] != '>')
// 				i++;
// 		}
// 	}
// 	return (len);
// }

// int	get_len2(char *s)
// {
// 	int	len;

// 	len = 0;
// 	while (s[len] && !ft_isspace(s[len]) && s[len] != '<' && s[len] != '>')
// 		len++;
// 	return (len);
// }
