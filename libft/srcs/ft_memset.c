/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qsomarri <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 14:00:15 by qsomarri          #+#    #+#             */
/*   Updated: 2024/05/29 14:30:02 by qsomarri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

void	*ft_memset(void *s, int c, size_t n)
{
	unsigned char	c2;
	unsigned char	*s2;

	c2 = (unsigned char)c;
	s2 = (unsigned char *)s;
	while (n--)
		s2[n] = c2;
	return (s2);
}
