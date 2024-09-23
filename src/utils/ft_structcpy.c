/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_structcpy.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afrikach <afrikach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/20 16:51:17 by afrikach          #+#    #+#             */
/*   Updated: 2024/09/23 16:20:19 by afrikach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*ft_structcpy(char *dest, char *src, int i)
{
	int j;

	j = 0;
	while (ft_isspace(src[i]) == 1)
		i++;
	while (src[i] != '\0' && ft_isspace(src[i]) != 1)
	{
		dest[j] = src[i];
		i++;
		j++;
	}
	dest[j] = '\0';
	return (dest);
}