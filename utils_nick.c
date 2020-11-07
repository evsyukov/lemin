#include "lem_in.h"

t_hash		**make_arr_nodes(t_graph *graph)
{
    size_t	index_table;
    size_t  index_arr;
	t_hash	*node;
    t_hash  **table;
    t_hash  **arr;
    char    *str;

	MFAIL((arr = (t_hash **)malloc(sizeof(t_hash *) * nodes_num)));
//	if ((arr = (t_hash **)malloc(sizeof(t_hash *) * nodes_num)) == NULL)
//		return NULL;
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

//                ft_putstr("index arr = ");
//                ft_putnbr(index_arr);
//                ft_putstr(", node_name = ");
//                str = arr[index_arr]->node_name;
//                ft_putstr(str);
//                ft_putstr("\n");

				node = node->next;
                ++index_arr;
			}
		}
		index_table++;
	}
  	return (arr);
}

void		print_graph_arr(t_hash **arr)
{
  t_hash	*node;
  int		i;
  char		*str;

  i = 0;
  while (i < nodes_num) {
    node = arr[i];
    ft_putstr("index arr = ");
    ft_putnbr(i);
    ft_putstr(", node_name = ");
    str = node->node_name;
    ft_putstr(str);
    ft_putstr("\n");
    ++i;
  }
}

void		print_path(t_path *path)
{
    while (path != NULL)
    {
        ft_putstr("node_name = ");
        ft_putstr(path->node->node_name);
        ft_putstr(" -> ");
        path = path->next;
    }
}

void	print_paths(t_graph *graph)
{
	t_paths	*paths;

	paths = graph->begin_path;
	if (paths == NULL)
		return;
	while (paths != NULL)
	{
		print_path(paths->path);
		paths = paths->next;
	}
}

t_paths	*create_paths(t_path *path)
{
	t_paths *new_paths;

	MFAIL((new_paths = (t_paths *)malloc(sizeof(t_paths))));
	new_paths->path = path;
	new_paths->next = NULL;
	return (new_paths);
}

void 	add_path(t_graph *graph, t_path *new_path)
{
	t_paths	*end_path;

	if (graph == NULL)
		return;
	end_path = graph->end_path;
	if (end_path != NULL)
	{
		end_path->next = create_paths(new_path);
		graph->end_path = end_path->next;
	}
	else
	{
		graph->begin_path = create_paths(new_path);
		graph->end_path = graph->begin_path;
	}
	graph->num_paths += 1;
}
