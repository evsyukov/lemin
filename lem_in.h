/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmustach <nmustach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/18 22:28:00 by nmustach          #+#    #+#             */
/*   Updated: 2020/11/20 22:32:09 by nmustach         ###   ########.fr       */
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
extern unsigned long nodes_num;
extern unsigned long edges_num;

# define FCNT(x) x; fr++
# define MFAIL(x) if (!x) err_exit(); else ml++;

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

typedef struct	s_paths
{
	struct s_path	*path;
	struct s_paths	*next;
	struct s_path	*begin_print;
	struct s_path	*current_print;
	struct s_path	*end_print;
	size_t			num_nodes;
}				t_paths;

typedef struct	s_path
{
	struct s_hash	*node;
	char			*node_name;
	size_t			num_ant;
	struct s_path	*next;
	struct s_path	*prev;
}				t_path;

typedef struct	s_vis
{
	struct s_hash	*node;
	struct s_vis	*next;
}				t_vis;

typedef	struct		s_hash
{
	char			*node_name;
	int				x;
	int				y;
	size_t			visit;
	size_t			mark;
	size_t			bfs_level;
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
	char			*map_buf;
	t_path			*paths_list;
	t_hash			**arr_nodes;
	size_t			num_start_node;
	size_t			num_childs_start;
	size_t			num_end_node;
	size_t			num_childs_end;
	int32_t			speed;
	size_t			num_paths;
	t_paths			*begin_path;
	t_paths			*end_path;
	size_t			num_paths_first_res;
	t_paths			*begin_path_first_res;
	t_paths			*end_path_first_res;
	size_t			num_paths_second_res;
	t_paths			*begin_path_second_res;
	t_paths			*end_path_second_res;
}					t_graph;

/*
** -------------------------- Hash table functions ----------------------------
*/

t_hash				*hash_query(t_hash **h_table, char *node_name);
unsigned int		calc_hash(char *str);
t_hash				**hash_table_init();
t_hash				*assign_to_table(t_hash **table, char *node_name);
void				free_hash_table(t_hash **h_table);
t_graph				*graph_init();
void				check_if_already_linked(t_hash *haystack, t_hash *needle);

/*
** -------------------------- Parsing functions --------------------------------
*/

void				parse_comments(char *line, t_graph *graph);
int					parse_start_node(char *line, t_graph *graph);
int					parse_end_node(char *line, t_graph *graph);
t_graph				*parse_input();
int					ft_atoi_validate_pos(const char *str);
int					check_nodenames_is_family(char *str, char *str1);
t_hash				*parse_node_name(char *line, t_hash **h_table, int flag);
char				*read_to_str(int fd);
char				*gnl(char *text);
void				err_exit();

/*
** -------------------------- Debug functions --------------------------------
*/
void				print_hash_table_child(t_hash **h_table);
void				print_hash_table(t_hash **h_table);

int					dijkstra(t_graph *graph);
void				dijkstra_shortest_reverse(t_graph *graph);
t_child				*get_edge(t_child *haystack, t_hash *needle);
void				get_paths(t_graph *graph);

/*
** -------------------------- Bellman_ford.c ---------------------------------
*/
t_path				*get_bellman_ford_path(t_graph *graph, size_t *len_path);

/*
** -------------------------- Utils_nick.c -----------------------------------
*/
t_hash				**make_arr_nodes(t_graph *graph);
t_paths				*create_paths(t_path *path, size_t len_path);
void				add_path(t_graph *graph, t_path *new_path, size_t len_path);
void				add_path_second(t_graph *graph, t_path *new_path, size_t len_path);
void				add_link(t_hash *parent, t_hash *child,
int weight, int is_part_of_path);
int					is_already_linked(t_hash *haystack, t_hash *needle);
void				reverse_edges(t_graph *graph, t_path *path);

/*
** -------------------------- calc_speed.c -----------------------------------
*/
void				li_sort(size_t *arr, size_t len);
size_t				do_calc_speed(int num, const size_t *arr, size_t len);
size_t				calc_speed(t_graph *graph);

/*
** -------------------------- debug_func_nick.c -------------------------------
*/
void				print_graph_arr(t_hash **arr);
void				print_path(t_path *path);
void				print_paths(t_paths *paths);
void				test_speed_calc();

/*
** -------------------------- my_cool_algo.c -----------------------------------
*/
void				real_func(t_graph *graph);
void				my_cool_func(t_graph *graph);

/*
** -------------------------- utils_free.c -----------------------------------
*/
void				free_path(t_path *path);
void				free_paths(t_paths *paths);
void				free_graph(t_graph *graph);

/*
** -------------------------- utils_nick_3.c -----------------------------------
*/
t_path				*add_path_node(t_path **root, t_hash *node);
size_t				get_set_paths(t_graph *graph);

/*
** -------------------------- print_result.c -----------------------------------
*/
void				print_solution(t_graph *graph);

#endif
