/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afrikach <afrikach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/09 14:07:38 by idakhlao          #+#    #+#             */
/*   Updated: 2024/11/05 17:10:33 by afrikach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"
#include "../includes/minishell.h"

char	*ft_strdup(char *s)
{
	char	*dest;
	int		len;
	int		i;

	i = 0;
	len = ft_strlen(s) + 1;
	dest = (char *)malloc(len * sizeof(char));
	if (dest == NULL)
		return (NULL);
	while (s[i])
	{
		dest[i] = s[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}

char	*quoted_strdup(char *s)
{
	char	*dest;
	int		len;
	int		i;
	int		j;
	char	quote_char;

	len = 0;
	i = 0;
	j = 0;
	quote_char = 0;
	if (s[0] == '\'' || s[0] == '"')
		quote_char = s[i++];
	while (s[i++] && !(s[i] == quote_char && s[i + 1] == '\0'))
		len++;
	dest = (char *)malloc(sizeof(char) * (len + 1));
	if (dest == NULL)
		return (NULL);
	if (quote_char != 0)
		i = 1;
	else
		i = 0;
	while (s[i] && !(s[i] == quote_char && s[i + 1] == '\0'))
		dest[j++] = s[i++];
	dest[j] = '\0';
	return (dest);
}

// char	*quoted_strdup(char *s)
// {
// 	char	*dest;
// 	int		len;
// 	int		i;

// 	i = 0;
// 	len = 0;
// 	while (s[len])
// 	{
// 		if (s[len] == '\'' || s[len] == '"')
// 			len += len_with_quote(&s[len]);
// 		else
// 			len++;
// 	}
// 	printf("INFILE LEN === %d\n", len);
// 	// len = ft_strlen(s) + 1;
// 	dest = (char *)malloc(sizeof(char) * (len +1));
// 	if (dest == NULL)
// 		return (NULL);
// 	while (s[i])
// 	{
// 		dest[i] = s[i];
// 		i++;
// 	}
// 	dest[i] = '\0';
// 	return (dest);
// }

/*static void		ft_print_result(char*s)
{
	int		len;

	len = 0;
	while (s[len])
		len++;
	write(1, s, len);
}

int				main(int argc,  char *argv[])
{
	char	str[] = "lorem ipsum dolor sit amet";
	char	*str_dup;

	alarm(5);
	if (argc == 1)
		return (0);
	if (atoi(argv[1]) == 1)
	{
		if (!(str_dup = ft_strdup(str)))
			ft_print_result("NULL");
		else
			ft_print_result(str_dup);
		if (str_dup == str)
			ft_print_result("\nstr_dup's adress == str's adress");
		else
			free(str_dup);
	}
	return (0);
}*/