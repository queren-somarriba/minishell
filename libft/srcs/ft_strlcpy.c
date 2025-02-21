/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qsomarri <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 17:27:28 by qsomarri          #+#    #+#             */
/*   Updated: 2024/05/29 15:04:46 by qsomarri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t size)
{
	size_t	len;
	size_t	i;

	len = 0;
	i = -1;
	while (src[len] != '\0')
		len++;
	if (size <= 0)
		return (len);
	while (src[++i] != '\0' && i < size - 1)
		dst[i] = src[i];
	dst[i] = '\0';
	return (len);
}
