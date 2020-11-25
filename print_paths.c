/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_paths.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smanta <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/25 21:22:54 by smanta            #+#    #+#             */
/*   Updated: 2020/11/25 21:23:05 by smanta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static void	print_path(t_path *path)
{
	while (path != NULL)
	{
		ft_putstr(path->node_name);
		if (path->next != NULL)
			ft_putstr(" -> ");
		path = path->next;
	}
}

void		print_paths(t_paths *paths)
{
	if (paths == NULL)
		return ;
	while (paths != NULL)
	{
		ft_putstr("LEN = ");
		ft_putnbr(paths->num_nodes);
		ft_putstr(" Path ~ ");
		print_path(paths->path);
		ft_putstr("\n");
		paths = paths->next;
	}
	ft_putstr("\n");
}
