/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_front.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daalmeid <daalmeid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/25 14:00:00 by daalmeid          #+#    #+#             */
/*   Updated: 2021/10/29 15:18:57 by daalmeid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_front(t_list **lst, t_list *new)
{
	t_list	*lst_first;

	lst_first = *lst;
	if (lst == NULL)
		return ;
	if (new != NULL)
	{
		new->next = lst_first;
		*lst = new;
	}
}
