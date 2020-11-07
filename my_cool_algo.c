#include "lem_in.h"

//static	t_child	*find_child_node_by_hash(t_hash *node)
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
//static void		disable_forward_edges(t_graph *graph, t_path *new_path)
//{
//	t_path	*path;
//	t_hash	*node;
//	t_child	*child_node;
//
//	path = new_path;
//	if (path != NULL && path->node == graph->start)
//	{
//		if ((child_node = find_child_node_by_hash(path->node)) != NULL)
//		{
//			child_node->status = 1;
//			child_node->flow = 0;
//		}
//
//		path = path->next;
//	}
//	while (path != NULL && path->node != graph->end)
//	{
//		node = path->node;
//
//		path = path->next;
//	}
//}
//
//static t_paths	*get_set_paths(t_graphs *graphs_all)
//{
//	t_graph	*graph = graphs_all->graph;
//	t_graph	*curr_graph = graphs_all->curr_graph;
//	t_graph	*next_graph = graphs_all->next_graph;
//	t_path	*new_path;
//
//	new_path = get_bellman_ford_path(graph);
//	add_path(graph, new_path);
//	disable_forward_edges(graph, new_path);
//	// DEBUG
//	print_paths(graph);
//
//}
//
//static void		print_solution(t_graphs *graphs_all, t_paths *paths)
//{
//	t_graph	*curr_graph;
//
//	curr_graph = graphs_all->curr_graph;
//
//}
//
//void			my_cool_func(t_graphs *graphs_all)
//{
//	t_paths	*paths;
//
//	paths = get_set_paths(graphs_all);
//	print_solution(graphs_all, paths);
//}
