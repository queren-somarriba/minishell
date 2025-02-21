/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qsomarri <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 18:21:33 by qsomarri          #+#    #+#             */
/*   Updated: 2024/05/31 18:18:21 by qsomarri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t	i;
	char	*dest;
	size_t	slen;

	i = 0;
	slen = ft_strlen(s);
	if (start > slen)
		dest = (char *)malloc(sizeof(char));
	else
	{
		if (len > slen - start)
			len = slen - start;
		dest = (char *)malloc(sizeof(char) * (len + 1));
	}
	if (dest == NULL)
		return (NULL);
	while (i < len && (start + i) < slen)
	{
		dest[i] = s[start + i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}
