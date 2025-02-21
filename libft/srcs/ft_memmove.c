/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qsomarri <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 16:02:57 by qsomarri          #+#    #+#             */
/*   Updated: 2024/05/29 14:59:46 by qsomarri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h" 

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	unsigned char	*dest2;
	unsigned char	*src2;
	size_t			i;

	dest2 = (unsigned char *)dest;
	src2 = (unsigned char *)src;
	i = -1;
	if (!dest && !src)
		return (NULL);
	if (dest < src)
	{
		while (++i < n)
			dest2[i] = src2[i];
	}
	else
	{	
		while (++i < n)
			dest2[n - i - 1] = src2[n - i - 1];
	}
	return (dest2);
}
