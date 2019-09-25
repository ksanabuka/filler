//
//  utils.h
//  filler2
//
//  Created by Oksana Buksha on 7/21/19.
//  Copyright © 2019 Oksana Buksha. All rights reserved.
//

#ifndef utils_h
#define utils_h

void read_line(int fd, char *buf);
int str_starts_with(const char *str, const char *with);
int str_len(const char *str);
void app_error(const char *str);
int str_to_i(const char *str);
void i_to_str(int i, char *str);
const char *str_chr(const char *str, char c);
void str_reverse(char *str);
void str_cpy(char *dst, const char *src);
int is_point_in_segment(int x, int seg_x, int seg_length);
int segments_intersect(int seg_x1, int seg_length1, int seg_x2, int seg_length2);
int i_abs(int n);

#endif /* utils_h */
