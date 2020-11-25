/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hash.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmustach <nmustach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/20 14:44:25 by nmustach          #+#    #+#             */
/*   Updated: 2020/11/21 18:24:08 by nmustach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static unsigned int	calc_hash(const char *node_name)
{
	unsigned long int	value;
	unsigned int		i;

	value = 0;
	i = 0;
	while (node_name[i])
		value = value * HASH_MULT + node_name[i++];
	return (value % TABLE_SIZE);
}

t_hash				**hash_table_init(void)
{
	size_t	i;
	t_hash	**hash_table;

	i = 0;
	if ((hash_table = malloc(sizeof(t_hash*) * TABLE_SIZE)) == NULL)
		err_exit();
	while (i < TABLE_SIZE)
	{
		hash_table[i] = NULL;
		i++;
	}
	return (hash_table);
}

t_hash				*assign_to_table(t_hash **table, char *node_name)
{
	t_hash			*new;
	unsigned int	hash_val;
	t_hash			*node;

	hash_val = calc_hash(node_name);
	if ((new = malloc(sizeof(t_hash))) == NULL)
		err_exit();
	new->next = NULL;
	new->child = NULL;
	new->x = 0;
	new->y = 0;
	new->node_name = node_name;
	new->prev = NULL;
	if (table[hash_val] == NULL)
		table[hash_val] = new;
	else
	{
		node = table[hash_val];
		while (node->next)
			node = node->next;
		node->next = new;
	}
	return (new);
}

t_hash				*hash_query(t_hash **h_table, char *node_name)
{
	t_hash			*node;
	unsigned int	hash_val;

	hash_val = calc_hash(node_name);
	if (h_table[hash_val] == NULL)
		return (NULL);
	node = h_table[hash_val];
	while (node)
	{
		if (ft_strequ(node_name, node->node_name))
			return (node);
		node = node->next;
	}
	return (NULL);
}
