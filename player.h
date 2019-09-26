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

enum				e_map_filler
{
	player1_filler = 'o',
	player2_filler = 'x'
};
typedef struct		s_player
{
	enum e_map_filler filler;
}					t_player;
enum e_map_filler	enemy_filler(t_player p);
t_player			read_player(int fd);

#endif
