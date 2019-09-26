/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   evaluator.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obuksha <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/26 12:19:31 by obuksha           #+#    #+#             */
/*   Updated: 2019/09/26 12:19:34 by obuksha          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EVALUATOR_H
# define EVALUATOR_H
# include "arr2d.h"
# include "player.h"
# include "point.h"

int get_enemy_distance(t_arr2d map, t_point p, t_player me);
t_point evaluate_best_move(t_arr2d map, t_arr2d piece, t_player me);

#endif
