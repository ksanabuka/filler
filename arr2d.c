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

static int idx(struct arr2d arr, int r, int c)
{
	return r * arr.num_cols + c;
}
struct arr2d createArr2d(int rows, int cols)
{
	struct arr2d res;
	res.num_cols = cols;
	res.num_rows = rows;
	res.arr = malloc(rows * cols * sizeof(int));
	return res;
}
void arr2dDispose(struct arr2d arr)
{
	free(arr.arr);
}
int arr2dGetItemAt(struct arr2d arr, int r, int c)
{
	return arr.arr[idx(arr, r, c)];
}
void arr2dSetItemAt(struct arr2d arr, int val, int r, int c)
{
	arr.arr[idx(arr, r, c)] = val;
}
