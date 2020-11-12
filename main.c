/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmustach <nmustach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/18 22:10:51 by nmustach          #+#    #+#             */
/*   Updated: 2020/11/10 22:02:13 by nmustach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

unsigned long ml = 0;
unsigned long fr = 0;
unsigned long nodes_num = 0;
unsigned long edges_num = 0;

void	free_graph(t_graph *graph)
{
	free_hash_table(graph->h_table);
	FCNT(free(graph->map_buf));
	// NICK
	FCNT(free(graph->arr_nodes));
	free_paths(graph->begin_path);
	free_paths(graph->begin_path_first_res);
	free_paths(graph->begin_path_second_res);

	FCNT(free(graph));
}

int	main(void)
{
	t_graph *graph;

	graph = parse_input();
	// write(1, graph->map_buf, ft_strlen(graph->map_buf));
	/*
	get_paths(graph);
	//bfs(graph);
	//get_shortest_path(graph->end);
	printf("\n\nNodes_num %lu, Edges_num %lu", nodes_num, edges_num);
	// print_hash_table_child(graph->h_table);
	printf("\nStart node:%s\nEnd node:%s\n", graph->start->node_name, graph->end->node_name);
	free_graph(graph);
	printf("\nMalloc:%lu Free:%lu\n",ml, fr);
	*/
	graph->arr_nodes = make_arr_nodes(graph);
	real_func(graph);

	// DEBUG распечатать скорость прохода
	ft_putstr("Ants num = ");
	ft_putnbr(graph->ants_num);
	ft_putstr(" \nНабор путей : Speed = ");
	ft_putnbr(graph->speed);
	ft_putstr("\n");
	print_paths(graph->begin_path_first_res);

	// ??? НУЖНО ???
//	delete_double_nodes(graph);
	free_graph(graph);
	printf("\nMalloc:%lu Free:%lu\n",ml, fr);
}
