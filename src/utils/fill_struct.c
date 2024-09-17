/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_struct.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afrikach <afrikach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/13 15:19:09 by afrikach          #+#    #+#             */
/*   Updated: 2024/09/17 13:00:04 by afrikach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	find_quotes(char *s, int i)
{
	int simple_quote;
	int	double_quote;
	
	simple_quote = 0;
	double_quote = 0;
	while (s[i])
	{
		if (s[i] == '\'' && double_quote == 0)
			simple_quote = !simple_quote;
		else if (s[i] == '"' && simple_quote == 0)
			double_quote = !double_quote;
		i++;
	}
	if (simple_quote || double_quote)
		return (1);
	return (0);
}
int	get_redirection(char *s)
{
	int	i;
	int		length;
	
	i = 0;
	length = 0;
	while(s[i])
	{
		if (s[i] == '<'|| s[i] == '>')
		{
			if(find_quotes(s, i))
				return(-1);
			if (s[i] && ft_isspace(s[i]))
				i++;
			while (s[i] && !ft_isspace(s[i]) && (s[i] != '<' || s[i] != '>'))
			{
				length++;
				i++;
			}
		}
		else
			i++;
	}
	return (length);
}

int get_redirection_length(char *s, int start_index)
{
    int i = start_index;
    int length;
	
	length = 0;
    while (s[i] && ft_isspace(s[i]))
        i++;
    while (s[i] && !ft_isspace(s[i]) && s[i] != '<' && s[i] != '>')
    {
        length++;
        i++;
    }
    return (length);
}

void allocate_and_copy_redir(t_input *input, char *line)
{
    int i;
    int j;
    int nb_blocks = count_blocks(line);
	int length;

	i = 0;
    while (i < nb_blocks)
	{
        j = 0;
        while (input[i].input[j])
		{
            if (input[i].input[j] == '<')
			{
                length = get_redirection_length(input[i].input, j + 1);
                if (input[i].in_file)
                    free(input[i].in_file);

                input[i].in_file = malloc(sizeof(char) * (length + 1));
                if (input[i].in_file == NULL)
				{
                    perror("allocate_and_copy_redir: Failed to allocate memory for input[i].in_file");
                    return;
                }
				while (ft_isspace(input[i].input[j]))
					j++;
                ft_strncpy(input[i].in_file, &input[i].input[j + 1], length);
                input[i].in_file[length] = '\0';

                j += length + 1;
            }
            else if (input[i].input[j] == '>')
			{
                int length = get_redirection_length(input[i].input, j + 1);

                if (input[i].out_file) {
                    free(input[i].out_file);
                }
                input[i].out_file = malloc(sizeof(char) * (length + 1));
                if (input[i].out_file == NULL)
				{
                    perror("allocate_and_copy_redir: Failed to allocate memory for input[i].out_file");
                    return;
                }
				while (ft_isspace(input[i].input[j]))
					j++;
                ft_strncpy(input[i].out_file, &input[i].input[j + 1], length);
                input[i].out_file[length] = '\0';
                j += length + 1;
            }
            else
                j++;
        }
        i++;
    }
}

// void	allocate_and_copy_redir(t_input *input, char *line)
// // {
// // 	int		i;
// // 	int		j;
// // 	int		nb_blocks;
	
	
// // 	i = 0;
// // 	nb_blocks = count_blocks(line);
// // 	while (i < nb_blocks)
// // 	{
// // 		j = 0;
// // 		while (input[i].input[j])
// // 		{
			
// // 			if (get_redirection(input[i].input) != -1 && ft_strcmp(&input[i].input[j], "<") == 0)
// // 			{
// // 				input[i].in_file = malloc(sizeof(char) * get_redirection(input[i].input));
// // 				if (input[i].in_file == NULL)
// //             		perror("allocate and redir = Failed to allocate memory for input[i]");
// // 				ft_strcpy(input[i].in_file, &input[i].input[j]);
// // 				j++;
// // 			}
// // 			else if (get_redirection(input[i].input) != -1 && ft_strcmp(&input[i].input[j], ">") == 0)
// // 			{
// // 				input[i].out_file = malloc(sizeof(char) * get_redirection(input[i].input));
// // 				if (input[i].out_file == NULL)
// //             		perror("allocate and copy redir = Failed to allocate memory for input[i]");
// // 				ft_strcpy(input[i].out_file, &input[i].input[j]);
// // 				j++;
				
// // 			}
// // 		}
// // 		i++;
// // 	}
// // }
int count_cmds(char **tab)
{
	int i = 0;
	int count = 0;

	while (tab[i])
	{
		if (ft_strcmp(tab[i], "<") != 0 && ft_strcmp(tab[i], ">") != 0
			&& ft_strcmp(tab[i], ">>") != 0 && ft_strcmp(tab[i], "<<") != 0)
		{
			count++;
		}
		else
		{
			i++;
		}
		i++;
	}
	return (count);
}

void	skip_redir(t_input *input, char *line)
{
	int		i;
	int		j;
	int		k;
	int		nb_blocks;
	
	i = 0;
	nb_blocks = count_blocks(line);
	while (i < nb_blocks)
	{
		j = 0;
		k = 0;
		input[i].cmd = malloc(sizeof(char *) * (count_cmds(input[i].tab) + 1));
		if (!input[i].cmd)
			return ;
		
		while (input[i].tab[j])
		{
			
			if (ft_strcmp(input[i].tab[j], "<") == 0 
				|| ft_strcmp(input[i].tab[j], ">") == 0 
				|| ft_strcmp(input[i].tab[j], ">>") == 0 
				|| ft_strcmp(input[i].tab[j], "<<") == 0)
			{
				j += 2;
				continue;
			}
			input[i].cmd[k] = ft_strdup(input[i].tab[j]);
			k++;
			j++;
		}
		input[i].cmd[k] = NULL;
		i++;
	}
}

