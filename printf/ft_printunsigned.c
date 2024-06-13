/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printunsigned.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: idakhlao <idakhlao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/04 14:47:13 by idakhlao          #+#    #+#             */
/*   Updated: 2024/03/16 12:10:17 by idakhlao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

int	ft_putunsigned(unsigned int n)
{
	long unsigned int	nb;
	int					len;
	char				c;

	nb = n;
	len = 0;
	if (nb >= 10)
		len += ft_putunsigned(nb / 10);
	c = nb % 10 + 48;
	len += write(1, &c, 1);
	return (len);
}

int	ft_puthexa(long int nb, char format)
{
	int			len;
	char		c;

	len = 0;
	if (nb < 0)
	{
		len += write(1, "-", 1);
		nb *= -1;
	}
	if (nb >= 16)
	{
		len += ft_puthexa(nb / 16, format);
		len += ft_puthexa(nb % 16, format);
	}
	else
	{
		if (nb < 10)
			c = nb + 48;
		else
			c = nb - 10 + format - 23;
		len += write(1, &c, 1);
	}
	return (len);
}
