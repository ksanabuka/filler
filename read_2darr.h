/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_2darr.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obuksha <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/26 12:19:50 by obuksha           #+#    #+#             */
/*   Updated: 2019/09/26 12:19:54 by obuksha          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef READ_2DARR_H
# define READ_2DARR_H
# include "arr2d.h"

t_arr2d read_map(int fd);
t_arr2d read_piece(int fd);

#endif
