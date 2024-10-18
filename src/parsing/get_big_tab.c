/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_big_tab.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afrikach <afrikach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/31 16:13:38 by idakhlao          #+#    #+#             */
/*   Updated: 2024/10/18 17:48:28 by afrikach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

// char	*s1;
//ft_strjoin chaque caractere au fur et a mesure qu'on parcours tab[i]
//ex char*s1 = tab[i++]. et des Que je tombe sur un '$' je strjoin s1 avec
//ce que me return look_for_expand->s2; et c'est ca qu'on va mettre 
//dans input[i].input;
// Appeler add_to_input(tab[i]) et le stocker dans input[i].input
// input[i] = malloc(sizeof(t_input));

void	fill_input(t_input *input, char *line)
{
	char	**tab;
	int		i;
	int		j;
	int		nb_blocks;

	i = 0;
	nb_blocks = count_blocks(line);
	tab = split_pipes(line);
	j = 0;
	while (i < nb_blocks)
	{
		input[i].redir_infile = NULL;
		input[i].in_file = NULL;
		input[i].redir_outfile = NULL;
		input[i].out_file = NULL;
		input[i].tab = NULL;
		input[i].cmd = NULL;
		input[i].input = malloc(sizeof(char) * ft_strlen(tab[j]) + 1);
		if (input[i].input == NULL)
			perror("fill input = Failed to allocate memory for input[i]");
		ft_strcpy(input[i].input, tab[i]);
		i++;
	}
	input[nb_blocks].input = NULL;
	malloc_free(tab);
}

void	allocate_new_struct(t_input **input, char *line)
{
	int		nb_blocks;

	nb_blocks = count_blocks(line);
	*input = malloc(sizeof(t_input) * (nb_blocks + 1));
	if (input == NULL)
	{
		perror("Failed to allocate memory for t_input");
		return ;
	}
}

int	skip_quotes(char *s, int i)
{
	char	quote;

	while (s[i] && s[i] != '"' && s[i] != '\'')
		i++;
	if (s[i] == '"' || s[i] == '\'')
	{
		quote = s[i];
		i++;
		while (s[i] && ft_isspace(s[i + 1]) == 0)
		{
			if (s[i] == quote && s[i + 1] != ft_isspace(s[i]) == 1)
				i++;
			else
			{
				i++;
			}
		}
	}
	return (i);
}

int	skip_redir(char *s, int i)
{
	while (s[i])
	{
		if ((!find_quotes(s, i)) && (s[i] == '<' || s[i] == '>'))
		{
			while (s[i] == '<' || s[i] == '>')
				i++;
			while (s[i] && (ft_isspace(s[i]) == 1))
				i++;
			while (s[i] && (ft_isspace(s[i]) == 0))
			{
				if (s[i] == '"' || s[i] == '\'')
					i = skip_quotes(s, i);
				else
					i++;
			}
		}
		else
			break ;
	}
	return (i);
}

int	count_cmd(char *s)
{
	int	i;
	int	cmd;

	i = 0;
	cmd = 0;
	while (s[i])
	{
		while (s[i] && ft_isspace(s[i]) == 1)
			i++;
		if (s[i] && find_quotes(s, i) == 1)
		{
			cmd++;
			i = skip_quotes(s, i);
		}
		if (s[i] && (s[i] == '<' || s[i] == '>'))
			i = skip_redir(s, i);
		else if (s[i] && ft_isspace(s[i]) == 0)
		{
			cmd++;
			while (s[i] && ft_isspace(s[i]) == 0 && s[i] != '<' && s[i] != '>')
				i++;
		}
	}
	return (cmd);
}
