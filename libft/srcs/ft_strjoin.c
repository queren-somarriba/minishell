/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qsomarri <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 18:51:53 by qsomarri          #+#    #+#             */
/*   Updated: 2024/06/27 18:18:47 by qsomarri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t	i;
	size_t	s1_len;
	char	*dest;

	i = -1;
	if (!s1)
	{
		s1 = ft_strdup("");
		if (!s1)
			return (NULL);
	}
	s1_len = ft_strlen(s1);
	dest = (char *)malloc(sizeof(const char) * (s1_len + ft_strlen(s2) + 1));
	if (dest == NULL)
		return (NULL);
	while (s1[++i])
		dest[i] = s1[i];
	i = -1;
	while (s2[++i])
		dest[s1_len + i] = s2[i];
	dest[s1_len + i] = '\0';
	return (dest);
}
