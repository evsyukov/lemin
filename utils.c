/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmustach <nmustach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/21 19:06:34 by nmustach          #+#    #+#             */
/*   Updated: 2020/11/21 19:08:56 by nmustach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void	err_exit(void)
{
	write(2, "ERROR\n", 6);
	exit(1);
}

void	free_path(t_path *path)
{
	t_path	*temp_path;

	while (path != NULL)
	{
		temp_path = path;
		path = path->next;
		if (temp_path->node_name != NULL)
		{
			free(temp_path->node_name);
		}
		free(temp_path);
	}
}

void	free_paths(t_paths *paths)
{
	t_paths	*temp_paths;

	while (paths != NULL)
	{
		temp_paths = paths;
		paths = paths->next;
		free_path(temp_paths->path);
		free(temp_paths);
	}
}

void	free_graph(t_graph *graph)
{
	free_hash_table(graph->h_table);
	free(graph->map_buf);
	free(graph->arr_nodes);
	free_paths(graph->begin_path);
	free_paths(graph->begin_path_first_res);
	free_paths(graph->begin_path_second_res);
	free(graph);
}

int		is_family(char *str, char *str1)
{
	size_t	str_l;
	size_t	str1_l;

	str_l = ft_strlen(str);
	str1_l = ft_strlen(str1);
	if (!((str[str_l - 1] == 't' && str1[str1_l - 1] == 'n')
		|| (str[str_l - 1] == 'n' && str1[str1_l - 1] == 't')))
		return (0);
	if (str[str_l - 1] == 't')
		str_l -= 4;
	if (str[str_l - 1] == 'n')
		str_l -= 3;
	if (str1[str1_l - 1] == 't')
		str1_l -= 4;
	if (str1[str1_l - 1] == 'n')
		str1_l -= 3;
	if (str_l == str1_l && ft_strnequ(str, str1, str_l))
		return (1);
	return (0);
}
