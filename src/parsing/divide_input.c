/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   divide_input.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afrikach <afrikach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 12:35:06 by afrikach          #+#    #+#             */
/*   Updated: 2024/10/11 19:13:58 by afrikach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

// Fct pour compter la len a partir d'une quote
// jusqu'a rencontrer un espace ou une redir apres la quote fermante

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
int	get_tab_len(char *s)
{
	int	i;
	int	len;
	int	k;

	i = 0;
	len = 0;
	while (s[i])
	{
		while (s[i] && ft_isspace(s[i]) == 1)
			i++;
		if (s[i] && (s[i] == '\'' || s[i] == '"'))
		{
			k = len_with_quote(s + i);
			len++;
			i += k;
		}
		else if (s[i] && (s[i] == '<' || s[i] == '>'))
		{
			len++;
			if (s[i + 1] == '<' || s[i + 1] == '>')
				i += 2;
			else
				i++;
		}
		else if (s[i] && ft_isspace(s[i]) == 0)
		{
			len++;
			while (s[i] && ft_isspace(s[i]) == 0 && s[i] != '<' && s[i] != '>')
				i++;
		}
	}
	return (len);
}

int	get_len2(char *s)
{
	int	len;

	len = 0;
	while (s[len] && !ft_isspace(s[len]) && s[len] != '<' && s[len] != '>')
		len++;
	return (len);
}
int handle_normal_string(t_input *input, int i, int *j, int k)
{
	int len = get_len2(input[i].input + *j);
	input[i].tab[k] = malloc(sizeof(char) * (len + 1));
	if (!input[i].tab[k])
		return k;
	ft_strlcpy(input[i].tab[k], input[i].input + *j, len + 1);
	*j += len;
	return (k + 1);
}

int handle_quoted_string(t_input *input, int i, int *j, int k)
{
	int len = len_with_quote(input[i].input + *j);
	input[i].tab[k] = malloc(sizeof(char) * (len + 1));
	if (!input[i].tab[k])
		return k;
	ft_strlcpy(input[i].tab[k], input[i].input + *j, len + 1);
	*j += len;
	return (k + 1);
}

int handle_redirection(t_input *input, int i, int *j, int k)
{
	input[i].tab[k] = get_redir_type(input[i].input, *j);
	if (input[i].input[*j + 1] == '<' || input[i].input[*j + 1] == '>')
		*j += 2;
	else
		(*j)++;
	return (k + 1);
}

void fill_tab_entries(t_input *input, int i)
{
	int j;
	int k;
	
	j = 0;
	k = 0;
	while (input[i].input[j])
	{
		while (input[i].input[j] && ft_isspace(input[i].input[j]))
			j++;
		if (input[i].input[j] == '<' || input[i].input[j] == '>')
			k = handle_redirection(input, i, &j, k);
		else if (input[i].input[j] == '\'' || input[i].input[j] == '"')
			k = handle_quoted_string(input, i, &j, k);
		else if (input[i].input[j] && !ft_isspace(input[i].input[j]))
			k = handle_normal_string(input, i, &j, k);
	}
	input[i].tab[k] = NULL;
}

void fill_tab(t_input *input)
{
	int i;

	i = 0;
	while (input[i].input)
	{
		input[i].tab = malloc(sizeof(char *)
			* (get_tab_len(input[i].input) + 1));
		if (!input[i].tab)
			return;

		fill_tab_entries(input, i);
		i++;
	}
}


// void	fill_tab(t_input *input)
// {
// 	int	i;
// 	int	j;
// 	int	k;
// 	int	len;

// 	i = 0;
// 	len = 0;
// 	while (input[i].input)
// 	{
// 		j = 0;
// 		k = 0;
// 		input[i].tab = malloc(sizeof(char *) * (get_tab_len(input[i].input) + 1));
// 		if (!input[i].tab)
// 			return ;
// 		printf("get_tab_len: %d\n", get_tab_len(input[i].input));
// 		while (input[i].input[j])
// 		{
// 			while (input[i].input[j] && ft_isspace(input[i].input[j]))
// 				j++;
// 			if (input[i].input[j] == '<' || input[i].input[j] == '>')
// 			{
// 				input[i].tab[k] = get_redir_type(input[i].input, j);
// 				if (input[i].input[j + 1] == '<'
// 					|| input[i].input[j + 1] == '>')
// 					j += 2;
// 				else
// 					j++;
// 				k++;
// 			}
// 			else if (input[i].input[j] == '\'' || input[i].input[j] == '"')
// 			{
// 				len = len_with_quote(input[i].input + j);
// 				input[i].tab[k] = malloc(sizeof(char) * (len + 1));
// 				if (!input[i].tab[k])
// 					return ;
// 				ft_strlcpy(input[i].tab[k], input[i].input + j, len + 1);
// 				k++;
// 				j += len;
// 			}
// 			else if (input[i].input[j] && ft_isspace(input[i].input[j]) == 0)
// 			{
// 				len = get_len2(input[i].input + j);
// 				input[i].tab[k] = malloc(sizeof(char) * (len + 1));
// 				if (!input[i].tab[k])
// 					return ;
// 				ft_strlcpy(input[i].tab[k], input[i].input + j, len + 1);
// 				k++;
// 				j += len;
// 			}
// 		}
// 		input[i].tab[k] = NULL;
// 		i++;
// 	}
// }
