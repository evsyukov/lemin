/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_hash.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmustach <nmustach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/21 18:22:41 by nmustach          #+#    #+#             */
/*   Updated: 2020/11/21 18:23:21 by nmustach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void			free_hash_table(t_hash **h_table)
{
	size_t	i;

	i = 0;
	while (i < TABLE_SIZE)
	{
		if (h_table[i])
			free_nodes(h_table[i]);
		i++;
	}
	free(h_table);
}

void			free_nodes(t_hash *node)
{
	t_child	*child_list;
	t_child	*child_next;
	t_hash	*next;

	while (node)
	{
		next = node->next;
		free(node->node_name);
		if (node->child)
		{
			child_list = node->child;
			while (child_list)
			{
				child_next = child_list->next;
				free(child_list);
				child_list = child_next;
			}
		}
		free(node);
		node = next;
	}
}
