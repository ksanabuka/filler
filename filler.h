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

void convert_token2coord(int row_max, int column_max, char **s, int **int_token);
