/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obuksha <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/26 12:19:40 by obuksha           #+#    #+#             */
/*   Updated: 2019/09/26 12:19:43 by obuksha          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PLAYER_H
# define PLAYER_H

enum	map_filler
{
	player1_filler = 'o',
	player2_filler = 'x'
};
typedef struct player
{
	enum map_filler filler;
} t_player;
enum map_filler enemy_filler(struct player p);
struct player read_player(int fd);

#endif
