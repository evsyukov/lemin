/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmustach <nmustach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/18 22:14:48 by nmustach          #+#    #+#             */
/*   Updated: 2020/11/21 19:08:04 by nmustach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

int		split_line(char *str, size_t *sp)
{
	size_t i;

	i = 0;
	while (str[i] != ' ' && str[i])
		i++;
	if (!str[i])
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
		if ((node_ret = parse_node_name(str_ret, graph->h_table, 0)))
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
		else
			err_exit();
	}
}

t_hash	*parse_node_name(char *line, t_hash **h_table, int flag)
{
	t_hash	*node_in;
	t_hash	*node_out;
	size_t	sp_ind[2];

	node_in = NULL;
	if (!line || line[0] == ' ' || line[0] == 'L')
		err_exit();
	if (split_line(line, sp_ind))
	{
		node_out = split_and_insert(h_table, line, &node_in, sp_ind);
		nodes_num += 2;
		if (flag == PARSE_END)
			return (node_in);
		return (node_out);
	}
	else
		return (NULL);
}
