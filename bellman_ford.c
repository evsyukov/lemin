/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bellman_ford.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smanta <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/22 17:49:14 by smanta            #+#    #+#             */
/*   Updated: 2020/11/22 17:49:21 by smanta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static void		init_d_by_value(int *d, size_t len, int value)
{
	size_t	i;

	i = 0;
	while (i < len)
		d[i++] = value;
}

static t_path	*get_path(t_graph *graph, const int *d, const int *p)
{
	t_path	*path;
	int		t;

	path = NULL;
	if (d[graph->num_end_node] == 2000000000)
		return (NULL);
	else
	{
		t = graph->num_end_node;
		while (t != -1)
		{
			if (add_path_node(&path, (graph->arr_nodes)[t]) == NULL)
				err_exit();
			t = p[t];
		}
	}
	return (path);
}

static void		some_func(t_graph *graph,
					size_t i, int *d, int *p)
{
	t_child	*child_ptr;
	t_hash	*node;
	int		value;

	node = graph->arr_nodes[i];
	child_ptr = node->child;
	while (child_ptr != NULL)
	{
		value = child_ptr->c_node->num_node;
		if (child_ptr->flow == 1 && d[value] > d[i] + child_ptr->weight)
		{
			d[value] = d[i] + child_ptr->weight;
			p[value] = (int)i;
			graph->any_bf = 1;
		}
		child_ptr = child_ptr->next;
	}
}

t_path			*get_bellman_ford_path(t_graph *graph)
{
	int		d[graph->nodes_num];
	int		p[graph->nodes_num];
	size_t	i;

	init_d_by_value(d, graph->nodes_num, 2000000000);
	init_d_by_value(p, graph->nodes_num, -1);
	d[graph->num_start_node] = 0;
	graph->any_bf = 1;
	while (graph->any_bf == 1)
	{
		graph->any_bf = 0;
		i = 0;
		while (i < graph->nodes_num)
		{
			some_func(graph, i, d, p);
			++i;
		}
	}
	return (get_path(graph, d, p));
}

int				is_one_path_exist(t_graph *graph)
{
	t_path	*path;
	int		result;

	result = 1;
	path = get_bellman_ford_path(graph);
	if (path == NULL)
		result = 0;
	free_path(path);
	return (result);
}
