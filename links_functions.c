/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   links_functions.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmustach <nmustach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/21 18:30:38 by nmustach          #+#    #+#             */
/*   Updated: 2020/11/21 18:59:07 by nmustach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void		check_if_already_linked(t_hash *haystack, t_hash *needle)
{
	t_child	*c_node_hay;

	c_node_hay = haystack->child;
	while (c_node_hay)
	{
		if (c_node_hay->c_node == needle)
			err_exit();
		c_node_hay = c_node_hay->next;
	}
}

int			is_already_linked(t_hash *haystack, t_hash *needle)
{
	t_child	*c_node_hay;

	c_node_hay = haystack->child;
	while (c_node_hay)
	{
		if (c_node_hay->c_node == needle)
			return (1);
		c_node_hay = c_node_hay->next;
	}
	return (0);
}

void		add_link(t_hash *parent, t_hash *child,
int weight, int is_part_of_path)
{
	t_child *new;
	t_child *c_list;

	if ((new = malloc(sizeof(t_child))) == NULL)
		err_exit();
	new->next = NULL;
	new->c_node = child;
	new->flow = 1;
	new->weight = weight;
	new->is_reverse = weight == -1 ? 1 : 0;
	new->is_part_of_path = is_part_of_path;
	if (parent->child == NULL)
		parent->child = new;
	else
	{
		c_list = parent->child;
		while (c_list->next)
			c_list = c_list->next;
		c_list->next = new;
	}
}

void		parse_connections(t_graph *graph, char *line)
{
	int		i;

	i = 0;
	if (!line)
		err_exit();
	while (line[i] != '-' && line[i])
		i++;
	if (!line[i])
		err_exit();
	line[i] = 0;
	handle_double_node(graph, line, &line[i + 1]);
	line[i] = '-';
}
