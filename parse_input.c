/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmustach <nmustach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/18 22:14:48 by nmustach          #+#    #+#             */
/*   Updated: 2020/11/26 21:04:11 by nmustach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

int		split_line(char *str, size_t *sp)
{
	size_t i;

	i = 0;
	while (str[i] != ' ' && str[i] && str[i] != '-')
		i++;
	if (!str[i] || str[i] == '-')
		return (0);
	str[i] = 0;
	sp[0] = i;
	i++;
	while (str[i] != ' ' && str[i])
		i++;
	if (!str[i])
		return (0);
	str[i] = 0;
	sp[1] = i;
	return (1);
}

void	parse_rooms(t_graph *graph)
{
	char	*str_ret;
	t_hash	*node_ret;

	while ((str_ret = gnl(graph->map_buf)) != NULL)
	{
		if (str_ret[0] == '#')
		{
			parse_comments(str_ret, graph);
			continue ;
		}
		if ((node_ret = parse_node_name(graph, str_ret, 0)))
			continue ;
		else
			break ;
	}
	if (graph->start && graph->end)
		parse_links(graph, str_ret);
	else
		err_exit();
}

void	parse_comments(char *line, t_graph *graph)
{
	if (line[0] == '#' && line[1] == '#')
	{
		if (parse_start_node(line, graph))
			return ;
		else if (parse_end_node(line, graph))
			return ;
	}
}

t_hash	*parse_node_name(t_graph *graph, char *line, int flag)
{
	t_hash	*node_in;
	t_hash	*node_out;
	size_t	sp_ind[2];

	node_in = NULL;
	if (!line || line[0] == ' ' || line[0] == 'L')
		err_exit();
	if (split_line(line, sp_ind))
	{
		node_out = split_and_insert(graph->h_table, line, &node_in, sp_ind);
		graph->nodes_num += 2;
		if (flag == PARSE_END)
			return (node_in);
		return (node_out);
	}
	else
		return (NULL);
}
