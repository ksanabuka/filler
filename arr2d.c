/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arr2d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obuksha <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/26 12:18:09 by obuksha           #+#    #+#             */
/*   Updated: 2019/09/26 12:18:37 by obuksha          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "arr2d.h"
#include "utils.h"

static int idx(t_arr2d arr, int r, int c)
{
	return r * arr.num_cols + c;
}
t_arr2d create_arr2d(int rows, int cols)
{
	t_arr2d res;
	res.num_cols = cols;
	res.num_rows = rows;
	res.arr = malloc(rows * cols * sizeof(int));
	return res;
}
void arr2d_dispose(t_arr2d arr)
{
	free(arr.arr);
}
int arr2d_get_item_at(t_arr2d arr, int r, int c)
{
	return arr.arr[idx(arr, r, c)];
}
void arr2d_set_item_at(t_arr2d arr, int val, int r, int c)
{
	arr.arr[idx(arr, r, c)] = val;
}
