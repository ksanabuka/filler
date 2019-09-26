/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   point.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obuksha <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/26 12:19:07 by obuksha           #+#    #+#             */
/*   Updated: 2019/09/26 12:19:13 by obuksha          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "point.h"

t_point	make_point(int row, int col)
{
	t_point p;

	p.row = row;
	p.col = col;
	return (p);
}
