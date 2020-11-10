#include "lem_in.h"

void 	free_path(t_path *path)
{
	t_path	*temp_path;

	while (path != NULL)
	{
		temp_path = path;
		path = path->next;
		FCNT(free(temp_path));
	}
}

void	free_paths(t_paths *paths)
{
	t_paths	*temp_paths;

	while (paths != NULL)
	{
		temp_paths = paths;
		paths = paths->next;
		free_path(temp_paths->path);
		FCNT(free(temp_paths));
	}
}

static int	disable_edge(t_hash	*curr_hash, t_hash *next_hash)
{
	t_child	*child;
	char 	*str_1;
	char	*str_2;

	child = curr_hash->child;
	str_2 = next_hash->node_name;
	while (child != NULL)
	{
		str_1 = child->c_node->node_name;
//		if (ft_strequ(curr_hash->child->c_node->node_name, next_hash->node_name))
		if (ft_strequ(str_1, str_2))
		{
			child->flow = 0;
			child->is_part_of_path = 1;
			return (1);
		}
		child = child->next;
	}
	return (0);
}

void reverse_edges(t_graph *graph, t_path *path)
{
	t_path	*next;
	t_hash	*curr_hash;
	t_hash	*next_hash;

	while (path->node != graph->end)
	{
		curr_hash = path->node;
		next = path->next;
		next_hash = next->node;
		if (!disable_edge(curr_hash, next_hash))
		{
			// DEBUG
			ft_putstr("Удаление ребра из прямого пути БФ. Что то пошло не так оО\n");
			err_exit();
		}
		if (check_nodenames_is_family(curr_hash->node_name, next_hash->node_name))
			add_link(next_hash, curr_hash, 0, 0);
		else
			add_link(next_hash, curr_hash, -1, 0);
		path = next;
	}
}

static void	resolve_conflicts(t_graph *graph)
{
		(void)(graph);
}

void		get_result_paths(t_graph *graph)
{
	t_paths	*paths;
	t_hash	*node;

	(void)(paths);
	(void)(node);

	resolve_conflicts(graph);

}
