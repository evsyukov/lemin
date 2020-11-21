#include "lem_in.h"

void	init_paths(t_paths *paths, int32_t speed)
{
	while (paths != NULL)
	{
		paths->begin_print = paths->path;
		paths->end_print = paths->path;
		paths->num_allowed_ants = speed + 1 - paths->num_nodes;
//		paths->current_print = paths->path;
		paths = paths->next;
	}
}

void	move_and_add_one(t_graph *graph, t_paths *paths,
					size_t *count_ants, size_t *sum_ants) {
	t_path *begin_path;
	t_path *path;

	path = paths->begin_print;
	begin_path = paths->path;
	while (path != paths->end_print) {
		// если текущая нода - последняя в пути
		// то уменьшаем сумму муравьев на всех путях
		if (path->next == NULL)
			*sum_ants -= 1;
		else
			path->next->num_ant = path->num_ant;
		path = path->prev;
	}
	// если есть муравьи на старте
	// то выделяем муравья(номер) и увеливаем счетчик номеров
	if (path == begin_path)
	{
		if (paths->num_allowed_ants != 0 && *count_ants <= graph->ants_num)
		{
			path->next->num_ant = *count_ants;
			*count_ants += 1;
			*sum_ants += 1;
			paths->num_allowed_ants -= 1;
		}
			// иначе (если нет муравьев на старте)
			// двигаем удказатель end_print вперед
		else
		{
			paths->end_print = paths->end_print->next;
		}
	}
	else if (paths->end_print != paths->begin_print)
			paths->end_print = paths->end_print->next;
	// для перевода begin_print на новое место
	// если не последний элемент, то двигаем вперед
	if (paths->begin_print->next != NULL)
		paths->begin_print = paths->begin_print->next;
}

void	move_and_add_all(t_graph *graph, t_paths *paths,
					size_t *count_ants, size_t *sum_ants)
{
	t_paths	*path;

	path = paths;
	// перебираем все пути
	while (path != NULL)
	{
		move_and_add_one(graph, path, count_ants, sum_ants);
		path = path->next;
	}
}

void	print_ant_at_room(t_path *path)
{
	ft_putstr("L");
	ft_putnbr(path->num_ant);
	ft_putstr("-");
	ft_putstr(path->node_name);
}

//void 	print_one_from_path(t_paths *paths)
//{
//	print_ant_at_room(paths->current_print);
//	paths->current_print = paths->current_print->prev;
//}
//
//void	print_state_my_way(t_paths *paths, size_t sum_ants)
//{
//	size_t	count_ants;
//	t_paths	*path;
//
//	count_ants = 0;
//	while (count_ants < sum_ants)
//	{
//		path = paths;
//		while (path != NULL)
//		{
//			if (path->current_print != path->end_print)
//			{
//				// if (!count_ants)
//				print_one_from_path(path);
//				ft_putstr(" ");
//				++count_ants;
//			}
//			path = path->next;
//		}
//	}
//}

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
		// двигаем вперед в каждом пути печатные указатели
		// выделяем муравья, если они есть.
//		move_and_add_all(graph, paths, &count_ants, &sum_ants_at_paths);
		// печатаем по одному муравью с каждого пути по элементно
		move_and_add_all(graph, paths, &count_ants, &sum_ants_at_paths);

		// мой вариант, как я неправильно понял сабджект
//		if (sum_ants_at_paths)
//			print_state_my_way(paths, sum_ants_at_paths);

		// как правильно надо печатать по сабджекту
		if (sum_ants_at_paths)
		{
			print_state(paths);
			ft_putstr("\n");
		}
	}
}
