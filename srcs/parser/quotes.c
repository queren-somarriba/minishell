/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qsomarri <qsomarri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 15:49:09 by qsomarri          #+#    #+#             */
/*   Updated: 2025/02/18 12:25:41 by qsomarri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

size_t	go_to_nextquote(char *str, size_t index)
{
	size_t	i;

	i = 0;
	if (str[index] == '\'')
	{
		while (str[++i + index])
		{
			if (str[i + index] == str[index])
				return (i);
		}
		return (0);
	}
	else
	{
		while (str[++i + index])
		{
			if (str[i + index] == str[index])
				return (i);
		}
		return (0);
	}
}

size_t	count_quotes(char *str)
{
	size_t	i;
	size_t	count;

	i = -1;
	count = 0;
	while (str[++i])
	{
		if ((str[i] == '\"' || str[i] == '\''))
		{
			if (go_to_nextquote(str, i))
			{
				count++;
				i += go_to_nextquote(str, i);
				count++;
			}
		}
	}
	return (count);
}

static char	*ft_strdup_nospace(char *s)
{
	char	*dest;
	size_t	len;
	size_t	i;

	i = -1;
	len = -1;
	if (!s)
		return (NULL);
	while (s[++i] && ft_is_white_space(s[i]))
		continue ;
	while (s[++len])
		continue ;
	while (len > 0 && s[--len] && ft_is_white_space(s[len]))
		continue ;
	dest = ft_substr(s, i, len - i + 1);
	if (!dest)
		return (perror("malloc"), NULL);
	return (dest);
}

static void	cpy_without_quotes(char *dest, char *str)
{
	size_t	i;
	size_t	j;

	i = -1;
	j = -1;
	while (str[++i])
	{
		if (str[i] == '\"')
		{
			while (str[++i] && str[i] != '\"')
				dest[++j] = str[i];
		}
		else if (str[i] == '\'')
		{
			while (str[++i] && str[i] != '\'')
				dest[++j] = str[i];
		}
		else
			dest[++j] = str[i];
	}
	dest[++j] = '\0';
}

char	*remove_quotes(char *str)
{
	char	*dest;
	char	*tmp;
	size_t	len;

	len = 0;
	tmp = ft_strdup_nospace(str);
	if (!tmp)
		return (NULL);
	len = ft_strlen(tmp) - count_quotes(tmp) + 1;
	dest = malloc(sizeof(char) * len);
	if (!dest)
		return (error_msg("malloc"), NULL);
	if (count_quotes(tmp) % 2 == 0 && count_quotes(tmp))
		cpy_without_quotes(dest, tmp);
	else
	{
		free(dest);
		dest = ft_strdup(tmp);
		if (!dest)
			return (perror("malloc"), NULL);
	}
	free(tmp);
	return (dest);
}
