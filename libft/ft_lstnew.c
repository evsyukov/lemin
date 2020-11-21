/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmustach <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/20 16:12:10 by nmustach          #+#    #+#             */
/*   Updated: 2020/11/09 02:22:15 by nmustach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstnew(void const *content, size_t content_size)
{
	t_list *link;

	link = (t_list*)malloc(sizeof(t_list));
	if (link == NULL)
		return (NULL);
	if (content == NULL)
	{
		link->content = NULL;
		link->content_size = 0;
		link->next = NULL;
		return (link);
	}
	link->content = malloc(content_size);
	if (link->content == NULL)
	{
		free(link);
		return (NULL);
	}
	ft_memcpy(link->content, content, content_size);
	link->content_size = content_size;
	link->next = NULL;
	return (link);
}
