//
//  point.h
//  filler2
//
//  Created by Oksana Buksha on 9/12/19.
//  Copyright © 2019 Oksana Buksha. All rights reserved.
//

#ifndef point_h
#define point_h

typedef struct s_point {
    int row;
    int col;
} t_point;

t_point make_point(int row, int col);

#endif /* point_h */
