/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: idakhlao <idakhlao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/02 12:05:56 by idakhlao          #+#    #+#             */
/*   Updated: 2024/04/11 09:32:06 by idakhlao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdarg.h>
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>

int		ft_printf( char *str, ...);
int		ft_format(va_list ptr, char format);
int		ft_putchar(char c);
int		ft_putstr(char *str);
int		ft_put_adress(size_t nb);
int		ft_putptr(size_t ptr);
int		ft_putnbr(int n);
int		ft_putunsigned(unsigned int n);
int		ft_puthexa(long int nb, char format);

#endif
