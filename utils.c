//
//  utils.c
//  filler2
//
//  Created by Oksana Buksha on 7/21/19.
//  Copyright © 2019 Oksana Buksha. All rights reserved.
//

#include "utils.h"
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

void read_line(int fd, char *buf) {
    char c;
    ssize_t count;
    
    while (1) {
        count = read(fd, &c, 1);
        if (count != 1 || c == '\n') {
            break;
        }
        *buf = c;
        ++buf;
    }
    *buf = '\0';
}

int str_starts_with(const char *str, const char *with) {
    while (*with) {
        if (*str != *with) {
            return 0;
        }
        ++str;
        ++with;
    }
    return 1;
}

int str_len(const char *str) {
    int res;
    res = 0;
    while (str[res]) {
        ++res;
    }
    return res;
}

int str_to_i(const char *str) {
    int res;
    res = 0;
    while (*str >= '0' && *str <= '9') {
        res = 10 * res + *str - '0';
        ++str;
    }
    return res;
}

const char *str_chr(const char *str, char c) {
    while (*str) {
        if (*str == c) {
            return str;
        }
        ++str;
    }
    return 0;
}

void app_error(const char *str) {
    perror(str);
    exit(-1);
}
