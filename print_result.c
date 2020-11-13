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

void	move_and_add(t_paths *paths, size_t *count_ants, size_t	*sum_ants)
{
	
}

void	print_state(t_paths *paths)
{
//	while (paths != NULL)
//	{
//		print_one_from_path(paths);
//		paths = paths->next;
//	}
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
		move_and_add(paths, &count_ants, &sum_ants_at_paths);
		print_state(paths);
	}
}
