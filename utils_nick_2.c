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
		if (check_nodenames_is_family(curr_hash->node_name, next_hash->node_name))
			add_link_zero(next_hash, curr_hash, 0);
		else
			add_link_zero(next_hash, curr_hash, -1);
		path = next;
	}
}
