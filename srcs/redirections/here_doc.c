/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qsomarri <qsomarri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/31 18:52:55 by qsomarri          #+#    #+#             */
/*   Updated: 2025/02/18 19:25:42 by qsomarri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	loop_exit_eof(char *delimiter, char *tmp)
{
	ft_putstr_fd("warning: here-document delimited ", 2);
	ft_putstr_fd("by end-of-file (wanted `", 2);
	ft_putstr_fd(delimiter, 2);
	error_msg("')");
	if (tmp)
		free(tmp);
}

static void	loop_exit(char *line, char *tmp)
{
	if (line)
		free(line);
	if (tmp)
		free(tmp);
}

static void	here_doc_loop(t_here_doc_str *hd, t_minishell *data, int *fd_pipe)
{
	while (1)
	{
		hd->line = readline("heredoc> ");
		if (!(hd->line) && g_exit_status != 130)
		{
			loop_exit_eof(hd->delimiter, hd->tmp);
			break ;
		}
		if (!(hd->line) || (ft_str_equal(hd->delimiter, hd->line)))
		{
			loop_exit(hd->line, hd->tmp);
			break ;
		}
		if (ft_strchr(hd->str, '\"') || ft_strchr(hd->str, '\''))
			hd->tmp = ft_strdup(hd->line);
		else
			hd->tmp = expand(data, hd->line, 0);
		write(fd_pipe[1], hd->tmp, ft_strlen(hd->tmp));
		write(fd_pipe[1], "\n", 1);
		free(hd->line);
		hd->line = NULL;
		free(hd->tmp);
		hd->tmp = NULL;
	}
}

void	make_heredoc(char *str, t_minishell *data, int *fdpipe, t_list **lst)
{
	t_here_doc_str	hd;

	hd.delimiter = remove_quotes(str);
	hd.tmp = NULL;
	hd.line = NULL;
	hd.str = ft_strdup(str);
	here_doc_loop(&hd, data, fdpipe);
	free(hd.str);
	free_redir_lst(lst);
	free(hd.delimiter);
	free_minishell(data);
	if (close (fdpipe[0]) == -1)
		return (perror("close"));
	if (close(fdpipe[1]) == -1)
		return (perror("close"));
	close_stds(data);
	exit(g_exit_status);
}

int	heredoc_manage(char *str, t_minishell *data, t_list **redir_lst)
{
	int		fd_pipe[2];
	pid_t	pid;

	dup_stds(data);
	if (pipe(fd_pipe) < 0)
		return (perror("pipe"), 1);
	pid = fork();
	if (pid < 0)
		return (perror("fork"), EXIT_FAILURE);
	if (!pid)
	{
		set_signal_action(2);
		make_heredoc(str, data, fd_pipe, redir_lst);
	}
	else
		waitpid(pid, NULL, 0);
	if (close(fd_pipe[1]) == -1)
		return (perror("close"), EXIT_FAILURE);
	restore_stds(data);
	return (fd_pipe[0]);
}
