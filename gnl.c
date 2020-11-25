/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gnl.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmustach <nmustach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/14 00:24:47 by nmustach          #+#    #+#             */
/*   Updated: 2020/11/20 21:40:57 by nmustach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

char	*gnl(char *text)
{
	static int	i;
	int			b;

	b = 0;
	if ((i == 0 && (!text[0])) || (i < 0))
		return (NULL);
	if (i > 0)
	{
		text[i] = '\n';
		text = &text[i + 1];
		i += 1;
	}
	if (!text[0])
		return (NULL);
	while (text[b] != '\n' && text[b])
	{
		b += 1;
		i += 1;
	}
	if (!text[b])
		i = -1;
	text[b] = '\0';
	return (text);
}

char	*enlarge_buffer(char *old_buf, size_t *mem_buf)
{
	char	*new_buf;

	*mem_buf = *mem_buf * 2;
	if ((new_buf = malloc(sizeof(char) * *mem_buf)) == NULL)
		err_exit();
	new_buf[0] = 0;
	ft_strcat(new_buf, old_buf);
	free(old_buf);
	return (new_buf);
}

char	*read_to_str(int fd)
{
	char	read_buf[1001];
	char	*buf;
	int		ret;
	size_t	buf_s;
	size_t	mem_buf;

	buf_s = 0;
	mem_buf = 5000;
	if ((buf = malloc(sizeof(char) * mem_buf)) == NULL)
		err_exit();
	buf[0] = '\0';
	while ((ret = read(fd, read_buf, 1000)) > 0)
	{
		if (buf_s + ret >= mem_buf)
			buf = enlarge_buffer(buf, &mem_buf);
		read_buf[ret] = '\0';
		ft_strcat(buf, read_buf);
		buf_s += ret;
	}
	return (buf);
}
