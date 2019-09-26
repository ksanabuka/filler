/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   evaluator.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obuksha <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/26 12:18:42 by obuksha           #+#    #+#             */
/*   Updated: 2019/09/26 12:18:52 by obuksha          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "evaluator.h"
#include "utils.h"
int check_radius_not_too_big(int r, t_point p, t_arr2d map)
{
	int top = p.row - r;
	int left = p.col - r;
	int a = 2 * r + 1;
	return segments_intersect(top, a, 0, map.num_rows) && segments_intersect(left, a, 0, map.num_cols);
}
int check_enemy_in_row(t_point start, int num_cols, t_arr2d map, enum map_filler enemy)
{
	int i;
	i = 0;
	while (i < num_cols)
	{
		if (is_point_in_segment(start.row, 0, map.num_rows) && is_point_in_segment(start.col + i, 0, map.num_cols) && arr2d_get_item_at(map, start.row, start.col + i) == enemy)
			return 1;
		++i;
	}
	return 0;
}
int check_enemy_in_col(t_point start, int num_rows, t_arr2d map, enum map_filler enemy)
{
	int i;
	i = 0;
	while (i < num_rows)
	{
		if (is_point_in_segment(start.row + i, 0, map.num_rows) && is_point_in_segment(start.col, 0, map.num_cols) && arr2d_get_item_at(map, start.row + i, start.col) == enemy)
			return 1;
		++i;
	}
	return 0;
}
int get_enemy_distance(t_arr2d map, t_point p, t_player me)
{
	int r;
	enum map_filler enemy;
	enemy = enemy_filler(me);
	r = 1;
	while (check_radius_not_too_big(r, p, map))
	{
		int a;
		a = 2 * r + 1;
		if (check_enemy_in_row(make_point(p.row - r, p.col - r), a, map, enemy))
			break;
		if (check_enemy_in_row(make_point(p.row + r, p.col - r), a, map, enemy))
			break;
		if (check_enemy_in_col(make_point(p.row - r, p.col - r), a, map, enemy))
			break;
		if (check_enemy_in_col(make_point(p.row - r, p.col + r), a, map, enemy))
			break;
		++r;
	}
	return r;
}
int get_num_players_in_row(int row, t_arr2d map, enum map_filler filler)
{
	int res;
	int c;
	
	res = 0;
	c = 0;
	while (c < map.num_cols)
	{
		if (arr2d_get_item_at(map, row, c) == filler)
			++res;
		++c;
	}
	return res;
}
int get_num_players_in_col(int col, t_arr2d map, enum map_filler filler)
{
	int res;
	int r;
	
	res = 0;
	r = 0;
	while (r < map.num_rows)
	{
		if (arr2d_get_item_at(map, r, col) == filler)
			++res;
		++r;
	}
	return res;
}
int evaluate_score(t_point p, t_arr2d map, t_arr2d piece, t_player me)
{
	int r;
	int c;
	int num_overlaps;
	int score;
	t_point p_map;
	
	r = 0;
	num_overlaps = 0;
	score = 0;
	while (r < piece.num_rows)
	{
		c = 0;
		while (c < piece.num_cols)
		{
			if (arr2d_get_item_at(piece, r, c) == '*')
			{
				p_map = make_point(p.row + r, p.col + c);
				if (is_point_in_segment(p_map.row, 0, map.num_rows) && \
				 is_point_in_segment(p_map.col, 0, map.num_cols) && \
				 (arr2d_get_item_at(map, p_map.row, p_map.col) == '.' || \
				 arr2d_get_item_at(map, p_map.row, p_map.col) == me.filler))
				{
					if (arr2d_get_item_at(map, p_map.row, p_map.col) == me.filler)
					{
						++num_overlaps;
					}
					else
					{
						int ed = get_enemy_distance(map, p_map, me);
						int k = 2;
						int rows_score = k * map.num_cols - k * get_num_players_in_row(p_map.row, map, enemy_filler(me)) - get_num_players_in_row(p_map.row, map, me.filler);
						int cols_score = k * map.num_rows - k * get_num_players_in_col(p_map.col, map, enemy_filler(me)) - get_num_players_in_col(p_map.col, map, me.filler);
						int m1 = (rows_score < cols_score ? rows_score : cols_score);
						score += m1 < ed ? m1 : ed;
					}
				}
				else
				{
					return -1;
				}
			}
			++c;
		}
		++r;
	}
	
	return num_overlaps == 1 ? score : -1;
}
t_point evaluate_best_move(t_arr2d map, t_arr2d piece, t_player me)
{
	t_point best_pos;
	int best_score;
	t_point pos;
	int score;
	best_score = -1;
	best_pos = make_point(0, 0);
	pos.row = -piece.num_rows + 1;
	while (pos.row < map.num_rows)
	{
		pos.col = -piece.num_cols + 1;
		while (pos.col < map.num_cols)
		{
			score = evaluate_score(pos, map, piece, me);
			if (score >= 0 && (best_score < 0 || score < best_score))
			{
				best_score = score;
				best_pos = pos;
			}
			++pos.col;
		}
		++pos.row;
	}
	return best_pos;
}
