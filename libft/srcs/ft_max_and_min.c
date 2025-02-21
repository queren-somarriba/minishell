/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_max_and_min.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qsomarri <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 13:52:09 by qsomarri          #+#    #+#             */
/*   Updated: 2024/11/04 13:54:14 by qsomarri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

long	ft_max(long a, long b)
{
	if (a >= b)
		return (a);
	else
		return (b);
}

long	ft_min(long a, long b)
{
	if (a <= b)
		return (a);
	else
		return (b);
}
