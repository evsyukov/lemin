#include "lem_in.h"

//static void		init_node_by_node(t_hash *new_node, t_hash *node)
//{
//	new_node->node_name = ft_strdup(node->node_name);
//	new_node->x = node->x;
//	new_node->y = node->y;
//
//
//	if (node->child)
//	{
//		child_list = node->child;
//		while (child_list)
//		{
//
//			child_list = child_list->next;
//		}
//	}
//}

//static t_hash	**get_copy_h_table(t_hash **h_table)
//{
//	t_hash	**new_h_table;
//	t_hash	*new_node;
//	size_t	i;
//	t_hash	*node;
//	t_hash	*prev_node;
//
//    MFAIL((new_h_table = (t_hash **)malloc(sizeof(t_hash *) * TABLE_SIZE)));
//	i = 0;
//	while (i < TABLE_SIZE)
//	{
//		if (h_table[i])
//		{
//			node = h_table[i];
//			MFAIL((new_node = (t_hash *)malloc(sizeof(t_hash))));
//			init_node_by_node(new_node, node);
//			new_h_table[i] = new_node;
//			node = node->next;
//			prev_node = new_node;
//			while (node)
//			{
//				MFAIL((new_node = (t_hash *)malloc(sizeof(t_hash))));
//				init_node_by_node(new_node, node);
//				prev_node->next = new_node;
//				new_node->prev = prev_node;
//				prev_node =new_node;
//				node = node->next;
//			}
//		}
//		i++;
//	}
//}
//
//static void		copy_paths(t_graph *new_graph, t_graph *graph)
//{
//
//}
//
//t_graph			*get_copy_graph(t_graph *graph)
//{
//	t_graph	*new_graph;
//
//	MFAIL((new_graph = (t_graph *)malloc(sizeof(t_graph))));
//	new_graph->h_table = get_copy_h_table(graph->h_table);
//	new_graph->start = graph->start;
//	new_graph->end = graph->end;
//	new_graph->ants_num = graph->ants_num;
//	new_graph->map_buf = NULL; // в копии эти данные не нужны уже
//	new_graph->paths_list = NULL; // в копии эти данные не нужны уже
//	new_graph->arr_nodes = make_arr_nodes(new_graph);
//	new_graph->num_start_node = graph->num_start_node;
//	new_graph->num_end_node = graph->num_end_node;
//	new_graph->num_paths = graph->num_paths;
//	copy_paths(new_graph, graph);
//}
