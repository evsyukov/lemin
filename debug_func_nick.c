#include "lem_in.h"

void		print_graph_arr(t_graph *graph)
{
	t_hash	*node;
	size_t	i;
	char	*str;

	i = 0;
	while (i < graph->nodes_num)
	{
		node = (graph->arr_nodes)[i];
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
		ft_putstr(" node_name = ");
		ft_putstr(path->node_name);
		ft_putstr(" -> ");
		path = path->next;
	}
}

void		print_paths(t_paths *paths)
{
	if (paths == NULL)
		return ;
	while (paths != NULL)
	{
		ft_putstr("LEN = ");
		ft_putnbr(paths->num_nodes);
		print_path(paths->path);
		ft_putstr("\n");
		paths = paths->next;
	}
	ft_putstr("\n");
}
