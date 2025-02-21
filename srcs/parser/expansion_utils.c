/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qsomarri <qsomarri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/31 15:00:31 by qsomarri          #+#    #+#             */
/*   Updated: 2025/02/19 18:04:42 by qsomarri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	check_dollar(char *str, size_t i)
{
	if (i > 0 && !ft_strncmp(&str[i - 1], "\"$\"", 3))
		return (true);
	if (str[i] == '$' && str[i + 1] && ft_is_white_space(str[i + 1]))
		return (true);
	return (false);
}

char	*remove_dollar(char *str, size_t index)
{
	char	*dest;
	char	*tmp;
	char	*tmp2;

	tmp = ft_substr(str, 0, index);
	if (!tmp)
		return (perror("malloc"), NULL);
	tmp2 = ft_substr(str, index + 1, ft_strlen(str) - index);
	if (!tmp2)
		return (perror("malloc"), free(tmp), NULL);
	dest = ft_strjoin(tmp, tmp2);
	if (!dest)
		return (perror("malloc"), free(tmp), free(tmp2), NULL);
	return (free(tmp), free(tmp2), dest);
}

char	*dollar_varname(char *str)
{
	char	*dest;
	size_t	i;
	size_t	j;
	size_t	len;

	i = -1;
	j = 0;
	len = 0;
	while (str[++i] && str[i] != '$')
	{
		if (str[i] == '\"' && str[i + 1] && ((i && i != j) || !i))
			j = i + go_to_nextquote(str, i);
		if (str[i] == '\'' && i >= j)
			i += go_to_nextquote(str, i);
	}
	if (str[i] == '$')
		i++;
	len = i;
	while (str[len] && ft_isalnum(str[len]))
		len++;
	dest = ft_substr(str, i, len - i);
	if (!dest)
		return (perror("malloc"), NULL);
	return (dest);
}

char	*expand_no_var(char *str, size_t dollar_str_len, size_t index)
{
	char	*tmp;
	char	*tmp2;
	char	*dest;

	tmp = ft_substr(str, 0, index - 1);
	if (!tmp)
		return (perror("malloc"), NULL);
	tmp2 = ft_substr(str, index + dollar_str_len,
			ft_strlen (str) - (index + dollar_str_len));
	if (!tmp2)
		return (perror("malloc"), free(tmp), NULL);
	dest = ft_strjoin(tmp, tmp2);
	if (!dest)
		return (perror("malloc"), free(tmp), free(tmp2), NULL);
	free(tmp);
	free(tmp2);
	return (dest);
}
