/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   outputs.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qsomarri <qsomarri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/01 15:34:00 by qsomarri          #+#    #+#             */
/*   Updated: 2025/02/14 18:48:15 by qsomarri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exit_status(int nbr)
{
	g_exit_status = nbr;
}

void	error_msg(char *str)
{
	if (!str)
		return ;
	return (ft_putstr_fd(str, 2), ft_putstr_fd("\n", 2));
}

void	error_msg2(char *str1, char *str2)
{
	if (!str1 || !str2)
		return ;
	return (ft_putstr_fd(str1, 2), ft_putstr_fd(str2, 2), ft_putstr_fd("\n", 2));
}
