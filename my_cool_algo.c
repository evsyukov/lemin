#include "lem_in.h"

//static	t_child	* (t_hash *node)
//{
//	t_child	*child;
//
//	child = node->child;
//	while (child != NULL)
//	{
//		if (child->c_node->node_name == node->node_name)
//			return child;
//		child = child->next;
//	}
//	return NULL;
//}
//

//static t_paths	*get_set_paths(t_graphs *graphs_all)
//{
//	t_path	*new_path;
//
//	new_path = get_bellman_ford_path(graph);
//	add_path(graph, new_path);
//	disable_forward_edges(graph, new_path);
//	// DEBUG
//	print_paths(graph);
//
//}

void	print_solution(t_graph *graph)
{

}

void			my_cool_func(t_graph *graph)
{
	t_path	*new_path;
	t_path	*new_path_2;
	size_t	len_path;
	size_t	speed;

	print_hash_table_child(graph->h_table);
	graph->arr_nodes = make_arr_nodes(graph);

	// DEBUG
	print_graph_arr(graph->arr_nodes);

	// STEP 1
	new_path = get_bellman_ford_path(graph, &len_path);
	add_path(graph, new_path, len_path);
//	print_paths(graph);

	get_result_paths(graph);
	speed = calc_speed(graph);
	print_paths(graph->begin_path);

	// STEP 2
	reverse_edges(graph, new_path);
	// DEBUG
	print_hash_table_child(graph->h_table);

	new_path_2 = get_bellman_ford_path(graph, &len_path);
	add_path(graph, new_path_2, len_path);
//	print_path(new_path_2);


	print_paths(graph->begin_path);

//	paths = get_set_paths(graph);
	print_solution(graph);
}
