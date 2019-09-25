//
//  point.c
//  filler2
//
//  Created by Oksana Buksha on 9/12/19.
//  Copyright © 2019 Oksana Buksha. All rights reserved.
//

#include "point.h"

t_point make_point(int row, int col)
{
    t_point p;
    p.row = row;
    p.col = col;
    return p;
}
