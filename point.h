#ifndef point_h
#define point_h

typedef struct s_point {
    int row;
    int col;
} t_point;

t_point make_point(int row, int col);

#endif
