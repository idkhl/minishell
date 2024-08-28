/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_pipes.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: idakhlao <idakhlao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/27 19:23:30 by idakhlao          #+#    #+#             */
/*   Updated: 2024/08/28 18:37:12 by idakhlao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	count_blocks(char *line)
{
	int	size;
	int	i;

	size = 0;
	i = 0;
	while (line[i])
    {
        if (line[i] == 34 || line[i] == 39)
        {
            i++;
            while ((line[i] != 34 && line[i] != 39) && line[i])
                i++;
        }
        else if (line[i] == '|')
        {
            size++;
            i++;
        }
        else
        {
            i++;
        }
    }

    return (size);
}


// char	**add_blocks(char **bloc, char *line)
// {
// 	int	i;
// 	int	j;

// 	i = 0;
// 	j = 0;
// 	while (line[i])
// 	{
// 		if (line[i] == 34 || line[i] == 39)
// 		{
// 			i++;
// 			while ((line[i] != 34 && line[i] != 39) && line[i])
// 				i++;
// 		}
// 		while (line[i] != '|' && line[i])
// 			i++;
		
// 	}
// }

char	**split_pipes(char *line)
{
	int		size;
	char	**split;

	if (!line)
		return (NULL);
	size = count_blocks(line);
	printf("%d\n", size);
	split = (char **)malloc((size + 1) * sizeof(char *));
	if (!split)
		return (NULL);
	// split = add_blocks(split, line);
	return (ft_split(line, ' '));
}