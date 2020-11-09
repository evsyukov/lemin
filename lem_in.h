/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmustach <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/18 22:28:00 by nmustach          #+#    #+#             */
/*   Updated: 2020/09/14 02:03:18 by nmustach         ###   ########.fr       */
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
	struct s_hash	*c_node; //  Указатель на вершину t_hash (данные по вершине)
	int				flow; // флаг что ребро в эту сторону есть --->
	int				weight; // вес ребра [1, 0, -1]
	struct s_child	*next; // Указатель списка на следующую вершину
	// NICK
	int 			is_reverse;
	int 			is_part_of_path; //
}					t_child;

// NICK EDITION
typedef struct	s_paths
{
	struct s_path	*path;
	struct s_paths	*next;
}				t_paths;

typedef struct	s_path
{
	struct s_hash	*node;
	struct s_path	*next;
	// NICK EDITION
	size_t			num_nodes;
	struct s_path	*prev;
} 				t_path;

typedef struct s_print
{
	char	*name_room;
	int 	num_l;
}				t_print;

typedef struct	s_vis
{
	struct s_hash	*node;
	struct s_vis	*next;
}				t_vis;

typedef	struct				s_hash
{
	char		*node_name;
	int		x;
	int		y;
	struct		s_hash *next; // Тут хранятся коллизии хэш таблицы (Список)
	size_t			visit; // NICK - не использую
	size_t 		mark; // NICK - не использую
	size_t		bfs_level; // NICK - не использую
	t_child		*child; // Тут хранятся связи для данной ноды (Список)
	struct s_hash 	*prev;
	// NICK EDITION
	size_t		num_node; // номер ноды (индекс в arr_nodes)
}					t_hash;

typedef struct		s_graph
{
	t_hash			**h_table; // Указатель на хэш таблицу
	t_hash			*start; 
	t_hash			*end;
	int				ants_num;
	char			*map_buf;
	t_path			*paths_list; // NICK - не использовал его
	// NICK EDITION
	t_hash			**arr_nodes; // массив указателей на указатели на "комнаты"
	size_t			num_start_node; // номер (индекс) стартовой комнаты
	size_t			num_end_node; // // номер (индекс) конечной комнаты
	size_t			num_paths; // кол-во путей в списке путей
	t_paths			*begin_path; // указатель на первый путь в списке путей
	t_paths			*end_path; // указатель на последний путь в списке путей
}					t_graph;

typedef struct	s_q
{
		struct s_hash	*q_node;
		struct s_q		*next;
}				t_q;

/*
** -------------------------- Hash table functions ----------------------------
*/

t_hash				*hash_query(t_hash **h_table, char *node_name);
unsigned int		calc_hash(char *str);
t_hash				**hash_table_init();
t_hash				*assign_to_table(t_hash **table, char *node_name);
void				free_hash_table(t_hash **h_table);
t_graph				*graph_init();
//void				add_link(t_hash *parent, t_hash *child);
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
** -------------------------- Bfs functions --------------------------------
*/

t_hash				*bfs(t_graph *graph);
void				q_push(t_hash *node, t_q **queue);
t_hash				*q_pop(t_q **queue);
void				*get_shortest_path(t_hash *end_node);
t_path				*path_init(t_hash *start);
t_path				*clone_path(t_path *path);
void				append_to_path(t_path **path, t_hash *node);
void				free_path(t_path *path);
void				free_queue(t_q *queue);

/*
** -------------------------- Debug functions --------------------------------
*/
void				print_hash_table_child(t_hash **h_table);
void				print_hash_table(t_hash **h_table);
void				print_queue(t_q *queue);

int dijkstra(t_graph *graph);
void dijkstra_shortest_reverse(t_graph *graph);
t_child		*get_edge(t_child *haystack, t_hash *needle);
void	get_paths(t_graph *graph);


// NICK EDITION
/*
** -------------------------- Bellman_ford.c ---------------------------------
*/
t_path				*get_bellman_ford_path(t_graph *graph);

/*
** -------------------------- Utils_nick.c -----------------------------------
*/
t_hash				**make_arr_nodes(t_graph *graph);
void				print_graph_arr(t_hash **arr);
void				print_path(t_path *path);
void				print_paths(t_graph *graph);
void				add_path(t_graph *graph, t_path *new_path);

void				free_paths(t_paths *paths);

void				my_cool_func(t_graph *graph);

void				add_link(t_hash *parent, t_hash *child,
					  int weight, int is_reverse);

int					is_already_linked(t_hash *haystack, t_hash *needle);
void				reverse_edges(t_graph *graph, t_path *path);

#endif
