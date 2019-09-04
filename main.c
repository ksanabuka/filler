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
#include <stdio.h>

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>


int main(int argc, const char * argv[]) {
    struct player p;
    int in_fd = open("test.txt", O_RDONLY);
    p = read_player(in_fd);
    
    while (1) {
        struct arr2d map = read_map(in_fd);
        struct arr2d piece = read_piece(in_fd);
        
        arr2dDispose(piece);
        arr2dDispose(map);
        app_error("not implemented");
    }
    // read player data
    // while (1)
    // read map
    // read token
    // evaluate options
    // write best option
    return 0;
}
