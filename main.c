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
	real_func(graph);

	// DEBUG распечатать скорость прохода
	ft_putstr("Ants num = ");
	ft_putnbr(graph->ants_num);
	ft_putstr(" \nНабор путей : Speed = ");
	ft_putnbr(graph->speed);
	ft_putstr("\n");
	print_paths(graph->begin_path_first_res);

	// PRINT RESULT
	print_solution(graph);

	// ??? НУЖНО ???
//	delete_double_nodes(graph);
	free_graph(graph);
	printf("\nMalloc:%lu Free:%lu\n",ml, fr);
}
