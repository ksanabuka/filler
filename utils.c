/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obuksha <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/26 12:19:19 by obuksha           #+#    #+#             */
/*   Updated: 2019/09/26 12:19:22 by obuksha          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
void read_line(int fd, char *buf) {
	char c;
	ssize_t count;
	
	while (1)
	{
		count = read(fd, &c, 1);
		if (count != 1 || c == '\n') {
			break ;
		}
		*buf = c;
		++buf;
	}
	*buf = '\0';
}
int str_starts_with(const char *str, const char *with) {
	while (*with) {
		if (*str != *with) {
			return (0);
		}
		++str;
		++with;
	}
	return (1);
}
int str_len(const char *str) {
	int res;
	res = 0;
	while (str[res]) {
		++res;
	}
	return (res);
}
int str_to_i(const char *str) {
	int res;
	res = 0;
	while (*str >= '0' && *str <= '9') {
		res = 10 * res + *str - '0';
		++str;
	}
	return (res);
}
void i_to_str(int n, char *str)
{
	char tmp[16];
	int j;
	int neg;
	neg = n < 0;
	n = neg ? -n : n;
	j = 0;
	while (n)
	{
		tmp[j] = n % 10 + '0';
		n /= 10;
		++j;
	}
	tmp[j] = '\0';
	if (neg)
	{
		str[0] = '-';
		++str;
	}
	str_reverse(tmp);
	str_cpy(str, tmp);
	if (j == 0)
		str_cpy(str, "0");
}
const char *str_chr(const char *str, char c) {
	while (*str) {
		if (*str == c) {
			return str;
		}
		++str;
	}
	return (0);
}
void str_reverse(char *str)
{
	int j;
	int i;
	char c;
	i = 0;
	j = str_len(str);
	while (i < j)
	{
		--j;
		c = str[i];
		str[i] = str[j];
		str[j] = c;
		++i;
	}
}
void str_cpy(char *dst, const char *src)
{
	while ((*dst++ = *src++));
}
void app_error(const char *str)
{
	perror(str);
	exit(-1);
}
int is_point_in_segment(int x, int seg_x, int seg_length)
{
	return x >= seg_x && x < seg_x + seg_length;
}
int segments_intersect(int seg_x1, int seg_length1, int seg_x2, int seg_length2)
{
	int left1;
	int right1;
	int left2;
	int right2;
	left1 = seg_x1;
	right1 = seg_x1 + seg_length1 - 1;
	left2 = seg_x2;
	right2 = seg_x2 + seg_length2 - 1;
	return is_point_in_segment(left1, seg_x2, seg_length2) || is_point_in_segment(right1, seg_x2, seg_length2) || is_point_in_segment(left2, seg_x1, seg_length1) || is_point_in_segment(right2, seg_x1, seg_length1);
}
int i_abs(int n)
{
	return n >= 0 ? n : -n;
}
