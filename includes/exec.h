/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qsomarri <qsomarri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/01 18:00:43 by qsomarri          #+#    #+#             */
/*   Updated: 2025/02/18 18:54:33 by qsomarri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXEC_H
# define EXEC_H

/*CHILD PROCESS*/
int		child_process(t_minishell *data, t_cmd *cmd, int *pipefd);

/*EXEC_CMD*/
int		x_cmd(char **argv, char **envp, t_minishell *data);

/*PROCESSS*/
int		exec_cmd_lst(t_cmd *cdm, t_minishell *data);

int		x_pipe(t_minishell *data);

#endif