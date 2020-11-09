#include "lem_in.h"

static size_t	do_calc_speed(int ants_num,
							size_t	*path_lens, size_t num_nodes)
{
	size_t	result;

	result = 0;
	return (result);
}

static void		ft_sort(size_t *path_lens, size_t num_paths)
{

}

size_t			calc_speed(t_graph *graph)
{
	size_t	result;
	t_paths	*paths_to_calc;
	size_t	*path_lens;
	size_t	index;
	size_t	num_paths;

	index = 0;
	num_paths = graph->num_paths_second_res;
	paths_to_calc = graph->begin_path_second_res;
	MFAIL((path_lens = (size_t *)malloc(sizeof(size_t) * num_paths)));
	while (index < num_paths && paths_to_calc != NULL)
	{
		path_lens[index] = paths_to_calc->num_nodes;
		paths_to_calc = paths_to_calc->next;
		++index;
	}
	// !!! SORTING
	ft_sort(path_lens, num_paths);
	result = do_calc_speed(graph->ants_num, path_lens, num_paths);
	FCNT((free(path_lens)));
    return (result);
}
