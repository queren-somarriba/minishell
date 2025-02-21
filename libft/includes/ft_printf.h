/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qsomarri <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/11 14:41:20 by qsomarri          #+#    #+#             */
/*   Updated: 2024/08/22 15:55:51 by qsomarri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include "libft.h"
# include <stdarg.h>
# include <stddef.h>
# include <unistd.h>
# include <stdint.h>

int	ft_printf(const char *format, ...);

int	ft_putchar_count(char c);

int	ft_putnbr_count(int n);

int	ft_putstr_count(char *s);

int	ft_put_unsigned_nbr_count(unsigned int n);

int	ft_put_hexa_count(unsigned long n, char c);

int	ft_putptr_count(void *ptr);

#endif
