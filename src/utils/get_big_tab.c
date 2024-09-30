/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_big_tab.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afrikach <afrikach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/31 16:13:38 by idakhlao          #+#    #+#             */
/*   Updated: 2024/09/30 16:20:06 by afrikach         ###   ########.fr       */
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
	int		nb_blocks;
	
	i = 0;
	nb_blocks = count_blocks(line);
	tab = split_pipes(line);

	while(i < nb_blocks)
	{
		input[i].input = NULL;
		input[i].input= malloc(sizeof(char) * ft_strlen(tab[i]) + 1);
		if (input[i].input == NULL)
            perror("fill input = Failed to allocate memory for input[i]");
		ft_strcpy(input[i].input, tab[i]);
		// input[i].tab = split_quotes(tab[i], ' ');
		i++;
	}
	input[nb_blocks].input = NULL;
	malloc_free(tab);
}

void	allocate_new_struct(t_input **tab, char *line)
{
	int		nb_blocks;
	
	*tab = NULL;
	nb_blocks = count_blocks(line);
	*tab = malloc(sizeof(t_input) * (nb_blocks + 1));
	if (tab == NULL)
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
			break;
	}
	return (i);
}
int	count_cmd(char *s)
{
	int i;
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
	int i;
	int	len;
	char quote;

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
	int i;
	int len;

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
        	break;
	}
    return (len);
}

void	fill_cmd(t_input *input)
{
	int i;
	int j;
	int k;

	i = 0;
	k = 0;
	while(input[i].input)
	{
		j = 0;
		input[i].cmd = malloc(sizeof(char *) * (count_cmd(input[i].input) + 1));
		if (!input[i].cmd)
			return;
		while (input[i].input[j])
		{
			if (input[i].input[j] && (input[i].input[j] == '<' || input[i].input[j] == '>'))
				j = skip_redir(input[i].input, j);
			if (input[i].input[j] && (input[i].input[j] == '"' || input[i].input[j] == '\''))
			{
				char quote;
				quote = input[i].input[j];
				int len = get_len_in_quotes(&input[i].input[j]);
				printf("LEN IN QUOTE : %d\n", get_len_in_quotes(&input[i].input[j]));
				j++;
				input[i].cmd[k] = malloc(sizeof(char) * (len + 1));
				if (!input[i].cmd[k])
					return;
				quotecpy(input[i].cmd[k], &input[i].input[j], len, quote);
				k++;
				j += len;
				printf("J = %d\n", j);
			}
			else if (input[i].input[j] && ft_isspace(input[i].input[j]) == 0)
			{		
				int len = get_len(&input[i].input[j]);
				input[i].cmd[k] = malloc(sizeof(char) * (len + 1));
				if (!input[i].cmd[k])
					return;
				ft_strncpy(input[i].cmd[k], &input[i].input[j], len);
				input[i].cmd[k][len] = '\0';
				k++;
				j += len;
			}
			j++;	
		}
		input[i].cmd[k] = NULL;
		i++;
	}
}

