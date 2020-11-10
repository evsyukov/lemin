#include "lem_in.h"

static void		case_minus()
{

}

static size_t	do_calc_speed(int num, const size_t *arr, size_t len)
{
	size_t	result;
	size_t	index;
	size_t	area;

	result = 0;
	index = 0;
	while (num > 0)
	{
		while (index < len - 1 && arr[index] == arr[index + 1])
			++index;
		area = (index + 1);
		num -= area;
	}
	if (num < 0)
		case_minus();
	return (result);
}

static void		li_swap(size_t *a, size_t *b)
{
	size_t temp;

	temp = *a;
	*a = *b;
	*b = temp;
}

static void		li_sort(size_t *arr, size_t len)
{
	size_t	count;
	size_t	index;

	if (len <= 1)
		return;
	count = 0;
	while (count < len)
	{
		index = 0;
		while (index < len - 1)
		{
			if (arr[index] > arr[index + 1])
				li_swap(&(arr[index]), &(arr[index + 1]));
			++index;
		}
		++count;
	}
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
	li_sort(path_lens, num_paths);
	result = do_calc_speed(graph->ants_num, path_lens, num_paths);
	FCNT((free(path_lens)));
    return (result);
}
