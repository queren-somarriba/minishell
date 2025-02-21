/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_lst.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qsomarri <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/21 18:28:58 by qsomarri          #+#    #+#             */
/*   Updated: 2024/11/21 18:29:44 by qsomarri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_free_lst(t_list **lst)
{
	t_list	*tmp;

	tmp = NULL;
	if (lst)
	{
		if (*lst)
		{
			while (*lst)
			{
				tmp = *lst;
				*lst = (*lst)->next;
				free(tmp);
			}
		}
		free(lst);
	}
}
