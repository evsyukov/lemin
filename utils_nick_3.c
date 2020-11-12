#include "lem_in.h"

t_path			*add_path_node(t_path **root, t_hash *node)
{
	t_path	*path;
	t_path	*new_path;

	path = *root;
	MFAIL((new_path = (t_path *)malloc(sizeof(t_path))));
	new_path->node = node;
	new_path->next = path;
	new_path->prev = NULL;
	if (path != NULL)
		path->prev = new_path;
	*root = new_path;
	return (new_path);
}

static t_path	*get_result_path(t_graph *graph, t_hash *node, size_t *len_path)
{
	t_path	*path;
	t_child	*child;

	path = NULL;
	add_path_node(&path, graph->start);
	add_path_node(&path, node);
	*len_path = 1;
	if (node == graph->end)
		return (path);
	while (node != graph->end)
	{
		child = node->child;
		while (child != NULL)
		{
			if (child->is_part_of_path == 1)
				break ;
			child = child->next;
		}
		if (child == NULL)
		{
			// DEBUG
			ft_putstr("Восстановление одного из конечных путей не получилось");
			free_path(path);
			return (NULL);
		}
		add_path_node(&path, child->c_node);
		node = child->c_node;
		*len_path += 1;
	}
	return (path);
}

static void		reverse_path(t_path **apath)
{
	t_path	*new_rev;
	t_path	*begin_current;
	t_path	*next_current;

	if (apath == NULL || *apath == NULL)
		return ;
	new_rev = NULL;
	begin_current = *apath;
	while (begin_current != NULL)
	{
		next_current = begin_current->next;
		begin_current->next = new_rev;
		new_rev = begin_current;
		begin_current = next_current;
	}
	*apath = new_rev;
}

static void		do_main_get_set_paths(t_graph *graph)
{
	t_child *child;
	t_path	*path;
	size_t	len_path;

	len_path = 0;
	child = graph->start->child;
	while (child != NULL)
	{
		if (child->is_part_of_path == 1)
		{
			path = get_result_path(graph, child->c_node, &len_path);
			if (path == NULL)
				continue ;
			reverse_path(&path);
			add_path_second(graph, path, len_path);
		}
		child = child->next;
	}
}

size_t			get_set_paths(t_graph *graph)
{
	t_path	*new_path;
	size_t	len_path;
	size_t	speed;

	new_path = get_bellman_ford_path(graph, &len_path);
	if (new_path == NULL) // путей больше нет
		return (0);
	reverse_edges(graph, new_path);
	free_path(new_path); // очистка пути БФ
	do_main_get_set_paths(graph);
	speed = calc_speed(graph);
	return (speed);
}
