/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_expand.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afrikach <afrikach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 13:27:28 by afrikach          #+#    #+#             */
/*   Updated: 2024/10/01 14:07:41 by afrikach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

// $USER"frwwr" -> USER;
// f(USER) -> afrikach;
// f(USER) -> "";


// si guillemets simple ouvert on n'interprete pas (on return direct le nom de la variable)
// else on interprete et on appelle look_for_expand.
char *add_to_input(char *str, t_data data);
//on parcours et on ajoute au fur et a mesure si ce n'est pas un guillemet
// si c'est un guillemets on appel la fonction 
char *look_for_expand(t_input input, t_data data); // elle est appelee dans add_to_input
//des que str[i] == $ et que la fonction pour interpreter l'expand me renvoie true
//elle doit me return ce par quoi je dois remplacer la variable $USER (afrikach)


//input[i].input : [< in"$USER" cat]

