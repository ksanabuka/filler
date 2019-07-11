#include <fcntl.h>
#include "inc/gnl/get_next_line.h"
#include "inc/gnl/libft/libft.h"
#include "inc/ft_printf/parser.h"
#include <stdlib.h>
#include <stdio.h>

typedef struct  s_dim
{
    int row_max;
    int column_max;
}				t_dim;

typedef struct  s_coord
{
    int row;
    int col;
}               t_coord;

typedef struct s_token
{
    t_dim *token_dim;
    char **char_token;
    int *token_coord;
    int *token_map_coord;
    int len_token_coord;

}				t_token;

typedef struct  s_filler
{
    int me;
    int enemy;
    
    t_dim *map_dim;
    t_token *token;
    char **char_map;
    int **int_map;
}				t_filler;

int *convert_token2coord(int row_max, int column_max, char **s);
int r_coord_in_list(int r, int c, int * checked_coord_stack); 
void print_int_arr(int * arr, int len);
int * init_arr_coord(t_dim *map_dim, int qtycoord);
 void put_first_token(int ** map, t_dim *map_dim, int *token_coord, int *my_coord);
void add_my_initial_coords(int ** my_coord, int ** map, t_dim *map_dim);
void print2d_int_array(int ** arr, t_dim *map_dim);