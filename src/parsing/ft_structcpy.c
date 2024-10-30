/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_structcpy.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afrikach <afrikach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/20 16:51:17 by afrikach          #+#    #+#             */
/*   Updated: 2024/10/30 17:23:40 by afrikach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*ft_structcpy(char *dest, char *src, int i)
{
	int	j;

	j = 0;
	while (ft_isspace(src[i]) == 1)
		i++;
	while (src[i] && ft_isspace(src[i]) != 1)
	{
		dest[j] = src[i];
		i++;
		j++;
	}
	dest[j] = '\0';
	return (dest);
}

char	*ft_strncpy(char *dest, char *src, unsigned int n)
{
	unsigned int	i;

	i = 0;
	while (src[i] != '\0' && i < n)
	{
		dest[i] = src[i];
		++i;
	}
	while (i < n)
	{
		dest[i] = '\0';
		i++;
	}
	return (dest);
}

char	*quotecpy(char *dest, char *src, int n, char quote)
{
	int	i;

	i = 0;
	while (src[i] != '\0' && i < n && src[i] != quote)
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}

char	*join_str(char *s1, char *s2)
{
	char	*res;
	int		len;

	if (!s1 && !s2)
		return (NULL);
	if (!s1)
		return (ft_strdup(s2));
	len = ft_strlen(s1) + ft_strlen(s2) + 1;
	res = malloc(len * sizeof(char));
	if (res == NULL)
		return (NULL);
	*res = '\0';
	ft_strncat(res, s1, ft_strlen(s1));
	ft_strncat(res, s2, ft_strlen(s2));
	free(s1);
	return (res);
}

char	*join_char(char *s1, char c)
{
	char	*res;
	int		len;

	if (!s1 && !c)
		return (NULL);
	if (!s1)
	{
		res = malloc(2 * sizeof(char));
		if (res == NULL)
			return (NULL);
		res[0] = c;
		res[1] = '\0';
		return (res);
	}
	len = ft_strlen(s1) + 2;
	res = malloc(len * sizeof(char));
	if (res == NULL)
		return (NULL);
	*res = '\0';
	ft_strncat(res, s1, ft_strlen(s1));
	res[len - 2] = c;
	res[len - 1] = '\0';
	free(s1);
	return (res);
}
