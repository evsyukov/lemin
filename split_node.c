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

void	handle_double_node(t_graph *graph,
						   char *first, char *second)
{
	char	*first_in_name;
	char	*first_out_name;
	t_hash	*first_node_in;
	t_hash	*first_node_out;
	char	*second_in_name;
	char	*second_out_name;
	t_hash	*second_node_in;
	t_hash	*second_node_out;

	first_in_name = NULL;
	first_out_name = NULL;
	first_node_in = NULL;
	first_node_out = NULL;
	second_in_name = NULL;
	second_out_name = NULL;
	second_node_in = NULL;
	second_node_out = NULL;

	MFAIL((first_in_name = ft_strjoin(first, "_in")));
	first_node_in = hash_query(graph->h_table, first_in_name);
	MFAIL((first_out_name = ft_strjoin(first, "_out")));
	first_node_out = hash_query(graph->h_table, first_out_name);

	MFAIL((second_in_name = ft_strjoin(second, "_in")));
	second_node_in = hash_query(graph->h_table, second_in_name);
	MFAIL((second_out_name = ft_strjoin(second, "_out")));
	second_node_out = hash_query(graph->h_table, second_out_name);

	FCNT((free(first_in_name)));
	FCNT((free(first_out_name)));
	FCNT((free(second_in_name)));
	FCNT((free(second_out_name)));

	first_in_name = NULL;
	first_out_name = NULL;
	second_in_name = NULL;
	second_out_name = NULL;

	if ((first_node_in && first_node_out && second_node_in && second_node_out)
		&& !ft_strequ(first, second))
	{
		check_if_already_linked(first_node_out, second_node_in);
		check_if_already_linked(second_node_out, first_node_in);
		add_link(first_node_out, second_node_in, 1, 0);
		add_link(second_node_out, first_node_in, 1, 0);
		if (!is_already_linked(first_node_in, first_node_out))
		{
			add_link(first_node_in, first_node_out, 0, 0);
			++edges_num;
		}
		if (!is_already_linked(second_node_in, second_node_out))
		{
			add_link(second_node_in, second_node_out, 0, 0);
			++edges_num;
		}
	}
	else
		err_exit();
}
