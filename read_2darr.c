//
//  read_2darr.c
//  filler2
//
//  Created by Oksana Buksha on 7/21/19.
//  Copyright © 2019 Oksana Buksha. All rights reserved.
//

#include "read_2darr.h"
#include "utils.h"
#include <stdlib.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

static void read_arr_lines(int fd, struct arr2d arr, char *buf, int is_map) {
    int r;
    int c;
    char map_char;
    
    if (is_map)
        read_line(fd, buf);
    r = 0;
    
    while (r < arr.num_rows) {
        read_line(fd, buf);
        c = 0;
        
        while (c < arr.num_cols) 
        {
            map_char = buf[c + (is_map ? 4 : 0)];
            if (map_char >= 'A' && map_char <= 'Z') 
            {
                map_char = map_char - 'A' + 'a';
            }
            arr2dSetItemAt(arr, map_char, r, c);
            ++c;
        }
        ++r;
    }
}

//  static void my_read_arr_lines(int fd, struct arr2d arr, int is_map) 
//  {
//     int r;
//     int c;
//     char map_char;
//     int count;
//     int num_cells;
//     char * buf;

//     num_cells = (is_map) ? (arr.num_cols + 4 + 1) * (arr.num_rows + 1) : (arr.num_cols + 1) * arr.num_rows; 
//     buf = (char*)malloc(sizeof(char) * (num_cells + 1)); 
//     count = read(fd, buf, num_cells);
//     printf("num_cells - %d\n bits - %d,\n string:\n%s\n", num_cells, count, buf); 
//     buf[num_cells] = '\0';
   
//     int i; 
   
//     i = (is_map) ? arr.num_cols + 1 + 4: 0; // skip first row in plateu; 
//     r = 0; 
//     while (r < arr.num_rows)
//     {
//         i += (is_map) ? 4 : 0;
//         c = 0;
//         while (c < arr.num_cols)
//         {
//             map_char = buf[i];
//             if (map_char >= 'A' && map_char <= 'Z') 
//             {
//                 map_char = map_char - 'A' + 'a';
//             }
//             arr2dSetItemAt(arr, map_char, r, c);
//             c++; 
//             i++;
//         }
//         i++; 
//         r++;

//     }

//     free(buf);
// }


struct arr2d read_arr2d(int fd, const char *dims_prefix, int is_map) 
{
    struct arr2d res;
    char buf[1024];
    const char *dims_ptr;
    int rows;
    int cols;
    read_line(fd, buf);
    
    if (!str_starts_with(buf, dims_prefix)) {
        app_error("arr dimensions error");
    }
    
    dims_ptr = buf + str_len(dims_prefix);
    rows = str_to_i(dims_ptr);
    dims_ptr = str_chr(dims_ptr, ' ') + 1;
    cols = str_to_i(dims_ptr);
    res = createArr2d(rows, cols);
    read_arr_lines(fd, res, buf, is_map);
    return res;
}

// struct arr2d read_arr2d(int fd, const char *dims_prefix, int is_map) 
// {
//     struct arr2d res;
//     char buf[1024];
//     const char *dims_ptr;
//     int rows;
//     int cols;
//     read_line(fd, buf);
    
//     if (!str_starts_with(buf, dims_prefix)) {
//         app_error("arr dimensions error");
//     }
    
//     dims_ptr = buf + str_len(dims_prefix);
//     rows = str_to_i(dims_ptr);
//     dims_ptr = str_chr(dims_ptr, ' ') + 1;
//     cols = str_to_i(dims_ptr);
//     res = createArr2d(rows, cols);
//     my_read_arr_lines(fd, res, is_map);
//     return res;
// }

struct arr2d read_map(int fd) {
    return read_arr2d(fd, "Plateau ", 1 /* is_map */);
}

struct arr2d read_piece(int fd) {
    return read_arr2d(fd, "Piece ", 0 /* is_map */);
}
