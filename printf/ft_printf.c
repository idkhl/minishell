/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: idakhlao <idakhlao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/30 13:27:39 by idakhlao          #+#    #+#             */
/*   Updated: 2024/04/11 09:31:44 by idakhlao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

int	ft_formats(va_list ptr, char format)
{
	int	len;

	len = 0;
	if (format == 'c')
		len += ft_putchar(va_arg(ptr, int));
	else if (format == 's')
		len += ft_putstr(va_arg(ptr, char *));
	else if (format == 'p')
		len += ft_putptr(va_arg(ptr, unsigned long int));
	else if (format == 'd' || format == 'i')
		len += ft_putnbr(va_arg(ptr, int));
	else if (format == 'u')
		len += ft_putunsigned(va_arg(ptr, unsigned int));
	else if (format == 'x' || format == 'X')
		len += ft_puthexa(va_arg(ptr, unsigned int), format);
	else if (format == '%')
		len += ft_putchar('%');
	else
		return (-1);
	return (len);
}

int	ft_printf( char *str, ...)
{
	int		i;
	va_list	args;
	int		print_length;

	i = 0;
	print_length = 0;
	va_start(args, str);
	while (str[i])
	{
		if (str[i] == '%')
		{
			print_length += ft_formats(args, str[i + 1]);
			i++;
		}
		else
			print_length += ft_putchar(str[i]);
		i++;
	}
	va_end(args);
	return (print_length);
}
