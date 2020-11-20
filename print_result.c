#include "lem_in.h"

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
		// если текущая нода первая

		if (path->node == begin_path->node)
		{
			// и есть муравьи на старте
			// то выделяем муравья и увеливаем счетчик номера муравья
			if (*count_ants <= graph->ants_num)
			{
				path_next->num_ant = *count_ants;
				*count_ants += 1;
				*sum_ants += 1;
			}
			// иначе (если нет муравьев на старте)
			// двигаем удказатель end_print вперед
			else if (paths->end_print != NULL)
				paths->end_print = paths->end_print->next;
		}
		// иначе, если текущая нода - последняя
		// то уменьшаем сумму муравьев на всех путях
		else if (path_next == NULL)
			*sum_ants -= 1;
		else
			path_next->num_ant = path->num_ant;
		path = path->prev;
	}
	// для перевода begin_print на новое место
	// если не последний элемент, то двигаем вперед
	if (paths->begin_print->next != NULL)
		paths->begin_print = paths->begin_print->next;
	// переназначение current на begin
	paths->current_print = paths->begin_print;
}

void	move_and_add_all(t_graph *graph, t_paths *paths,
					size_t *count_ants, size_t *sum_ants)
{
	t_paths	*paths_one;

	paths_one = paths;
	// перебираем все пути
	while (paths_one != NULL)
	{
		move_and_add_one(graph, paths_one, count_ants, sum_ants);
		paths_one = paths_one->next;
	}
}

void	print_ant_at_room(t_path *path)
{
	ft_putstr("L");
	ft_putnbr(path->num_ant);
	ft_putstr("-");
	ft_putstr(path->node_name);
}

void 	print_one_from_path(t_paths *paths)
{
	print_ant_at_room(paths->current_print);
	paths->current_print = paths->current_print->prev;
}

void	print_state(t_paths *paths, size_t sum_ants)
{
	size_t	count_ants;
	t_paths	*path;

	count_ants = 0;
	while (count_ants < sum_ants)
	{
		path = paths;
		while (path != NULL)
		{
			if (path->current_print != path->end_print)
			{
				// if (!count_ants)
				print_one_from_path(path);
				ft_putstr(" ");
				++count_ants;
			}
			path = path->next;
		}
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
		// двигаем вперед в каждом пути печатные указатели
		// выделяем муравья, если они есть.
		move_and_add_all(graph, paths, &count_ants, &sum_ants_at_paths);
		// печатаем по одному муравью с каждого пути по элементно
		print_state(paths, sum_ants_at_paths);
		ft_putstr("\n");
	}
}
