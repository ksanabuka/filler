#include "filler.h"

int is_my_cell(int *my_cells_coord, t_coord *cur_coord)
{
   
    int i;

    i = 1;
	while (i < my_cells_coord)
	{
		c = 0; 
		while (c < map_dim->column_max)
		{
			if (my_cells_coord[i] == cur_coord->row && my_cells_coord[i + 1] == cur_coord->row)
			c++; 
		}
		r++;
	}

}

int *create_map_token_coord(t_coord * token_joint_cell, t_coord * map_joint_cell,  int *token_coord)
{
    int * map_token_coord = (int*)malloc(sizeof(int) * token_coord[0]);
    if (token_coord && token_coord[0] > 1)
    {
        map_token_coord[0] = token_coord[0]; 
        int r_dif = map_joint_cell->row - token_joint_cell->row;
        int c_dif = map_joint_cell->col - token_joint_cell->col;
        int i = 1;
        while (i < token_coord[0])
        {
            map_token_coord[i] = r_dif + token_coord[i]; 
            map_token_coord[i + 1] = c_dif + token_coord[i + 1];
            i = i + 2;
        }
        return map_token_coord;
    }
    else 
        return 0; 
}

int r_valid_coord(int *map_token_coord, int ** map, int max_row, int max_col)
{
    int j = 1; 

    while (j < map_token_coord[0])
    {
        if (map_token_coord[j] >= 0 && map_token_coord[j + 1] >= 0 && \
           map_token_coord[j] < max_row && map_token_coord[j + 1] < max_col )
           j = j + 2; 
        else 
            return 0; 
    }
    return 1; 
}

int can_put_on_map(int *map_token_coord, int ** map, t_coord * map_joint_cell, t_dim *map_dim)
{
    int i = 0;
    int j = 1;
     
    if (r_valid_coord(map_token_coord, map, map_dim->row_max, map_dim->column_max))
         ;
    else 
        return 0; 

    while (j < map_token_coord[0])
    {
        if ((map[j][j + 1] == 0) || (map[j][j + 1] == -1 && j == map_joint_cell->row && j + 1 == map_joint_cell->col))
        {
            j = j + 2; 
        }
        else 
            return 0;
    }
    return 1; 
}


int put_score_token_on_map(int *map_token_coord, int ** map)
{
    int j = 1; 
    int score = 0;

    while (j < map_token_coord[0])
    {
        score += map[map_token_coord[j]][map_token_coord[j + 1]];
        map[map_token_coord[j]][map_token_coord[j + 1]] = -1;
        j = j + 2;
    }
    return score;
}

int put_token(int ** map, t_dim *map_dim, t_coord * token_joint_cell, t_coord * map_joint_cell,  int *token_coord)
{
    int score = 0; 
    int * map_token_coord = create_map_token_coord(token_joint_cell, map_joint_cell,  token_coord);
    if (can_put_on_map(map_token_coord, map, map_joint_cell, map_dim))
    {
        score = put_score_token_on_map(map_token_coord, map); 
    }
    free(map_token_coord);
    return score; 
}

int put_token_(int *token_coord, int ** map, int *my_cells_coord, t_dim *map_dim)
{
    int r;
    int c;

    r = 0;


	while (r < map_dim->row_max)
	{
		c = 0; 
		while (c < map_dim->column_max)
		{
			if (r_coord_in_list(r, c, my_cells_coord))
            {

            }
			c++; 
		}
		r++;
	}
}