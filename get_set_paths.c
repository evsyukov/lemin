/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_set_paths.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smanta <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/22 20:15:48 by smanta            #+#    #+#             */
/*   Updated: 2020/11/22 20:15:58 by smanta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static t_path	*get_result_path(t_graph *graph, t_hash *node, size_t *len_path)
{
	t_path	*path;
	t_child	*child;

	path = NULL;
	add_path_node(&path, graph->start);
	add_path_node(&path, node);
	*len_path = 1;
	if (node == graph->end)
		return (path);
	while (node != graph->end)
	{
		child = node->child;
		while (child != NULL)
		{
			if (child->is_part_of_path == 1)
				break ;
			child = child->next;
		}
		add_path_node(&path, child->c_node);
		node = child->c_node;
		*len_path += 1;
	}
	return (path);
}

static void		reverse_path(t_path **apath)
{
	t_path	*new_rev;
	t_path	*begin_current;
	t_path	*next_current;

	if (apath == NULL || *apath == NULL)
		return ;
	new_rev = NULL;
	begin_current = *apath;
	while (begin_current != NULL)
	{
		next_current = begin_current->next;
		begin_current->next = new_rev;
		if (new_rev != NULL)
			new_rev->prev = begin_current;
		new_rev = begin_current;
		begin_current = next_current;
	}
	new_rev->prev = NULL;
	*apath = new_rev;
}

static void		do_main_get_set_paths(t_graph *graph)
{
	t_child *child;
	t_path	*path;
	size_t	len_path;

	len_path = 0;
	child = graph->start->child;
	while (child != NULL)
	{
		if (child->is_part_of_path == 1)
		{
			path = get_result_path(graph, child->c_node, &len_path);
			reverse_path(&path);
			add_path_second(graph, path, len_path);
		}
		child = child->next;
	}
}

size_t			get_set_paths(t_graph *graph)
{
	t_path	*new_path;
	size_t	speed;

	new_path = get_bellman_ford_path(graph);
	if (new_path == NULL)
		return (0);
	reverse_edges(graph, new_path);
	free_path(new_path);
	do_main_get_set_paths(graph);
	get_normal_paths(graph);
	speed = calc_speed(graph);
	return (speed);
}
