/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_arr_nodes.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smanta <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/22 19:52:25 by smanta            #+#    #+#             */
/*   Updated: 2020/11/22 19:52:27 by smanta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static size_t	add_to_arr(t_graph *graph,
							t_hash *node, t_hash **arr, size_t index)
{
	while (node)
	{
		arr[index] = node;
		node->num_node = index;
		if (node == graph->start)
			graph->num_start_node = index;
		if (node == graph->end)
			graph->num_end_node = index;
		node = node->next;
		++index;
	}
	return (index);
}

t_hash			**make_arr_nodes(t_graph *graph)
{
	size_t	index_table;
	size_t	index_arr;
	t_hash	*node;
	t_hash	**table;
	t_hash	**arr;

	if ((arr = (t_hash **)malloc(sizeof(t_hash *) * graph->nodes_num)) == NULL)
		err_exit();
	table = graph->h_table;
	index_table = 0;
	index_arr = 0;
	while (index_table < TABLE_SIZE)
	{
		if (table[index_table])
		{
			node = table[index_table];
			index_arr = add_to_arr(graph, node, arr, index_arr);
		}
		index_table++;
	}
	return (arr);
}
