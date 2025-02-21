/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qsomarri <qsomarri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 12:22:50 by qsomarri          #+#    #+#             */
/*   Updated: 2024/07/04 13:04:24 by qsomarri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

static char	*ft_join_buffer(int fd, char *stock)
{
	ssize_t	r;
	char	*buff;

	r = 1;
	buff = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buff)
		return (ft_free(&stock));
	buff[0] = '\0';
	while (r > 0 && !ft_strchr(buff, '\n'))
	{
		r = read(fd, buff, BUFFER_SIZE);
		if (r > 0)
		{
			buff[r] = '\0';
			stock = ft_strjoin2(stock, buff);
		}
	}
	free(buff);
	if (r == -1)
		return (ft_free(&stock));
	return (stock);
}

static char	*ft_set_line(char *stock)
{
	size_t	len;
	char	*line;
	char	*tmp;

	tmp = ft_strchr(stock, '\n');
	len = (tmp - stock) + 1;
	line = ft_substr(stock, 0, len);
	if (!line)
		return (NULL);
	return (line);
}

static char	*ft_set_stock(char *stock)
{
	size_t	len;
	char	*tmp;
	char	*clean_stock;

	tmp = ft_strchr(stock, '\n');
	if (!tmp)
	{
		clean_stock = NULL;
		return (ft_free(&stock));
	}
	len = (tmp - stock) + 1;
	if (!stock[len])
		return (ft_free(&stock));
	clean_stock = ft_substr(stock, len, ft_strlen(stock) - len);
	ft_free(&stock);
	if (!clean_stock)
		return (NULL);
	return (clean_stock);
}

char	*get_next_line(int fd)
{
	char		*line;
	static char	*stock[1024];

	if (fd < 0 || fd > 1024 || BUFFER_SIZE <= 0)
		return (NULL);
	if ((stock[fd] && !ft_strchr(stock[fd], '\n')) || !stock[fd])
		stock[fd] = ft_join_buffer(fd, stock[fd]);
	if (!stock[fd])
		return (NULL);
	line = ft_set_line(stock[fd]);
	if (!line)
		return (ft_free(&stock[fd]));
	stock[fd] = ft_set_stock(stock[fd]);
	return (line);
}
