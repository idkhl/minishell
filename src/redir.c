/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inesdakhlaoui <inesdakhlaoui@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 12:28:21 by inesdakhlao       #+#    #+#             */
/*   Updated: 2024/09/09 19:21:38 by inesdakhlao      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	is_redir(char **tab)
{
	int	i;

	i = 0;
	while (tab[i])
	{
		if (ft_strncmp(tab[i], ">", 1) == 0 || ft_strncmp(tab[i], "<", 1) == 0)
			return (1);
		i++;
	}
	return (0);
}

char	**malloc_redir_before(char **tab, int i)
{
	int	j;

	j = ft_tablen(tab);
	while (j != i)
	{
		free(tab[j]);
		j--;
	}
	tab[j] = NULL;
	return (ft_tabdup(tab));
}

void	identify_redir(t_data *data, char **tab)
{
	char **redir_before; //les mettre dans une structure
	// char **redir_after;
	int	i;

	i = 0;
	// saute les premieres redirections
	while (tab[i])
	{
		if (ft_strncmp(tab[i], ">", 1) == 0 || ft_strncmp(tab[i], "<", 1) == 0)
			i++;
		else
			break ;
		i++;
	}
	redir_before = malloc_redir_before(tab, i); // free tout ce qui est apres
	int j = 0;
	while (redir_before[j])
	{
		printf("[%s]", redir_before[j]);
		j++;
	}
	//A PARTIR DE LA CA MARCHE PLUS
	while (tab[i])
	{
		if (ft_strncmp(tab[i], ">", 1) == 0 || ft_strncmp(tab[i], "<", 1) == 0)
			break ;
		i++;
	}
	printf("%d\n", i);
	(void)data;
	// redir_after = malloc_redir_after(tab, i);

	
	// dans une boucle: if redir -> mettre la redir + le mot d'apres(le fichier)
	// -> tant qu'il y a une paire redir + fichier la mettre a la suite dans le char **
	// si un mot en + de la paire redir+fichier -> c'est la commande on arrete le char ** 
	// -> on a notre redir_before
	// autre boucle apres avoir saute la partie commande+option+arg
	// -> meme chose pour redir_after
}

void	redir(t_data *data, char **tab)
{
	if (is_redir(tab) == 0)
		return ;
	identify_redir(data, tab);
	// while (redir_before[i])
	// 	exec_redir(data, redir_before[i]);
	// exec_command();
	// while (redir_after[i])
	// 	exec_redir(data, redir_after[i]);
}