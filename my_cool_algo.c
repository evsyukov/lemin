#include "lem_in.h"

//static t_child	*find_child_by_hash(t_hash *node, t_hash *find_node)
//{
//	t_child	*child;
//
//	child = node->child;
//	while (child != NULL)
//	{
//		if (child->c_node->node_name == find_node->node_name)
//			return (child);
//		child = child->next;
//	}
//	return (NULL);
//}

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

static size_t	get_num_childs_start(t_graph *graph)
{
	return (get_len_child(graph->start->child));
}

static size_t	get_num_childs_end(t_graph *graph)
{
	size_t	len;
	char	*str_in;
	char	*str_out;
	t_hash	*hash;

	str_in = ft_strdup(graph->end->node_name);
	str_in[ft_strlen(str_in) - 3] = '\0';
	str_out = ft_strjoin(str_in, "_out");
	hash = hash_query(graph->h_table, str_out);
	len = get_len_child(hash->child);
	str_in[ft_strlen(str_in) - 3] = '_';
	free(str_in);
	free(str_out);
	return (len);
}

static size_t	get_limits(t_graph *graph)
{
	size_t	result;

	graph->num_childs_start = get_num_childs_start(graph);
	graph->num_childs_end = get_num_childs_end(graph);
	result = graph->num_childs_start <= graph->num_childs_end ?
			 graph->num_childs_start : graph->num_childs_end;
	result = result < graph->ants_num ? result : graph->ants_num;
	return (result);
}

void	print_solution(t_graph *graph)
{
	(void)(graph);
}

void	real_func(t_graph *graph)
{
	size_t	speed_current;
	size_t	speed_next;
	size_t	limits;

	limits = get_limits(graph);
	speed_next = (size_t)INT_MAX;
	speed_current = speed_next;
	while (speed_next > 0 && speed_next <= speed_current && limits-- > 0)
	{
		speed_current = speed_next;
		graph->num_paths_first_res = 0; // очистка первого набора путей
		free_paths(graph->begin_path_first_res); // очистка (+ free) первого набора путей
		graph->end_path_first_res = NULL; // очистка первого набора путей

		graph->num_paths_first_res = graph->num_paths_second_res; // копирование из второго набора в первый
		graph->begin_path_first_res = graph->begin_path_second_res; // копирование (*) из второго набора в первый
		graph->end_path_first_res = graph->end_path_second_res; // копирование из второго набора в первый

		graph->num_paths_second_res = 0; // очистка второго набора путей
		graph->begin_path_second_res = NULL; // очистка второго набора путей
		graph->end_path_second_res = NULL; // очистка второго набора путей

		speed_next = get_set_paths(graph);
		print_paths(graph->begin_path_second_res);
		ft_putstr("\n");
	}
	graph->speed = speed_current;
}

void	my_cool_func(t_graph *graph)
{
	t_path	*new_path;
	t_path	*new_path_2;
	size_t	len_path;
	size_t	speed;

	graph->arr_nodes = make_arr_nodes(graph);

	// DEBUG ПЕЧАТЬ ИЗНАЧАЛЬНОГО ГРАФА
//	print_hash_table_child(graph->h_table);
//	print_graph_arr(graph->arr_nodes);

	// STEP 1
	new_path = get_bellman_ford_path(graph, &len_path);
	add_path(graph, new_path, len_path);
//	print_paths(graph);

//	get_result_paths(graph);
//	speed = calc_speed(graph);
//	print_paths(graph->begin_path);

	// DEBUG Делаем Reverse по первому пути
	reverse_edges(graph, new_path);

	// STEP 2

	// DEBUG ПЕЧАТЬ ГРАФА после первого реверса
//	print_hash_table_child(graph->h_table);

	new_path_2 = get_bellman_ford_path(graph, &len_path);
//	add_path(graph, new_path_2, len_path);
//	print_path(new_path_2);

//	print_paths(graph->begin_path);

	// DEBUG Делаем Reverse по второму пути
//	reverse_edges(graph, new_path_2);

	// DEBUG ПЕЧАТЬ ГРАФА после второго реверса
//	print_hash_table_child(graph->h_table);

	speed = get_set_paths(graph);
	// DEBUG распечатать скорость прохода
	ft_putstr("Speed = ");
	ft_putnbr(speed);
	ft_putstr("\n");
	ft_putstr("Новый набор путей : \n");
	print_paths(graph->begin_path_second_res);

	print_solution(graph);
}
