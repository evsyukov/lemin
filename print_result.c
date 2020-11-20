#include "lem_in.h"

void	print_ant_at_room(t_path *path)
{
	ft_putstr("L");
	ft_putnbr(path->num_ant);
	ft_putstr("-");
	ft_putstr(path->node_name);
}

void 	print_one_from_path(t_paths *paths)
{
//	t_path	*begin_print;
//	t_path	*next;
//	t_path	*prev;
//
//	begin_print = paths->begin_print;
//	if (begin_print->next != NULL)
//	{
//		print_ant_at_room(next);
//	}
//	else
//	{
//
//	}
}

void	init_paths(t_paths *paths)
{
	while (paths != NULL)
	{
		paths->begin_print = paths->path;
		paths->end_print = paths->path;
		paths->current_print = paths->path;
		paths = paths->next;
	}
}


void	move_and_add_one(t_graph *graph, t_paths *paths,
					size_t *count_ants, size_t *sum_ants)
{
	t_path	*path;
	t_path	*begin_path;
	t_path	*path_next;

	path = paths->begin_print;
	begin_path = paths->path;
	while (path != NULL)
	{
		path_next = path->next;
		if (path->node == begin_path->node
			&& *count_ants <= graph->ants_num)
		{
			path_next->num_ant = *count_ants;
			*count_ants += 1;
			*sum_ants += 1;
		}
		else if (path_next == NULL)
			*sum_ants -= 1;
		else
			path_next->num_ant = path->num_ant;
		path = path->prev;
	}
	if (paths->begin_print->next != NULL)
		paths->begin_print = paths->begin_print->next;
	paths->current_print = paths->begin_print;
}

void	move_and_add_all(t_graph *graph, t_paths *paths,
					size_t *count_ants, size_t *sum_ants)
{
	t_paths	*paths_one;

	paths_one = paths;
	while (paths_one != NULL)
	{
		move_and_add_one(graph, paths_one, count_ants, sum_ants);
		paths_one = paths_one->next;
	}
}

void	print_state(t_paths *paths)
{
	while (paths != NULL)
	{
		print_one_from_path(paths);
		paths = paths->next;
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
	init_paths(paths);
	while (count_ants <= graph->ants_num || sum_ants_at_paths > 0)
	{
		move_and_add_all(graph, paths, &count_ants, &sum_ants_at_paths);
		print_state(paths);
	}
}
