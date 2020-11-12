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

static int	disable_edge(t_hash	*curr_hash, t_hash *next_hash, int *flag)
{
	t_child	*child;
	char 	*str_1;
	char	*str_2;

	child = curr_hash->child;
	str_2 = next_hash->node_name;
	while (child != NULL)
	{
		str_1 = child->c_node->node_name;
		if (ft_strequ(str_1, str_2))
		{
			child->flow = 0;
			if (child->is_reverse == 1)
			{
				child->is_part_of_path = 0;
				*flag = 1;
			}
			else
			{
				child->is_part_of_path = 1;
			}
			return (1);
		}
		child = child->next;
	}
	return (0);
}

static int	disable_just_edge(t_hash *first, t_hash *second)
{
	t_child	*child;
	char 	*str_1;
	char	*str_2;

	child = first->child;
	str_2 = second->node_name;
	while (child != NULL)
	{
		str_1 = child->c_node->node_name;
		if (ft_strequ(str_1, str_2))
		{
			child->flow = 0;
			child->is_part_of_path = 0;
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
	int 	flag;

	flag = 0;
	while (path->node != graph->end)
	{
		curr_hash = path->node;
		next = path->next;
		next_hash = next->node;
		if (!disable_edge(curr_hash, next_hash, &flag))
		{
			// DEBUG
			ft_putstr("Удаление ребра из прямого пути БФ. Что то пошло не так оО\n");
			err_exit();
		}
		if (flag == 0)
		{
			if (check_nodenames_is_family(curr_hash->node_name, next_hash->node_name))
				add_link(next_hash, curr_hash, 0, 0);
			else
				add_link(next_hash, curr_hash, -1, 0);
		}
		else
		{
			if (!disable_just_edge(next_hash, curr_hash))
			{
				// DEBUG
				ft_putstr("Удаление ребра из прямого пути БФ. JUST_FUNC. Что то пошло не так оО\n");
				err_exit();
			}
			flag = 0;
		}
		path = next;
	}
}
