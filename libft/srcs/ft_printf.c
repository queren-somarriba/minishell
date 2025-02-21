/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qsomarri <qsomarri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/11 12:30:46 by qsomarri          #+#    #+#             */
/*   Updated: 2024/07/09 14:57:25 by qsomarri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_putchar_count(char c)
{
	ssize_t	res;

	res = write (1, &c, 1);
	return (res);
}

static int	ft_mini_printf(va_list ap, const char *format, size_t index)
{
	int	res;

	res = 0;
	if (format[index] == 'c')
		res = ft_putchar_count(va_arg(ap, int));
	if (format[index] == 's')
		res = ft_putstr_count(va_arg(ap, char *));
	if (format[index] == 'd' || format[index] == 'i')
		res = ft_putnbr_count(va_arg(ap, int));
	if (format[index] == 'u')
		res = ft_put_unsigned_nbr_count(va_arg(ap, unsigned int));
	if (format[index] == 'x' || format[index] == 'X')
		res = ft_put_hexa_count(va_arg(ap, unsigned int), format[index]);
	if (format[index] == 'p')
		res = ft_putptr_count (va_arg(ap, void *));
	if (format[index] == '%')
		res = ft_putchar_count('%');
	return (res);
}

int	ft_printf(const char *format, ...)
{
	va_list	ap;
	int		res;
	size_t	i;

	i = -1;
	res = 0;
	if (format == NULL)
		return (-1);
	va_start(ap, format);
	while (format[++i])
	{
		if (format[i] != '%')
			res += ft_putchar_count(format[i]);
		if (format[i] == '%' && format[i + 1] == '\0')
			return (va_end(ap), -1);
		else if (format[i] == '%' && ft_strchr("cspdiuxX%", format[i + 1]))
		{
			res += ft_mini_printf(ap, format, i + 1);
			i++;
		}
		else if (format[i] == '%' && !ft_strchr("cspdiuxX%", format[i + 1]))
			return (va_end(ap), -1);
	}
	va_end(ap);
	return (res);
}
