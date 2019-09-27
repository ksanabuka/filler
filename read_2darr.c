/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_2darr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obuksha <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/26 12:19:15 by obuksha           #+#    #+#             */
/*   Updated: 2019/09/26 12:19:17 by obuksha          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "read_2darr.h"
#include "utils.h"
#include <stdlib.h>
#include <unistd.h>
#include <stdlib.h>

static void	read_arr_lines(int fd, t_arr2d arr, char *buf, int is_map)
{
	int		r;
	int		c;
	char	map_char;

	if (is_map)
		read_line(fd, buf);
	r = 0;
	while (r < arr.num_rows)
	{
		read_line(fd, buf);
		c = 0;

		while (c < arr.num_cols)
		{
			map_char = buf[c + (is_map ? 4 : 0)];
			if (map_char >= 'A' && map_char <= 'Z')
			{
				map_char = map_char - 'A' + 'a';
			}
			arr2d_set_item_at(arr, map_char, r, c);
			++c;
		}
		++r;
	}
}

t_arr2d		read_arr2d(int fd, const char *dims_prefix, int is_map)
{
	t_arr2d		res;
	char		buf[1024];
	const char	*dims_ptr;
	int			rows;
	int			cols;

	read_line(fd, buf);
	if (!str_starts_with(buf, dims_prefix))
	{
		app_error("It's the end.");
	}
	dims_ptr = buf + str_len(dims_prefix);
	rows = str_to_i(dims_ptr);
	dims_ptr = str_chr(dims_ptr, ' ') + 1;
	cols = str_to_i(dims_ptr);
	res = create_arr2d(rows, cols);
	read_arr_lines(fd, res, buf, is_map);
	return (res);
}

t_arr2d		read_map(int fd)
{
	return (read_arr2d(fd, "Plateau ", 1));
}

t_arr2d		read_piece(int fd)
{
	return (read_arr2d(fd, "Piece ", 0));
}
