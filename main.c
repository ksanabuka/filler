/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obuksha <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/26 12:18:55 by obuksha           #+#    #+#             */
/*   Updated: 2019/09/26 12:18:57 by obuksha          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "arr2d.h"
#include "player.h"
#include "utils.h"
#include "read_2darr.h"
#include "point.h"
#include "evaluator.h"
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>

void	write_option(t_point p, int fd)
{
	char str[16];

	i_to_str(p.row, str);
	write(fd, str, str_len(str));
	write(fd, ", ", 2);
	i_to_str(p.col, str);
	write(fd, str, str_len(str));
	write(fd, "\n", 1);
}

int		main(void)
{
	t_player	me;
	int			in_fd;
	t_arr2d		map;
	t_arr2d		piece;
	t_point		p;

	in_fd = 0;
	me = read_player(in_fd);
	while (1)
	{
		map = read_map(in_fd);
		piece = read_piece(in_fd);
		p = evaluate_best_move(map, piece, me);
		write_option(p, 1);
		arr2d_dispose(piece);
		arr2d_dispose(map);
	}
	return (0);
}
