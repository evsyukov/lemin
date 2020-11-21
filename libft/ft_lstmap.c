/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmustach <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/22 20:49:55 by nmustach          #+#    #+#             */
/*   Updated: 2020/11/09 02:19:19 by nmustach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, t_list *(*f)(t_list *elem))
{
	t_list	*start;
	t_list	*current;

	if (lst == NULL)
		return (NULL);
	start = f(lst);
	current = start;
	while (lst->next)
	{
		lst = lst->next;
		current->next = f(lst);
		current = current->next;
	}
	return (start);
}
