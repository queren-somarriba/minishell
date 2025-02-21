/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qsomarri <qsomarri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 12:59:52 by qsomarri          #+#    #+#             */
/*   Updated: 2024/12/03 17:25:04 by qsomarri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	is_quoted(const char *str, size_t index)
{
	size_t	i;
	bool	res;
	bool	res2;

	i = -1;
	res = 0;
	res2 = 0;
	while (str[++i] && i < index)
	{
		if (str[i] == '\"')
			res = (res + 1) % 2;
	}
	i = -1;
	while (str[++i] && i < index)
	{
		if (str[i] == '\'')
			res2 = (res2 + 1) % 2;
	}
	if (res || res2)
		return (true);
	return (false);
}

static int	ft_count_str(const char *s, char c)
{
	size_t	i;
	int		count;

	i = 0;
	count = 0;
	while (s[i])
	{
		while (s[i] == c && s[i])
			i++;
		if (s[i] != '\0')
			count++;
		while (s[i] && (s[i] != c || (s[i] == c && is_quoted(s, i))))
			i++;
	}
	return (count);
}

static char	*ft_str_index_cpy(const char *s, int index, char c)
{
	size_t	i;
	char	*dest;

	i = 0;
	while (s[index + i] && (s[index + i] != c
			|| (s[index + i] == c && is_quoted(s, i + index))))
		i++;
	dest = (char *)malloc(sizeof(const char) * (i + 1));
	if (dest == NULL)
		return (NULL);
	i = 0;
	while (s[index + i] && (s[index + i] != c
			|| (s[index + i] == c && is_quoted(s, i + index))))
	{
		dest[i] = s[index + i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}

static	char	**ft_makesplit(char **dest, const char *s, char c)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	while (s[i])
	{
		while (s[i] == c && s[i])
			i++;
		if (s[i] != '\0')
		{
			dest [j] = ft_str_index_cpy(s, i, c);
			if (!dest[j])
			{
				ft_free_array(dest);
				return (NULL);
			}
			j++;
			while (s[i] && (s[i] != c || (s[i] == c && is_quoted(s, i))))
				i++;
		}
	}
	dest[j] = NULL;
	return (dest);
}

char	**ft_split(const char *s, char c)
{
	size_t	len;
	char	**dest;

	len = ft_count_str(s, c);
	dest = (char **)malloc(sizeof(const char *) * (len + 1));
	if (dest == NULL)
		return (NULL);
	dest = ft_makesplit(dest, s, c);
	return (dest);
}
