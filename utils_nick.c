#include "lem_in.h"

t_hash		**make_arr_nodes(t_graph *graph)
{
	size_t	index_table;
	size_t	index_arr;
	t_hash	*node;
	t_hash	**table;
	t_hash	**arr;

	MFAIL((arr = (t_hash **)malloc(sizeof(t_hash *) * nodes_num)));
	table = graph->h_table;
	index_table = 0;
	index_arr = 0;
	while (index_table < TABLE_SIZE)
	{
		if (table[index_table])
		{
			node = table[index_table];
			while (node)
			{
				arr[index_arr] = node;
				node->num_node = index_arr;
				if (node == graph->start)
					graph->num_start_node = index_arr;
				if (node == graph->end)
					graph->num_end_node = index_arr;
				node = node->next;
				++index_arr;
			}
		}
		index_table++;
	}
	return (arr);
}

t_paths		*create_paths(t_path *path, size_t len_path)
{
	t_paths *new_paths;

	MFAIL((new_paths = (t_paths *)malloc(sizeof(t_paths))));
	new_paths->path = path;
	new_paths->next = NULL;
	new_paths->begin_print = NULL;
	new_paths->current_print = NULL;
	new_paths->end_print = NULL;
	new_paths->num_nodes = len_path;
	return (new_paths);
}

void		add_path(t_graph *graph, t_path *new_path, size_t len_path)
{
	t_paths	*path;
	t_paths	*temp;

	if (graph == NULL)
		return ;
	path = graph->begin_path;
//	path = graph->end_path;
	temp = create_paths(new_path, len_path);
	if (path != NULL)
	{
		if (path->num_nodes > len_path)
		{
			temp->next = path;
			graph->begin_path = temp;
		}
		else
		{
			while (path->next != NULL && path->next->num_nodes <= len_path)
				path = path->next;
			temp->next = path->next;
			path->next = temp;
		}
//		path->next = create_paths(new_path, len_path);
//		graph->end_path = path->next;
	}
	else
	{
		graph->begin_path = temp;
//		graph->begin_path = create_paths(new_path, len_path);
		graph->end_path = graph->begin_path;
	}
	graph->num_paths += 1;
}

void		add_path_second(t_graph *graph, t_path *new_path, size_t len_path)
{
	t_paths	*path;
	t_paths	*temp;

	if (graph == NULL)
		return ;
	path = graph->begin_path_second_res;
	temp = create_paths(new_path, len_path);
	if (path != NULL)
	{
		if (path->num_nodes > len_path)
		{
			temp->next = path;
			graph->begin_path_second_res = temp;
		}
		else
		{
			while (path->next != NULL && path->next->num_nodes <= len_path)
				path = path->next;
			temp->next = path->next;
			path->next = temp;
			if (path->next == NULL)
				graph->end_path_second_res = temp;
		}
//		path->next = create_paths(new_path, len_path);
//		graph->end_path = path->next;
	}
	else
	{
		graph->begin_path_second_res = temp;
//		graph->begin_path = create_paths(new_path, len_path);
		graph->end_path_second_res = graph->begin_path_second_res;
	}
	graph->num_paths_second_res += 1;
}

//void		add_path_second(t_graph *graph, t_path *new_path, size_t len_path)
//{
//	t_paths	*path;
//
//	if (graph == NULL)
//		return ;
//	path = graph->end_path_second_res;
//	if (path != NULL)
//	{
//		path->next = create_paths(new_path, len_path);
//		graph->end_path_second_res = path->next;
//	}
//	else
//	{
//		graph->begin_path_second_res = create_paths(new_path, len_path);
//		graph->end_path_second_res = graph->begin_path_second_res;
//	}
//	graph->num_paths_second_res += 1;
//}
