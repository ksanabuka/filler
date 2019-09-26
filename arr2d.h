/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arr2d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obuksha <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/26 12:19:25 by obuksha           #+#    #+#             */
/*   Updated: 2019/09/26 12:19:28 by obuksha          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ARR2D_H
# define ARR2D_H

typedef struct		arr2d
{
	int	num_cols;
	int	num_rows;
	int	*arr;
}					t_arr2d;

struct arr2d		createArr2d(int rows, int cols);
void				arr2dDispose(struct arr2d arr);
int					arr2dGetItemAt(struct arr2d arr, int r, int c);
void				arr2dSetItemAt(struct arr2d arr, int val, int r, int c);


#endif
