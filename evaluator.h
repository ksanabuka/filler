#ifndef evaluator_h
#define evaluator_h

#include "arr2d.h"
#include "player.h"
#include "point.h"

int get_enemy_distance(t_arr2d map, t_point p, t_player me);
t_point evaluate_best_move(t_arr2d map, t_arr2d piece, t_player me);

#endif