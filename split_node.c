/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_node.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smanta <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/22 20:22:12 by smanta            #+#    #+#             */
/*   Updated: 2020/11/22 20:22:14 by smanta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static t_hash	*get_hash_node_in(t_graph *graph, char *name)
{
	t_hash	*node_in;
	char	*name_in;

	MFAIL((name_in = ft_strjoin(name, "_in")));
	node_in = hash_query(graph->h_table, name_in);
	FCNT(free(name_in));
	return (node_in);
}

static t_hash	*get_hash_node_out(t_graph *graph, char *name)
{
	t_hash	*node_out;
	char	*name_out;

	MFAIL((name_out = ft_strjoin(name, "_out")));
	node_out = hash_query(graph->h_table, name_out);
	FCNT(free(name_out));
	return (node_out);
}

void			handle_double_node(t_graph *graph, char *first, char *second)
{
	t_hash	*first_node_in;
	t_hash	*first_node_out;
	t_hash	*second_node_in;
	t_hash	*second_node_out;

	first_node_in = get_hash_node_in(graph, first);
	first_node_out = get_hash_node_out(graph, first);
	second_node_in = get_hash_node_in(graph, second);
	second_node_out = get_hash_node_out(graph, second);
	if (!first_node_in || !first_node_out || !second_node_in
		|| !second_node_out || ft_strequ(first, second))
		err_exit();
	check_if_already_linked(first_node_out, second_node_in);
	check_if_already_linked(second_node_out, first_node_in);
	add_link(first_node_out, second_node_in, 1, 0);
	add_link(second_node_out, first_node_in, 1, 0);
	if (!is_already_linked(first_node_in, first_node_out))
		add_link(first_node_in, first_node_out, 0, 0);
	if (!is_already_linked(second_node_in, second_node_out))
		add_link(second_node_in, second_node_out, 0, 0);
}
