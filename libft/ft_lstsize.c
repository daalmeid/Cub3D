/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstsize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daalmeid <daalmeid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/25 14:11:33 by daalmeid          #+#    #+#             */
/*   Updated: 2021/10/29 12:46:37 by daalmeid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_lstsize(t_list *lst)
{
	int	i;	

	i = 1;
	if (!lst)
		return (0);
	while (lst->next != NULL)
	{	
		i++;
		lst = lst->next;
	}
	return (i);
}
