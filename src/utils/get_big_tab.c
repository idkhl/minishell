/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_big_tab.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afrikach <afrikach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/31 16:13:38 by idakhlao          #+#    #+#             */
/*   Updated: 2024/09/13 18:54:01 by afrikach         ###   ########.fr       */
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
		input[i].input= malloc(sizeof(char) * ft_strlen(tab[i]) + 1);
		// input[i].input = ft_strdup(tab[i]);
		if (input[i].input == NULL)
            perror("fill input = Failed to allocate memory for input[i]");
		ft_strcpy(input[i].input, tab[i]);
		input[i].tab = split_quotes(tab[i], ' ');
		i++;
	}
	input[nb_blocks].input = NULL;
	malloc_free(tab);
}

void	allocate_new_struct(t_input *tab, char *line)
{
	int		nb_blocks;
	nb_blocks = count_blocks(line);
	tab = malloc(sizeof(t_input) * nb_blocks + 1);
	if (tab == NULL)
	{
		perror("Failed to allocate memory for t_input");
		return ;
	}
	
}


// // Fonction pour trouver le premier mot après une redirection
// void find_first_redir(t_input *tab, char **big_tab)
// {
//     int i;
	
// 	i = 0;
//     while (big_tab[i]) 
// 	{
//         int j = 0;
//         while (big_tab[i][j])
// 		{
//             if (big_tab[i][j] == '<' && big_tab[i][j + 1] != '<')
// 			{
//                 j++; 
//                 while (ft_isspace(big_tab[i][j]))
//                     j++;
//                 if (big_tab[i][j] != '\0')
// 				{
// 					if (tab->in_file != NULL)
//                         free(tab->in_file);
//                     tab->in_file = allocate_and_copy_redir(&big_tab[i][j], j);
//                     if (tab->in_file != NULL)
//                         return ;
//                 }
//             }
//             j++;
//         }
// 		i++;
//     }
// }

// char	***get_big_tab(char *line)
// {
// 	char	***result;
// 	int		i;
// 	int		nb_blocks;
// 	char	**tab;

// 	i = 0;
// 	tab = split_pipes(line);
// 	if (!tab)
// 		return (NULL);
// 	nb_blocks = count_blocks(line);
// 	result = (char ***)malloc((nb_blocks + 1) * sizeof(char **));
// 	if (!result)
// 	{
// 		perror("allocation failed\n");
// 		return (free(tab), NULL);
// 	}
// 	while (i < nb_blocks)
// 	{
// 		result[i] = split_quotes(tab[i], ' ');
// 		if (!result[i])
// 			return (malloc_free(tab), NULL);
// 		i++;
// 	}
// 	malloc_free(tab);
// 	return (result);
// }

	
