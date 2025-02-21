/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qsomarri <qsomarri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/03 15:25:35 by yamartin          #+#    #+#             */
/*   Updated: 2025/02/18 19:24:57 by qsomarri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	stdin_redir(char *str)
{
	int	fd;

	fd = open(str, O_RDONLY);
	if (fd < 0)
	{
		perror("open");
		return (1);
	}
	if (dup2(fd, STDIN_FILENO) == -1)
		return (perror("dup2"), close(fd), EXIT_FAILURE);
	if (close(fd) == -1)
		return (perror("close"), EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

int	stdout_redir_erase(char *str)
{
	int	fd;

	fd = open(str, O_CREAT | O_RDWR | O_TRUNC, 0644);
	if (fd < 0)
	{
		perror("open");
		return (1);
	}
	if (dup2(fd, STDOUT_FILENO) == -1)
		return (perror("dup2"), close(fd), EXIT_FAILURE);
	if (close(fd) == -1)
		return (perror("close"), EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

int	stdout_redir_append(char *str)
{
	int	fd;

	fd = open(str, O_CREAT | O_RDWR | O_APPEND, 0644);
	if (fd < 0)
	{
		perror("open");
		return (1);
	}
	if (dup2(fd, STDOUT_FILENO) == -1)
		return (perror("dup2"), close(fd), EXIT_FAILURE);
	if (close(fd) == -1)
		return (perror("close"), EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

int	parse_redirection(t_redir *redir)
{
	int	res;

	res = 1;
	if (redir->type == 1)
		res = stdin_redir(redir->target);
	if (redir->type == 2)
	{
		if (dup2(redir->fd, STDIN_FILENO) == -1)
			return (perror("dup2"), EXIT_FAILURE);
		if (close(redir->fd) == -1)
			return (perror("close"), EXIT_FAILURE);
		redir->fd = -1;
		res = 0;
	}
	if (redir->type == 3)
		res = stdout_redir_erase(redir->target);
	if (redir->type == 4)
		res = stdout_redir_append(redir->target);
	return (res);
}
