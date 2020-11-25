/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmustach <nmustach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/18 22:28:00 by nmustach          #+#    #+#             */
/*   Updated: 2020/11/21 19:13:48 by nmustach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEM_IN_H
# define LEM_IN_H

# define TABLE_SIZE 10000
# define HASH_MULT 37

# include <stdio.h>
# include <unistd.h>
# include "libft/libft.h"
# include <limits.h>

struct s_hash;

extern unsigned long ml;
extern unsigned long fr;

# define FCNT(x) x; fr++
# define MFAIL(x) if (!(x)) err_exit(); else ml++

# define PARSE_START 1
# define PARSE_END 0

typedef	struct		s_child
{
	int				flow;
	int				weight;
	int				is_reverse;
	int				is_part_of_path;
	struct s_hash	*c_node;
	struct s_child	*next;
}					t_child;

typedef struct		s_paths
{
	struct s_path	*path;
	struct s_paths	*next;
	struct s_path	*begin_print;
	struct s_path	*end_print;
	size_t			num_nodes;
	size_t			num_allowed_ants;
}					t_paths;

typedef struct		s_path
{
	struct s_hash	*node;
	char			*node_name;
	size_t			num_ant;
	struct s_path	*next;
	struct s_path	*prev;
}					t_path;

typedef	struct		s_hash
{
	char			*node_name;
	int				x;
	int				y;
	t_child			*child;
	struct s_hash	*prev;
	struct s_hash	*next;
	size_t			num_node;
}					t_hash;

typedef struct		s_graph
{
	t_hash			**h_table;
	t_hash			*start;
	t_hash			*end;
	size_t			ants_num;
	size_t			nodes_num;
	char			*map_buf;
	t_hash			**arr_nodes;
	size_t			any_bf;
	size_t			num_start_node;
	size_t			num_end_node;
	size_t			num_childs_start;
	size_t			num_childs_end;
	int32_t			speed;
	t_paths			*begin_path;
	t_paths			*begin_path_first_res;
	size_t			num_paths_second_res;
	t_paths			*begin_path_second_res;
}					t_graph;

/*
** -------------------------- Hash table functions ----------------------------
*/

t_hash				*hash_query(t_hash **h_table, char *node_name);
t_hash				**hash_table_init();
t_hash				*assign_to_table(t_hash **table, char *node_name);
void				free_hash_table(t_hash **h_table);
t_graph				*graph_init();
void				check_if_already_linked(t_hash *haystack, t_hash *needle);
void				free_nodes(t_hash *node);
t_hash				*split_and_insert(t_hash **h_table, char *line,
t_hash **node_in, size_t sp_ind[2]);

/*
** -------------------------- Parsing functions -------------------------------
*/

void				parse_comments(char *line, t_graph *graph);
void				parse_connections(t_graph *graph, char *line);
void				parse_links(t_graph *graph, char *line);
int					parse_start_node(char *line, t_graph *graph);
int					parse_end_node(char *line, t_graph *graph);
t_graph				*parse_input();
void				parse_ants_number(t_graph *graph);
void				parse_rooms(t_graph *graph);
int					ft_atoi_validate_pos(const char *str);
t_hash				*parse_node_name(t_graph *graph, char *line, int flag);
char				*read_to_str(int fd);
char				*gnl(char *text);

/*
** -------------------------- bellman_ford.c ----------------------------------
*/
t_path				*get_bellman_ford_path(t_graph *graph);
int					is_one_path_exist(t_graph *graph);

/*
** -------------------------- get_normal_paths.c ------------------------------
*/
void				get_normal_paths(t_graph *graph);

/*
** -------------------------- get_set_paths.c ---------------------------------
*/
size_t				get_set_paths(t_graph *graph);

/*
** -------------------------- calc_speed.c ------------------------------------
*/
void				li_sort(size_t *arr, size_t len);
size_t				do_calc_speed(int num, const size_t *arr, size_t len);
size_t				calc_speed(t_graph *graph);

/*
** -------------------------- debug_func_nick.c -------------------------------
*/
void				print_paths(t_paths *paths);

/*
** -------------------------- find_solution.c ---------------------------------
*/
void				find_solution(t_graph *graph);

/*
** -------------------------- add_path.c --------------------------------------
*/
t_path				*add_path_node(t_path **root, t_hash *node);
t_paths				*create_paths(t_path *path, size_t len_path);
void				add_path_second(t_graph *graph, t_path
*new_path, size_t len_path);

/*
** -------------------------- link_functions.c --------------------------------
*/
void				add_link(t_hash *parent, t_hash *child,
							int weight, int is_part_of_path);
int					is_already_linked(t_hash *haystack, t_hash *needle);

/*
** -------------------------- make_arr_nodes.c --------------------------------
*/
t_hash				**make_arr_nodes(t_graph *graph);

/*
** -------------------------- move_ants.c -------------------------------------
*/
void				move_ants(t_graph *graph, t_paths *paths,
						size_t *count_ants, size_t *sum_ants);

/*
** -------------------------- print_result.c ----------------------------------
*/
void				print_solution(t_graph *graph);

/*
** -------------------------- reverse_edges.c ---------------------------------
*/
void				reverse_edges(t_graph *graph, t_path *path);

/*
** -------------------------- split_nodes.c -----------------------------------
*/
void				handle_double_node(t_graph *graph,
									char *first, char *second);

/*
** -------------------------- utils.c -----------------------------------------
*/
void				err_exit();
void				free_path(t_path *path);
void				free_paths(t_paths *paths);
void				free_graph(t_graph *graph);
int					is_family(char *str, char *str1);

#endif
