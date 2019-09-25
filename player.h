//
//  player.h
//  filler2
//
//  Created by Oksana Buksha on 7/21/19.
//  Copyright © 2019 Oksana Buksha. All rights reserved.
//

#ifndef player_h
#define player_h

enum map_filler {
    player1_filler = 'o',
    player2_filler = 'x'
};

typedef struct player {
    enum map_filler filler;
} t_player;

enum map_filler enemy_filler(struct player p);
struct player read_player(int fd);

#endif /* player_h */
