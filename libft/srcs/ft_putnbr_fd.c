/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qsomarri <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 18:40:37 by qsomarri          #+#    #+#             */
/*   Updated: 2024/05/30 16:49:56 by qsomarri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putnbr_fd(int n, int fd)
{
	int	nb2;

	nb2 = n;
	if (n == -2147483648)
		write(fd, "-2147483648", 11);
	else
	{
		if (n < 0)
		{
			ft_putchar_fd('-', fd);
			nb2 = -n;
		}
		if (nb2 < 10)
			ft_putchar_fd(nb2 + '0', fd);
		if (nb2 >= 10)
		{
			ft_putnbr_fd(nb2 / 10, fd);
			ft_putnbr_fd(nb2 % 10, fd);
		}
	}
}
