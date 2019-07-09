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
    //    map[map_token_coord[j]][map_token_coord[j + 1]] = -1;
        j = j + 2;
    }
    return score + 1;
}

int give_score_for_token(int ** map, t_dim *map_dim, t_coord * token_joint_cell, t_coord * map_joint_cell,  int *token_coord)
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




void add_captured_cells(t_coord *captured_coord, int * my_captured_cells) 
{
   int j = 1;

    while (j < my_captured_cells[0] && my_captured_cells[j] != -2147483648)
    {
        j = j + 2;
    }
    if (j < my_captured_cells[0] && my_captured_cells[j] == -2147483648)
    {
        my_captured_cells[j] = captured_coord->row;
        my_captured_cells[j + 1] = captured_coord->col;
    }
}
int tracking_scoring_for_1_mapcell(int ** map, t_dim *map_dim, t_coord * map_joint_cell,  int *token_coord, int ** token_map_score, int start_index)
{
   
    int i = 1; 
    int score = 0; 
    t_coord * token_joint_cell = (t_coord *)malloc(sizeof(t_coord));
   
   while (i < token_coord[0])
   {
        token_joint_cell->row = token_coord[i]; 
        token_joint_cell->col = token_coord[i + 1];
        score = 0; 

        if ((score == give_score_for_token(map, map_dim, token_joint_cell, map_joint_cell, token_coord)) > 0) 
        {
            (*token_map_score)[start_index] = token_joint_cell->row;
            (*token_map_score)[start_index + 1] = token_joint_cell->col;
            (*token_map_score)[start_index + 2] = map_joint_cell->row;
            (*token_map_score)[start_index + 3] = map_joint_cell->col;
            (*token_map_score)[start_index + 4] = score;
            start_index += start_index + 5;

        }
        i = i + 2; 
   }
   free(token_joint_cell);
   return (start_index == 1) ? 0 : start_index;
}

void tracking_scoring(int ** map, t_dim *map_dim, int *token_coord, int *my_coord, int * token_map_score)
{
     int start_index = 1;
    int j = 1; 

    t_coord * map_joint_cell = (t_coord *)malloc(sizeof(t_coord));
   
    while (j < my_coord[0])
    {
        map_joint_cell->row = my_coord[j]; 
        map_joint_cell->col = my_coord[j + 1];
        start_index += tracking_scoring_for_1_mapcell(map, map_dim, map_joint_cell, token_coord, token_map_score, start_index);
        j = j + 2; 
    }
}

int put_token_on_map(int *map_token_coord, int ** map, t_coord * map_joint_cell, t_coord * token_joint_cell)
{
    int j = 1; 
    int score = 0;

    while (j < map_token_coord[0])
    {
        score += map[map_token_coord[j]][map_token_coord[j + 1]];
       map[map_token_coord[j]][map_token_coord[j + 1]] = -1;
        j = j + 2;
    }
    return score + 1;
}
 int * token_map_score = init_arr_coord(map_dim, 5);