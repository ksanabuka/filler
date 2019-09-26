/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obuksha <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/26 12:18:59 by obuksha           #+#    #+#             */
/*   Updated: 2019/09/26 12:19:02 by obuksha          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "player.h"
#include "utils.h"
enum map_filler enemy_filler(struct player p) {
	return p.filler == player1_filler ? player2_filler : player1_filler;
}
struct player read_player(int fd) {
	struct player res;
	char buf[300];
	read_line(fd, buf);
	res.filler = buf[10] == '1' ? player1_filler : player2_filler;
	return res;
}
