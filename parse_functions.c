/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_functions.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmustach <nmustach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/21 17:08:45 by nmustach          #+#    #+#             */
/*   Updated: 2020/11/21 18:48:18 by nmustach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

t_graph		*graph_init(void)
{
	t_graph	*graph;

	MFAIL((graph = malloc(sizeof(t_graph))));
	graph->start = NULL;
	graph->end = NULL;
	graph->h_table = hash_table_init();
	graph->arr_nodes = NULL;
	graph->any_bf = 0;
	graph->num_childs_start = 0;
	graph->num_childs_end = 0;
	graph->speed = INT_MAX;
	graph->begin_path = NULL;
	graph->begin_path_first_res = NULL;
	graph->num_paths_second_res = 0;
	graph->begin_path_second_res = NULL;
	return (graph);
}

int			parse_start_node(char *line, t_graph *graph)
{
	t_hash	*node;
	char	*str_ret;

	if (ft_strequ("##start", line))
	{
		if (graph->start)
			err_exit();
		if (((str_ret = gnl(graph->map_buf)) != NULL)
		&& (node = parse_node_name(graph, str_ret, PARSE_START)))
		{
			graph->start = node;
			return (1);
		}
		else
			err_exit();
	}
	return (0);
}

int			parse_end_node(char *line, t_graph *graph)
{
	t_hash	*node;
	char	*str_ret;

	if (ft_strequ("##end", line))
	{
		if (graph->end)
			err_exit();
		if (((str_ret = gnl(graph->map_buf)) != NULL)
		&& (node = parse_node_name(graph, str_ret, PARSE_END)))
		{
			graph->end = node;
			return (1);
		}
		else
			err_exit();
	}
	return (0);
}

void		parse_links(t_graph *graph, char *line)
{
	char *str_ret;

	parse_connections(graph, line);
	while ((str_ret = gnl(graph->map_buf)) != NULL)
	{
		if (str_ret[0] == '#')
		{
			if (str_ret[0] == '#' && str_ret[1] == '#')
				err_exit();
			continue ;
		}
		parse_connections(graph, str_ret);
	}
}

t_graph		*parse_input(void)
{
	t_graph	*graph;

	graph = NULL;
	graph = graph_init();
	graph->map_buf = read_to_str(0);
	parse_ants_number(graph);
	parse_rooms(graph);
	if (!graph->start->child || !graph->end->child
		|| !graph->end->child->c_node->child)
		err_exit();
	return (graph);
}
