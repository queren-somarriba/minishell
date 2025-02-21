/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qsomarri <qsomarri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 15:43:35 by qsomarri          #+#    #+#             */
/*   Updated: 2024/11/29 14:02:35 by qsomarri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_compute_size(int n)
{
	int		n2;
	size_t	size;

	n2 = n;
	size = 0;
	if (n <= 0)
	{
		size++;
		n2 = -n;
	}
	while (n2 > 0)
	{
		n2 /= 10;
		size++;
	}
	return (size);
}

static long	ft_compute_size_long(long n)
{
	long	n2;
	size_t	size;

	n2 = n;
	size = 0;
	if (n <= 0)
	{
		size++;
		n2 = -n;
	}
	while (n2 > 0)
	{
		n2 /= 10;
		size++;
	}
	return (size);
}

char	*ft_itoa(int n)
{
	int		n2;
	size_t	size;
	char	*dest;

	size = ft_compute_size(n);
	n2 = n;
	if (n == INT_MIN)
		return (ft_strdup("-2147483648"));
	dest = (char *)malloc(sizeof(char) * (size + 1));
	if (dest == NULL)
		return (NULL);
	if (n < 0)
		n2 = -n;
	dest[size] = '\0';
	while (size)
	{
		dest[--size] = (n2 % 10) + '0';
		n2 /= 10;
	}
	if (n < 0)
		dest[0] = '-';
	return (dest);
}

char	*ft_ltoa(long n)
{
	long		n2;
	size_t		size;
	char		*dest;

	size = ft_compute_size_long(n);
	n2 = n;
	if (n == LLONG_MIN)
		return (ft_strdup("-9223372036854775807"));
	dest = (char *)malloc(sizeof(char) * (size + 1));
	if (dest == NULL)
		return (NULL);
	if (n < 0)
		n2 = -n;
	dest[size] = '\0';
	while (size)
	{
		dest[--size] = (n2 % 10) + '0';
		n2 /= 10;
	}
	if (n < 0)
		dest[0] = '-';
	return (dest);
}
