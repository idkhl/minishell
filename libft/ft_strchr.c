/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: idakhlao <idakhlao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 10:15:38 by idakhlao          #+#    #+#             */
/*   Updated: 2024/04/11 09:30:55 by idakhlao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

char	*ft_strchr(char *s, int c)
{
	int	i;

	i = 0;
	if (!s)
		return (0);
	if (c == '\0')
		return ((char *)&s[ft_strlen(s)]);
	while (s[i] != '\0')
	{
		if (s[i] == (char) c)
			return ((char *)&s[i]);
		i++;
	}
	return (0);
}

/*int main()
{
     char *p = "hello";
    char *result = ft_strchr(p, 'l');
    if (result != 0)
    {
        printf("Caractère trouvé à l'adresse mémoire : %p\n", (void *)result);
        printf("Le reste de la chaîne à partir de ce point : %s\n", result);
    }
    else
    {
        printf("Caractère non trouvé dans la chaîne.\n");
    }
    return 0;
}*/
/*
int	main()
{
	 char	*p = "hello";
	char *result = ft_strchr(p, 'l');
	printf("%s", (char *)ft_strchr);
}*/

/*#include <stdlib.h>
#include <unistd.h>
#include <ctype.h>

static void		ft_print_result(char*s)
{
	int		len;

	len = 0;
	while (s[len])
		len++;
	write(1, s, len);
}

static void		check_strchr(char *s, int c, int offset)
{
	char		*str;

	if (!(str = ft_strchr(s, c)))
		ft_print_result("NULL");
	else
	{
		ft_print_result(str);
		if (str != (s + offset))
			ft_print_result("\nReturn value is false");
	}
}

int				main(int argc,  char *argv[])
{
	char		str2[] = "bonjour";
	int			arg;

	alarm(5);
	if (argc == 1)
		return (0);
	else if ((arg = atoi(argv[1])) == 1)
		check_strchr(str2, 'b', 0);
	else if (arg == 2)
		check_strchr(str2, 'o', 1);
	else if (arg == 3)
		check_strchr(str2, 'j', 3);
	else if (arg == 4)
		check_strchr(str2, 's', 0);
	else if (arg == 5)
		check_strchr(str2, '\0', 7);
	else if (arg == 6)
	{
		char	str3[] = "";

		check_strchr(str3, '\0', 0);
	}
	return (0);
}*/