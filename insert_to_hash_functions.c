/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   insert_to_hash_functions.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmustach <nmustach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/21 19:03:10 by nmustach          #+#    #+#             */
/*   Updated: 2020/11/21 19:08:24 by nmustach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static t_hash	*insert_node_to_h_table(char *line, t_hash **h_table,
size_t sp_ind[2], char *adding)
{
	int		l_x;
	int		l_y;
	char	*strdup;
	t_hash	*node;

	node = NULL;
	MFAIL((strdup = ft_strjoin(line, adding)));
	node = assign_to_table(h_table, strdup);
	l_x = ft_atoi_validate_pos(&line[sp_ind[0] + 1]);
	l_y = ft_atoi_validate_pos(&line[sp_ind[1] + 1]);
	if (l_x >= 0 && l_y >= 0)
	{
		node->x = l_x;
		node->y = l_y;
	}
	else
		err_exit();
	return (node);
}

t_hash			*split_and_insert(t_hash **h_table, char *line,
t_hash **node_in, size_t sp_ind[2])
{
	char	*str;
	t_hash	*node_out;

	node_out = NULL;
	MFAIL((str = ft_strjoin(line, "_in")));
	if (!hash_query(h_table, str))
	{
		FCNT(free(str));
		*node_in = insert_node_to_h_table(line, h_table, sp_ind, "_in");
		node_out = insert_node_to_h_table(line, h_table, sp_ind, "_out");
		line[sp_ind[0]] = ' ';
		line[sp_ind[1]] = ' ';
	}
	else
		err_exit();
	return (node_out);
}
