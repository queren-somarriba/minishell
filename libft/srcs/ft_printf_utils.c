/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qsomarri <qsomarri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 18:30:48 by qsomarri          #+#    #+#             */
/*   Updated: 2024/07/09 15:03:03 by qsomarri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_putstr_count(char *s)
{
	size_t	i;

	i = 0;
	if (!s)
	{
		i = write(1, "(null)", 6);
		return (i);
	}
	while (s[i])
		write(1, &s[i++], 1);
	return (i);
}

int	ft_putnbr_count(int n)
{
	int	nb2;
	int	count;

	nb2 = n;
	count = 0;
	if (n == -2147483648)
		count += write(1, "-2147483648", 11);
	else
	{
		if (n < 0)
		{
			count += ft_putchar_count('-');
			nb2 = -n;
		}
		if (nb2 < 10)
		{
			count += ft_putchar_count(nb2 + '0');
		}
		if (nb2 >= 10)
		{
			count += ft_putnbr_count(nb2 / 10);
			count += ft_putnbr_count(nb2 % 10);
		}
	}
	return (count);
}

int	ft_put_unsigned_nbr_count(unsigned int n)
{
	int	count;

	count = 0;
	if (n < 10)
	{
		count += ft_putchar_count(n + '0');
	}
	if (n >= 10)
	{
		count += ft_put_unsigned_nbr_count(n / 10);
		count += ft_put_unsigned_nbr_count(n % 10);
	}
	return (count);
}

int	ft_put_hexa_count(unsigned long n, char c)
{
	size_t	res;
	char	*hexa;

	res = 0;
	if (c == 'x')
		hexa = "0123456789abcdef";
	if (c == 'X')
		hexa = "0123456789ABCDEF";
	if (n < 16)
		res += ft_putchar_count(hexa[n % 16]);
	else if (n >= 16)
	{
		res += ft_put_hexa_count(n / 16, c);
		res += ft_put_hexa_count(n % 16, c);
	}
	return (res);
}

int	ft_putptr_count(void *ptr)
{
	uintptr_t	address;
	size_t		count;

	count = 0;
	if (!ptr)
		count += ft_putstr_count("(nil)");
	else
	{
		address = (uintptr_t)ptr;
		count += ft_putstr_count("0x");
		count += ft_put_hexa_count(address, 'x');
	}
	return (count);
}
