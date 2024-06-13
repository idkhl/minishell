/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: idakhlao <idakhlao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 11:53:30 by idakhlao          #+#    #+#             */
/*   Updated: 2024/03/18 14:07:41 by idakhlao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

char	*ft_strrchr(char *s, int c)
{
	size_t	i;

	i = ft_strlen(s);
	if (c == 0)
		return ((char *)s + i);
	while (i > 0 && s[i - 1] != (char)c)
		i--;
	if (i > 0)
		return ((char *)&s[i - 1]);
	else
		return (0);
}

/*int main()
{
     char *str = "Hello, world!";
    int character = 'o';

    char *result = ft_strrchr(str, 'o');

    if (result != NULL) {
        printf("Dernière occurrence du caractère '%c' trouvée à l'adresse :
		 %p\n", character, (void *)result);
        printf("Reste de la chaîne à partir de cet emplacement : %s\n",
		 result);
    } else {
        printf("Le caractère '%c' n'a pas été trouvé dans la chaîne.\n",
		 character);
    }

    return 0;
}*/
