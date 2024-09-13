/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inesdakhlaoui <inesdakhlaoui@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 12:28:21 by inesdakhlao       #+#    #+#             */
/*   Updated: 2024/09/09 12:28:45 by inesdakhlao      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	identify_redir(t_data *data, char **tab)
{
	char **redir_before; //les mettre dans une structure
	char **redir_after;

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
	while (redir_before[i])
		exec_redir(data, redir_before[i]);
	exec_command();
	while (redir_after[i])
		exec_redir(data, redir_after[i]);
}