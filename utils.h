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
const char *str_chr(const char *str, char c);

#endif /* utils_h */
