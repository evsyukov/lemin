/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi_validate_pos.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmustach <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/18 23:49:12 by nmustach          #+#    #+#             */
/*   Updated: 2020/09/14 01:37:50 by nmustach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

int	ft_atoi_validate_pos(const char *str)
{
	int	i;
	int	num;

	i = 0;
	num = 0;
	if (!str[i])
		return (-1);
	while (str[i])
		if (ft_isdigit(str[i]))
			num = num * 10 + (str[i++] - '0');
		else
			return (-1);
	return (num);
}

int check_nodenames_is_family(char *str, char *str1)
{
	size_t  str_l;
	size_t  str1_l;
	int     result;
	result = 0;
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
	str[str_l] = '\0';
	str1[str1_l] = '\0';
	if (ft_strequ(str, str1))
		result = 1;
	str[str_l] = '_';
	str1[str1_l] = '_';
	return (result);
}
