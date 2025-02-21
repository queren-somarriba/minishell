/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qsomarri <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 11:48:33 by qsomarri          #+#    #+#             */
/*   Updated: 2024/05/30 12:20:14 by qsomarri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(char const *s1, char const *set)
{
	size_t	i;
	size_t	len;
	char	*dest;

	i = 0;
	len = ft_strlen (s1);
	while (ft_strchr(set, s1[i]) && s1[i])
			i++;
	while (ft_strchr(set, s1[len - 1]) && len >= 0)
		len--;
	dest = ft_substr(s1, i, len - i);
	return (dest);
}
