#include "lem_in.h"

static void	init_d_by_value(int *d, int value)
{
	unsigned long i;

	i = 0;
	while (i < nodes_num)
		d[i++] = value;
}

t_path	*get_bellman_ford_path(t_graph *graph, size_t *len_path)
{
	/*
    INF = 10 ** 9
    F = [INF] * N
    F[start] = 0
    for k in range(1, N):
    for i in range(N):
    for j in range(N):
    if F[j] + W[j][i] < F[i]:
    F[i] = F[j] + W[j][i]
    */
	t_path			*path;
	int				d[nodes_num];
	int				p[nodes_num];
	t_child			*child_ptr;
//	unsigned long   k;
	int				value;
	unsigned long	i;
	int				t;
	size_t			any;

	path = NULL;
	init_d_by_value(d, 2000000000);
	init_d_by_value(p, -1);
	d[graph->num_start_node] = 0;

	t_hash *node;
//    k = 1;
//    while (k < nodes_num)
	while (1)
	{
		any = 0;
		i = 0;
		while (i < nodes_num)
		{
			node = graph->arr_nodes[i];
			child_ptr = node->child;
			while (child_ptr != NULL)
			{
				value = child_ptr->c_node->num_node;
				if (child_ptr->flow == 1 && d[value] > d[i] + child_ptr->weight)
				{
					d[value] = d[i] + child_ptr->weight;
					p[value] = i;
					any = 1;
				}
				child_ptr = child_ptr->next;
			}
			++i;
		}
		if (any == 0)
			break ;
//         ++k;
	}
	*len_path = 0;
	if (d[graph->num_end_node] == 2000000000)
	{
	// НЕТ пути вообще -> Выход
		write(1, "There is NO WAY between Start and End rooms\n", 44);
		return (NULL);
//		err_exit();
	}
	else
	{
		t = graph->num_end_node;
		while (t != -1)
		{
			if (add_path_node(&path, (graph->arr_nodes)[t]) == NULL)
				err_exit();
			t = p[t];
			*len_path += 1;
		}
	}
	*len_path /= 2;
//*len_path = d[graph->num_end_node];
	return (path);
}
