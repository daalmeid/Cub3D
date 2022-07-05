/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daalmeid <daalmeid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/25 15:32:39 by daalmeid          #+#    #+#             */
/*   Updated: 2021/11/03 14:49:06 by daalmeid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void*))
{
	t_list	*lst_to_clear;

	if (lst == NULL || del == NULL)
		return ;
	while (lst != NULL && *lst != NULL)
	{
		lst_to_clear = (*lst)->next;
		ft_lstdelone(*lst, del);
		*lst = lst_to_clear;
	}
	*lst = NULL;
}
