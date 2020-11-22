/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmustach <nmustach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/18 22:10:51 by nmustach          #+#    #+#             */
/*   Updated: 2020/11/21 18:25:40 by nmustach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

unsigned long ml = 0;
unsigned long fr = 0;
unsigned long nodes_num = 0;
unsigned long edges_num = 0;


int	main(void)
{
	t_graph *graph;

	graph = parse_input();
	graph->arr_nodes = make_arr_nodes(graph);
	if (!is_one_path_exist(graph))
		err_exit();
	find_solution(graph);
	ft_putstr("Ants num = ");
	ft_putnbr(graph->ants_num);
	ft_putstr(" \nНабор путей : Speed = ");
	ft_putnbr(graph->speed);
	ft_putstr("\n");
	print_paths(graph->begin_path_first_res);
//	write(1, graph->map_buf, ft_strlen(graph->map_buf));
//	write(1, "\n", 1);
	print_solution(graph);
	free_graph(graph);
	printf("\nMalloc:%lu Free:%lu\n", ml, fr);
}
