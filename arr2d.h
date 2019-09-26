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

typedef struct		s_arr2d
{
	int	num_cols;
	int	num_rows;
	int	*arr;
}					t_arr2d;

t_arr2d				create_arr2d(int rows, int cols);
void				arr2d_dispose(t_arr2d arr);
int					arr2d_get_item_at(t_arr2d arr, int r, int c);
void				arr2d_set_item_at(t_arr2d arr, int val, int r, int c);


#endif
