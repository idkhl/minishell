/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printptr.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: idakhlao <idakhlao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/04 14:14:08 by idakhlao          #+#    #+#             */
/*   Updated: 2024/03/16 12:10:17 by idakhlao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

int	ft_put_adress(size_t nb)
{
	char		c;
	int			len_sizet;

	len_sizet = 0;
	if (nb >= 16)
	{
		len_sizet += ft_put_adress(nb / 16);
		len_sizet += ft_put_adress(nb % 16);
	}
	else
	{
		if (nb < 10)
			c = nb + 48;
		else
			c = nb - 10 + 'a';
		len_sizet += write(1, &c, 1);
	}
	return (len_sizet);
}

int	ft_putptr(size_t ptr)
{
	int	print_length;

	if (!ptr)
		return (write(1, "(nil)", 5));
	print_length = write(1, "0x", 2);
	print_length += ft_put_adress(ptr);
	return (print_length);
}

int	ft_putnbr(int n)
{
	long int	nb;
	int			len;
	char		c;

	nb = n;
	len = 0;
	if (n < 0)
	{
		len += write(1, "-", 1);
		nb *= -1;
	}
	if (nb >= 10)
		len += ft_putnbr(nb / 10);
	c = nb % 10 + 48;
	len += write(1, &c, 1);
	return (len);
}
