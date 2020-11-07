/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmustach <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/18 22:14:48 by nmustach          #+#    #+#             */
/*   Updated: 2020/09/14 01:51:01 by nmustach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

int	split_line(char *str, size_t *sp)
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

// NICK
static void	fix_for_start_and_end_names(t_graph *graph, char **name)
{
	char 	*temp;

	if (ft_strequ(*name, graph->start->node_name))
	{
		temp = *name;
		MFAIL((*name = ft_strjoin(*name, "_fix")));
		FCNT(free(temp));
	}
	if (ft_strequ(*name, graph->end->node_name))
	{
		temp = *name;
		MFAIL((*name = ft_strjoin(*name, "_fix")));
		FCNT(free(temp));
	}
}

// NICK
static void	handle_double_node(t_graph *graph,
						char *first, char *second)
{
	char	*first_in_name = NULL;
	char	*first_out_name = NULL;
	t_hash	*first_node_in = NULL;
	t_hash	*first_node_out = NULL;

	char	*second_in_name = NULL;
	char	*second_out_name = NULL;
	t_hash	*second_node_in = NULL;
	t_hash	*second_node_out = NULL;

	if (!ft_strequ(first, graph->start->node_name) && !ft_strequ(first, graph->end->node_name))
	{
		MFAIL((first_in_name = ft_strjoin(first, "_in")));
		fix_for_start_and_end_names(graph, &first_in_name);
		first_node_in = hash_query(graph->h_table, first_in_name);
		MFAIL((first_out_name = ft_strjoin(first, "_out")));
		fix_for_start_and_end_names(graph, &first_out_name);
		first_node_out = hash_query(graph->h_table, first_out_name);
	}
	else
	{
		first_node_in = hash_query(graph->h_table, first);
		first_node_out = hash_query(graph->h_table, first);
	}
	if (!ft_strequ(second, graph->start->node_name) && !ft_strequ(second, graph->end->node_name))
	{
		MFAIL((second_in_name = ft_strjoin(second, "_in")));
		fix_for_start_and_end_names(graph, &second_in_name);
		second_node_in = hash_query(graph->h_table, second_in_name);
		MFAIL((second_out_name = ft_strjoin(second, "_out")));
		fix_for_start_and_end_names(graph, &second_out_name);
		second_node_out = hash_query(graph->h_table, second_out_name);
	}
	else
	{
		second_node_in = hash_query(graph->h_table, second);
		second_node_out = hash_query(graph->h_table, second);
	}

	if ((first_node_in && first_node_out && second_node_in && second_node_out)
		&& !ft_strequ(first, second))
	{
		check_if_already_linked(first_node_out, second_node_in);
		check_if_already_linked(second_node_out, first_node_in);
		add_link(first_node_out, second_node_in);
		add_link(second_node_out, first_node_in);
		edges_num += 2;
		if (first_node_in != first_node_out)
		{
			add_link(first_node_out, first_node_in);
			++edges_num;
		}
		if (second_node_in != second_node_out)
		{
			add_link(second_node_out, second_node_in);
			++edges_num;
		}
	}
	else
		err_exit();
}

void	parse_connections(t_graph *graph, char *line)
{
	t_hash	*parent;
	t_hash	*child;
	int		i;

	i = 0;
	if (!line)
		err_exit();
	while (line[i] != '-' && line[i])
		i++;
	if (!line[i])
		err_exit();
	line[i] = 0;
	parent = hash_query(graph->h_table, line);
	child = hash_query(graph->h_table, &line[i + 1]);
	// NICK
//	handle_double_node(graph, line, &line[i + 1]);

	line[i] = '-';
	if ((parent && child) && (parent != child))
	{
		check_if_already_linked(parent, child);
		check_if_already_linked(child, parent);
		add_link(parent, child);
		add_link(child, parent);
		edges_num += 2;
	}
	else
		err_exit();
}

void	parse_links(t_graph *graph, char *line)
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

void	parse_rooms(t_graph *graph)
{
	char	*str_ret;
	t_hash	*node_ret;

	while ((str_ret = gnl(graph->map_buf)) != NULL) // Читаем line by line пока читаются валидные комнаты с координатами как (nodename 25 25)
	{
		if (str_ret[0] == '#')
		{
			parse_comments(str_ret, graph);
			continue ;
		}
		if ((node_ret = parse_node_name(str_ret, graph->h_table))) // Парсим имена комнат и добавляем их в хэш таблицу
			continue ;
		else
			break ; // Если парсинг невалидный, комнаты закончились, переходим на парсинг связей как(nodeA-nodeB)
	}
	if (graph->start && graph->end) // Проверяем на наличие start и end node
		parse_links(graph, str_ret); 
	else
		err_exit();
}

void	err_exit(void)
{
	write(1, "ERROR\n", 6);
	exit(1);
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

void	parse_ants_number(t_graph *graph) 
{
	char	*ret;
	int		ants_num;

	ants_num = 0;
	if ((ret = gnl(graph->map_buf)) != NULL)
	{
		ants_num = ft_atoi_validate_pos(ret);
		if (ants_num > 0)
			graph->ants_num = ants_num;
		else
			err_exit();
	}
	else
		err_exit();
}

t_hash	*insert_node_to_h_table(char *line, t_hash **h_table, size_t sp_ind[2])
{
	int		l_x;
	int		l_y;
	char	*strdup;
	t_hash	*node;

	node = NULL;
	MFAIL((strdup = ft_strdup(line)));
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
	line[sp_ind[0]] = ' ';
	line[sp_ind[1]] = ' ';
	return (node);
}

t_hash	*parse_node_name(char *line, t_hash **h_table)
{
	size_t	i;
	t_hash	*node;
	size_t	sp_ind[2];

	i = 0;
	node = NULL;
	if (!line || line[i] == ' ' || line[i] == 'L')
		err_exit();
	if (split_line(line, sp_ind))
	{
		if (!hash_query(h_table, line))
			// NICK
			// !!!!
			node = insert_node_to_h_table(line, h_table, sp_ind);
		else
			err_exit();
		nodes_num++;
		return (node);
	}
	else
		return (NULL);
}

t_graph	*parse_input(void)
{
	t_graph	*graph;

	graph = NULL;
	graph = graph_init(); // Инициализиуем хэш таблицу и указатели на начальную и конечную ноду
	graph->map_buf = read_to_str(0);  // Читаем в буфер входной поток (0)
	// NICK
	// !!! Сохраняем на всякий нашу изначальную строку для копий графа
	// не знаю будет ли она менятся потом где то
	MFAIL((graph->initial_map_buf = ft_strdup(graph->map_buf)));
//	graph->initial_map_buf = ft_strdup(graph->map_buf);
	parse_ants_number(graph);
	parse_rooms(graph);
	if (!graph->start->child || !graph->end->child)
		err_exit();
	return (graph);
}

// NICK
t_graph	*get_copy_graph(t_graph *graph)
{
	t_graph	*new_graph;

	new_graph = NULL;
	new_graph = graph_init(); // Инициализиуем хэш таблицу и указатели на начальную и конечную ноду
	// коприуем внаглую нашу изначальную строку
	// !!!ПОДУМАТЬ есть мысль вообще скопировать указатель только
	MFAIL((new_graph->map_buf = ft_strdup(graph->initial_map_buf)));
	MFAIL((new_graph->initial_map_buf = ft_strdup(graph->initial_map_buf)));
//	new_graph->map_buf = ft_strdup(graph->initial_map_buf);
	parse_ants_number(new_graph);
	parse_rooms(new_graph);
	if (!new_graph->start->child || !new_graph->end->child)
		err_exit();
	return (new_graph);
}
