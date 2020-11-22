/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_ants.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smanta <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/22 19:02:09 by smanta            #+#    #+#             */
/*   Updated: 2020/11/22 19:02:17 by smanta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static void	move_and_add_one(t_graph *graph, t_paths *paths,
						size_t *count_ants, size_t *sum_ants)
{
	t_path *path;

	path = paths->begin_print;
	while (path != paths->end_print)
	{
		if (path->next == NULL)
			*sum_ants -= 1;
		else
			path->next->num_ant = path->num_ant;
		path = path->prev;
	}
	if (path == paths->path)
		if (paths->num_allowed_ants != 0 && *count_ants <= graph->ants_num)
		{
			path->next->num_ant = (*count_ants)++;
			*sum_ants += 1;
			paths->num_allowed_ants -= 1;
		}
		else
			paths->end_print = paths->end_print->next;
	else if (paths->end_print != paths->begin_print)
		paths->end_print = paths->end_print->next;
	if (paths->begin_print->next != NULL)
		paths->begin_print = paths->begin_print->next;
}

void		move_ants(t_graph *graph, t_paths *paths,
						size_t *count_ants, size_t *sum_ants)
{
	t_paths	*path;

	path = paths;
	while (path != NULL)
	{
		move_and_add_one(graph, path, count_ants, sum_ants);
		path = path->next;
	}
}
