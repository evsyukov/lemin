/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi_validate_pos.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmustach <nmustach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/18 23:49:12 by nmustach          #+#    #+#             */
/*   Updated: 2020/11/21 19:09:21 by nmustach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

int		ft_atoi_validate_pos(const char *str)
{
	int	i;
	int	num;

	i = 0;
	num = 0;
	if (!str[i])
		return (-1);
	while (str[i])
		if (ft_isdigit(str[i]))
		{
			if ((num * 10 + (str[i] - '0')) / 10 != num)
				err_exit();
			num = num * 10 + (str[i++] - '0');
		}
		else
			return (-1);
	return (num);
}

void	parse_ants_number(t_graph *graph)
{
	char	*ret;
	int		ants_num;

	ants_num = 0;
	if ((ret = gnl(graph->map_buf)) != NULL)
	{
		ants_num = ft_atoi_validate_pos(ret);
		if (ants_num > 0)
			graph->ants_num = ants_num;
		else
			err_exit();
	}
	else
		err_exit();
}
