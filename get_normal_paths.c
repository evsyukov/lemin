/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_normal_paths.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smanta <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/22 20:16:36 by smanta            #+#    #+#             */
/*   Updated: 2020/11/22 20:16:37 by smanta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static void	mod_name(t_path *path)
{
	char	*str;
	size_t	len;

	MFAIL((path->node_name = ft_strdup(path->node->node_name)));
	str = path->node_name;
	len = ft_strlen(str);
	if (str[len - 1] == 't')
		str[len - 4] = '\0';
	else
		str[len - 3] = '\0';
}

static void	get_normal_path(t_path **apath)
{
	t_path	*path;
	t_path	*path_next;

	if (apath == NULL || *apath == NULL)
		return ;
	path = *apath;
	mod_name(path);
	while (path->next != NULL)
	{
		path_next = path->next;
		mod_name(path_next);
		if (ft_strequ(path->node_name, path_next->node_name))
		{
			path->next = path_next->next;
			if (path_next->next != NULL)
				path_next->next->prev = path;
			FCNT(free(path_next->node_name));
			FCNT((free(path_next)));
			mod_name(path->next);
		}
		path = path->next;
	}
}

void		get_normal_paths(t_graph *graph)
{
	t_paths	*paths;
	t_path	*path;

	paths = graph->begin_path_second_res;
	while (paths != NULL)
	{
		path = paths->path;
		get_normal_path(&path);
		paths->num_nodes = (paths->num_nodes + 1) / 2;
		paths = paths->next;
	}
}
