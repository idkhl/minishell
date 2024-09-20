/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_struct.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afrikach <afrikach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/13 15:19:09 by afrikach          #+#    #+#             */
/*   Updated: 2024/09/20 16:29:05 by afrikach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	find_quotes(char *s, int index)
{
	int simple_quote;
	int	double_quote;
	int i;
	
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

int get_redirection_length(char *s) 
{
    int i;
    int length;

	i = 0;
	length = 0;
    while (s[i])
	{
        if (!find_quotes(s, i) && (s[i] == '<' || s[i] == '>'))
		{
			if ((s[i + 1] == '<' && s[i] == '<') || (s[i + 1] == '>' && s[i] == '>'))
                i += 2;
			else
				i++;
			while (s[i] && ft_isspace(s[i]))
				i++;
			while (s[i] && !ft_isspace(s[i]) && s[i] != '<' && s[i] != '>') 
			{
				if (s[i] && s[i] == '\"')
					i++;
				else
				{
					length++;
					i++;
				}
			}
			return (length);
		}
		i++;
	}
	return 0;
}

int		find_redirection(char *s)
{
	int i;

	i = 0;
	while (s[i])
	{
		if (!find_quotes(s, i) && (s[i] == '<' || s[i] == '>'))
			return (i);
		i++;
	}
	return (-1);
}
char	*get_redir_type(char *s, int index)
{
	if (s[index] == '<')
	{
        if (s[index + 1] == '<')
            return ft_strdup("<<");
        else
            return ft_strdup("<");
    } 
	else if (s[index] == '>')
	{
        if (s[index + 1] == '>')
            return ft_strdup(">>");
        else
            return ft_strdup(">");
    }
    return (NULL);
}
int get_redirection_start(char *s) 
{
    int i;

	i = 0;
    while (s[i])
	{
        if (!find_quotes(s, i) && (s[i] == '<' || s[i] == '>'))
		{
			if ((s[i + 1] == '<' && s[i] == '<') || (s[i + 1] == '>' && s[i] == '>'))
                i += 2;
			else
				i++;
			while (s[i] && ft_isspace(s[i]))
				i++;
			while (s[i] && !ft_isspace(s[i]) && s[i] != '<' && s[i] != '>') 
			{
				if (s[i] && s[i] == '\"')
					i++;
				else
				{
					return(i);
					i++;
				}
			}
		}
		i++;
	}
	return 0;
}
void	add_redir_struct(t_input *input)
{
	int i;
	int j;

	i = 0;
	while (input[i].input)
	{
		printf("Analyzing input[%d]: %s\n", i, input[i].input);
		j = 0;
		while ((find_redirection(&input[i].input[j])) != -1)
		{
			if (input[i].input[j] == '<' && input[i].input[j + 1] == '<')
			{
				printf("Found '<<' at position %d\n", j);
				input[i].redir_infile = get_redir_type(input[i].input, j);
				printf("redir_infile set to <<: %s\n", input[i].redir_infile);
				j += 2;
			}
			else if (input[i].input[j] == '<')
			{
				printf("Found '<' at position %d\n", j);
				input[i].redir_infile = get_redir_type(input[i].input, j);
				printf("redir_infile set to <: %s\n", input[i].redir_infile);
				j++;
			}
			else
				j++;
		}
		i++;
	}
	return ;
}
void	add_redir_struct2(t_input *input)
{
	int i;
	int j;

	i = 0;
	while (input[i].input)
	{
		printf("================[%d]===============\n", i);
		printf("Analyzing input[%d]: %s\n", i, input[i].input);
		j = 0;
		while ((find_redirection(&input[i].input[j])) != -1)
		{
			if (input[i].input[j] == '>' && input[i].input[j + 1] == '>')
			{
				printf("Found '>>' at position %d\n", j);
				input[i].redir_outfile = get_redir_type(input[i].input, j);
				printf("redir_outfile set to >>: %s\n", input[i].redir_outfile);
				j += 2;
			}
			else if (input[i].input[j] == '>')
			{
				printf("Found '>' at position %d\n", j);
				input[i].redir_outfile = get_redir_type(input[i].input, j);
				printf("redir_outfile set to >: %s\n", input[i].redir_outfile);
				j++;
			}
			else
				j++;
		}
		i++;
	}
}



// void	skip_redir(t_input *input, char *line)
// {
// 	int		i;
// 	int		j;
// 	int		k;
// 	int		nb_blocks;
	
// 	i = 0;
// 	nb_blocks = count_blocks(line);
// 	while (i < nb_blocks)
// 	{
// 		j = 0;
// 		k = 0;
// 		input[i].cmd = malloc(sizeof(char *) * (count_cmds(input[i].tab) + 1));
// 		if (!input[i].cmd)
// 			return ;
		
// 		while (input[i].tab[j])
// 		{
// 			if (ft_strcmp(input[i].tab[j], "<") == 0 
// 				|| ft_strcmp(input[i].tab[j], ">") == 0 
// 				|| ft_strcmp(input[i].tab[j], ">>") == 0 
// 				|| ft_strcmp(input[i].tab[j], "<<") == 0)
// 			{
// 				j += 2;
// 				continue;
// 			}
// 			input[i].cmd[k] = ft_strdup(input[i].tab[j]);
// 			k++;
// 			j++;
// 		}
// 		input[i].cmd[k] = NULL;
// 		i++;
// 	}
// }

