/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmustach <nmustach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/18 22:10:51 by nmustach          #+#    #+#             */
/*   Updated: 2020/11/25 21:43:00 by nmustach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static int	check_two_flag(char **argv)
{
	int result;

	result = -1;
	if ((ft_strequ(argv[1], "-p") && ft_strequ(argv[2], "-m"))
	|| (ft_strequ(argv[2], "-p") && ft_strequ(argv[1], "-m")))
		result = 3;
	else
		ft_putstr("Wrong flags [-p] [-m]. "
				"Usage: ./lem-in [-p] path/to/map_file\n");
	return (result);
}

static int	check_args(int argc, char **argv)
{
	int result;

	result = -1;
	if (argc == 1)
		return (0);
	if (argc == 2)
	{
		if (ft_strequ(argv[1], "-p"))
			result = 1;
		else if (ft_strequ(argv[1], "-m"))
			result = 2;
		else
			ft_putstr("Wrong flags [-p] [-m]. "
				"Usage: ./lem-in [-p] path/to/map_file\n");
	}
	else if (argc == 3)
		result = check_two_flag(argv);
	else
		ft_putstr("Too many arguments. "
			"Usage: ./lem-in [-p] [-m] path/to/map_file\n");
	return (result);
}

static void	print_map_buf(char *map_buf)
{
	size_t	len_buf;

	len_buf = ft_strlen(map_buf);
	write(1, map_buf, len_buf);
	if (map_buf[len_buf - 1] != '\n')
		write(1, "\n", 1);
	write(1, "\n", 1);
}

static void	print_debug(t_graph *graph)
{
	ft_putstr("\nAnts num = ");
	ft_putnbr(graph->ants_num);
	ft_putstr("\nNumber turns = ");
	ft_putnbr(graph->speed);
	ft_putstr(" \nPaths :\n");
	print_paths(graph->begin_path_first_res);
}

int			main(int argc, char **argv)
{
	t_graph	*graph;
	int		debug_flag;

	if ((debug_flag = check_args(argc, argv)) == -1)
		return (0);
	graph = parse_input();
	graph->arr_nodes = make_arr_nodes(graph);
	if (!is_one_path_exist(graph))
	{
		ft_putstr_fd("ERROR : No way between Start and End rooms\n", 2);
		exit(1);
	}
	find_solution(graph);
	if (debug_flag != 2 && debug_flag != 3)
		print_map_buf(graph->map_buf);
	print_solution(graph);
	if (debug_flag == 1 || debug_flag == 3)
		print_debug(graph);
	free_graph(graph);
	return (0);
}
