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
