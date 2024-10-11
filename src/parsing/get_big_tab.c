/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_big_tab.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afrikach <afrikach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/31 16:13:38 by idakhlao          #+#    #+#             */
/*   Updated: 2024/10/11 17:29:52 by afrikach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	free_tab(char ***big_tab, int size)
{
	int	i;

	i = 0;
	if (big_tab)
	{
		while (i < size)
		{
			malloc_free(big_tab[i]);
			i++;
		}
		free(big_tab);
	}
}

void	fill_input(t_input *input, char *line)
{
	char	**tab;
	int		i;
	int		j;
	int		nb_blocks;
	// char	*s1;

	i = 0;
	nb_blocks = count_blocks(line);
	tab = split_pipes(line);
	j = 0;
	//ft_strjoin chaque caractere au fur et a mesure qu'on parcours tab[i]
	//ex char*s1 = tab[i++]. et des Que je tombe sur un '$' je strjoin s1 avec
	//ce que me return look_for_expand->s2; et c'est ca qu'on va mettre dans input[i].input;
	
	while (i < nb_blocks)
	{
		// Appeler add_to_input(tab[i]) et le stocker dans input[i].input
		// input[i] = malloc(sizeof(t_input));
		input[i].input = malloc(sizeof(char) * ft_strlen(tab[j]) + 1);
		if (input[i].input == NULL)
			perror("fill input = Failed to allocate memory for input[i]");
		// while (tab[i])
		// {
		// 	if (tab[j] != '$')
		// 		s1[j] = 
		// }
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

int	get_len_in_quotes(char *s)
{
	int		i;
	int		len;
	char	quote;

	i = 0;
	len = 0;
	while (s[i] && s[i] != '"' && s[i] != '\'')
		i++;
	if (s[i] == '"' || s[i] == '\'')
	{
		quote = s[i];
		i++;
		while (s[i] && s[i] != quote)
		{
			len++;
			i++;
		}
	}
	return (len);
}

int	get_len(char *s)
{
	int	i;
	int	len;

	i = 0;
	len = 0;
	while (s[i])
	{
		while (s[i] && ft_isspace(s[i]) == 1)
			i++;
		while (s[i] && ft_isspace(s[i]) == 0)
		{
			len++;
			i++;
		}
		if (s[i] && ft_isspace(s[i]) == 1)
			break ;
	}
	return (len);
}
