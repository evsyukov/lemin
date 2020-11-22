/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_result.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smanta <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/22 18:53:23 by smanta            #+#    #+#             */
/*   Updated: 2020/11/22 18:53:26 by smanta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void	init_paths(t_paths *paths, int32_t speed)
{
	while (paths != NULL)
	{
		paths->begin_print = paths->path;
		paths->end_print = paths->path;
		paths->num_allowed_ants = speed + 1 - paths->num_nodes;
		paths = paths->next;
	}
}

void	print_ant_at_room(t_path *path)
{
	ft_putstr("L");
	ft_putnbr(path->num_ant);
	ft_putstr("-");
	ft_putstr(path->node_name);
}

size_t	print_all_from_one_path(t_paths *paths)
{
	t_path	*path;
	size_t	result;
	size_t	flag;

	path = paths->begin_print;
	flag = 0;
	result = 0;
	while (path != paths->end_print)
	{
		if (flag == 1)
			ft_putstr(" ");
		print_ant_at_room(path);
		flag = 1;
		result = 1;
		path = path->prev;
	}
	return (result);
}

void	print_state(t_paths *paths)
{
	t_paths	*path;
	size_t	flag;

	path = paths;
	flag = 0;
	while (path != NULL)
	{
		if (flag == 1)
			ft_putstr(" ");
		flag = print_all_from_one_path(path);
		path = path->next;
	}
}

void	print_solution(t_graph *graph)
{
	t_paths	*paths;
	size_t	count_ants;
	size_t	sum_ants_at_paths;

	count_ants = 1;
	sum_ants_at_paths = 0;
	paths = graph->begin_path_first_res;
	init_paths(paths, graph->speed);
	while (count_ants <= graph->ants_num || sum_ants_at_paths > 0)
	{
		move_ants(graph, paths, &count_ants, &sum_ants_at_paths);
		if (sum_ants_at_paths)
		{
			print_state(paths);
			ft_putstr("\n");
		}
	}
}
