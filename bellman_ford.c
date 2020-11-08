#include "lem_in.h"

static void     init_d_by_value(int *d, int value)
{
    unsigned long i = 0;

    while (i < nodes_num)
        d[i++] = value;
}

static void     init_node_path(t_path *new_path, t_hash *node,
    t_path *next, t_path *prev)
{
    new_path->node = node;
	new_path->next = next;
	new_path->prev = prev;
	if (next != NULL)
		next->prev = new_path;
}

static t_path   *add_path_node(t_path **root, t_hash *node)
{
    t_path  *path;
    t_path  *new;

    path = *root;
    MFAIL((new = (t_path *)malloc(sizeof(t_path))));
    if (path == NULL)
        init_node_path(new, node, NULL, NULL);
    else
        init_node_path(new, node, path, NULL);
    *root = new;
    return (new);
}

t_path          *get_bellman_ford_path(t_graph *graph)
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
	t_path          *path;
	int             d[nodes_num];
	int             p[nodes_num];
	t_child         *child_ptr;
	unsigned long   k;
	int             value;
	unsigned long   i;
	int             t;

    path = NULL;
    init_d_by_value(d, 2000000000);
    init_d_by_value(p, -1);
    d[graph->num_start_node] = 0;

    t_hash *node;
    k = 1;
    while (k < nodes_num)
    {
		i = 0;
		while (i < nodes_num)
		{
          	node = graph->arr_nodes[i];
            child_ptr = node->child;
            while (child_ptr != NULL) {
                value = child_ptr->c_node->num_node;
                if (child_ptr->flow == 1 && d[i] > d[value] + child_ptr->weight)
                {
                    d[i] = d[value] + child_ptr->weight;
                    p[i] = value;
                }
                child_ptr = child_ptr->next;
            }
            ++i;
        }
         ++k;
    }
    if (d[graph->num_end_node] == 2000000000)
	{
    	// НЕТ пути вообще -> Выход
		write(1, "There is NO WAY between Start and End rooms\n", 44);
		err_exit();
	}
    else
    {
        t = graph->num_end_node;
        while (t != -1)
        {
            if (add_path_node(&path, (graph->arr_nodes)[t]) == NULL)
                err_exit();
            t = p[t];
        }
    }
    return (path);
}
