/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_path.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smanta <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/22 19:52:01 by smanta            #+#    #+#             */
/*   Updated: 2020/11/22 19:52:04 by smanta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

t_path			*add_path_node(t_path **root, t_hash *node)
{
	t_path	*path;
	t_path	*new_path;

	path = *root;
	MFAIL((new_path = (t_path *)malloc(sizeof(t_path))));
	new_path->node = node;
	new_path->node_name = NULL;
	new_path->next = path;
	new_path->prev = NULL;
	if (path != NULL)
		path->prev = new_path;
	*root = new_path;
	return (new_path);
}

t_paths			*create_paths(t_path *path, size_t len_path)
{
	t_paths *new_paths;

	MFAIL((new_paths = (t_paths *)malloc(sizeof(t_paths))));
	new_paths->path = path;
	new_paths->next = NULL;
	new_paths->begin_print = NULL;
	new_paths->end_print = NULL;
	new_paths->num_nodes = len_path;
	return (new_paths);
}

void			add_path_second(t_graph *graph,
					t_path *new_path, size_t len_path)
{
	t_paths	*path;
	t_paths	*new_paths;

	path = graph->begin_path_second_res;
	new_paths = create_paths(new_path, len_path);
	if (path != NULL)
	{
		if (path->num_nodes > len_path && (new_paths->next = path) == path)
			graph->begin_path_second_res = new_paths;
		else
		{
			while (path->next != NULL && path->next->num_nodes < len_path)
				path = path->next;
			new_paths->next = path->next;
			path->next = new_paths;
		}
	}
	else
		graph->begin_path_second_res = new_paths;
	graph->num_paths_second_res += 1;
}
