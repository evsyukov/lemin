/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_solution.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smanta <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/21 22:07:09 by smanta            #+#    #+#             */
/*   Updated: 2020/11/21 22:07:15 by smanta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static size_t	get_len_child(t_child *child)
{
	size_t	len;

	len = 0;
	while (child != NULL)
	{
		++len;
		child = child->next;
	}
	return (len);
}

static size_t	get_num_childs_end(t_graph *graph)
{
	size_t	len_child;
	size_t	len;
	char	*str_in;
	char	*str_out;
	t_hash	*hash;

	MFAIL((str_in = ft_strdup(graph->end->node_name)));
	len = ft_strlen(str_in);
	str_in[len - 3] = '\0';
	MFAIL((str_out = ft_strjoin(str_in, "_out")));
	hash = hash_query(graph->h_table, str_out);
	len_child = get_len_child(hash->child);
	str_in[len - 3] = '_';
	FCNT((free(str_in)));
	FCNT((free(str_out)));
	return (len_child);
}

static size_t	get_limits(t_graph *graph)
{
	size_t	result;

	graph->num_childs_start = get_len_child(graph->start->child);
	graph->num_childs_end = get_num_childs_end(graph);
	result = graph->num_childs_start <= graph->num_childs_end ?
			graph->num_childs_start : graph->num_childs_end;
	result = result < graph->ants_num ? result : graph->ants_num;
	return (result);
}

static void		move_from_second_to_first(t_graph *graph)
{
	free_paths(graph->begin_path_first_res);
	graph->begin_path_first_res = graph->begin_path_second_res;
	graph->num_paths_second_res = 0;
	graph->begin_path_second_res = NULL;
}

void			find_solution(t_graph *graph)
{
	size_t	speed_current;
	size_t	speed_next;
	size_t	limits;

	limits = get_limits(graph);
	speed_current = (size_t)INT_MAX;
	speed_next = speed_current - 1;
	while (speed_next > 0 && speed_next < speed_current && limits > 0)
	{
		--limits;
		speed_current = speed_next;
		move_from_second_to_first(graph);
		speed_next = get_set_paths(graph);
	}
	if (limits == 0 && speed_next > 0 && speed_next < speed_current)
	{
		speed_current = speed_next;
		move_from_second_to_first(graph);
	}
	graph->speed = speed_current;
}
