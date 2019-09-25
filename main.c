//
//  main.c
//  filler2
//
//  Created by Oksana Buksha on 7/21/19.
//  Copyright © 2019 Oksana Buksha. All rights reserved.
//

#include "arr2d.h"
#include "player.h"
#include "utils.h"
#include "read_2darr.h"
#include "point.h"
#include "evaluator.h"

#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

void write_option(t_point p, int fd);

int main(int argc, const char * argv[]) {
    t_player me;
    int in_fd = 0;
    me = read_player(in_fd);
    
    while (1) {
        t_arr2d map = read_map(in_fd);
        t_arr2d piece = read_piece(in_fd);
        t_point p = evaluate_best_move(map, piece, me);
        write_option(p, 1);
        arr2dDispose(piece);
        arr2dDispose(map);
    }
    return 0;
}

void write_option(t_point p, int fd) {
    char str[16];
    i_to_str(p.row, str);
    write(fd, str, str_len(str));
    write(fd, ", ", 2);
    i_to_str(p.col, str);
    write(fd, str, str_len(str));
    write(fd, "\n", 1);
}
