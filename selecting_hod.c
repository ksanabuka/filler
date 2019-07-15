#include "filler.h"

int *create_map_token_coord(t_coord * token_joint_cell, t_coord * map_joint_cell,  int *token_coord, t_dim *map_dim)
{
    int * map_token_coord = init_arr_coord(map_dim, 2);


    int r_dif = map_joint_cell->row - token_joint_cell->row;
    int c_dif = map_joint_cell->col - token_joint_cell->col;
    int i = 1;
    while (i < token_coord[0] && token_coord[i] != -2147483648)
    {
        map_token_coord[i] = r_dif + token_coord[i]; 
        map_token_coord[i + 1] = c_dif + token_coord[i + 1];
        i = i + 2;
    }
    return map_token_coord;
    
    
}

int r_valid_coord(int *map_token_coord, int max_row, int max_col)
{
    int j = 1; 

    while (j < map_token_coord[0] &&  map_token_coord[j] != -2147483648)
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
    int j = 1;
     
    if (r_valid_coord(map_token_coord, map_dim->row_max, map_dim->column_max))
         ;
    else 
        return 0; 

    while (j < map_token_coord[0] && map_token_coord[j] != -2147483648)
    {
      //  ft_printf("map: %d, 2: %d\n", map[map_token_coord[j]][map_token_coord[j + 1]], map[map_token_coord[j]][map_token_coord[j + 1]]); 


        if (((map[map_token_coord[j]][map_token_coord[j + 1]] != -2) && \
            (map[map_token_coord[j]][map_token_coord[j + 1]] != -1)) || \
            (map[map_token_coord[j]][map_token_coord[j + 1]] == -1 && map_token_coord[j] == map_joint_cell->row && map_token_coord[j + 1] == map_joint_cell->col))
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

    while (j < map_token_coord[0] && map_token_coord[j] != -2147483648)
    {
        score += map[map_token_coord[j]][map_token_coord[j + 1]];
        j = j + 2;
    }
    return score + 1;
}

int give_score_for_token(int ** map, t_dim *map_dim, t_coord * token_joint_cell, t_coord * map_joint_cell,  int *token_coord)
{
    int score = 0; 
    int * map_token_coord = create_map_token_coord(token_joint_cell, map_joint_cell,  token_coord, map_dim);

    // ft_printf("map_token_coord\n");
   // print_int_arr(map_token_coord, map_token_coord[0]);

    if (can_put_on_map(map_token_coord, map, map_joint_cell, map_dim))
    {
        score = put_score_token_on_map(map_token_coord, map); 
    }
    free(map_token_coord);
    return score; 
}

void add_captured_cells(int * map_token_coord, int *my_coord, int map_joint_row, int map_joint_col)
{
    int j = 1;
    int i = 1; 

    while (j < my_coord[0] && my_coord[j] != -2147483648)
        j = j + 2; 
    
    if (j < my_coord[0] && my_coord[j] == -2147483648)
    {
         while (i < map_token_coord[0] && map_token_coord[i] != -2147483648 &&\
                j < my_coord[0] && my_coord[j] == -2147483648)
        {
            if (map_token_coord[i] == map_joint_row && map_token_coord[i + 1] == map_joint_col)
                 ;
            else 
            {
                my_coord[j] = map_token_coord[i];
                my_coord[j + 1] = map_token_coord[i + 1];
                j = j + 2;
            }
            i = i + 2;

        }
    }
}

int tracking_scoring_for_1_mapcell(int ** map, t_dim *map_dim, t_coord * map_joint_cell,  int *token_coord, int ** token_map_score, int start_index)
{
   
    int i = 1; 
    int score = 0; 
    t_coord * token_joint_cell = (t_coord *)malloc(sizeof(t_coord));
   
   while (i < token_coord[0] && token_coord[i] != -2147483648)
   {
        token_joint_cell->row = token_coord[i]; 
        token_joint_cell->col = token_coord[i + 1];
        score = give_score_for_token(map, map_dim, token_joint_cell, map_joint_cell, token_coord); 

        if (score > 0) 
        {
            (*token_map_score)[start_index] = token_joint_cell->row;
            (*token_map_score)[start_index + 1] = token_joint_cell->col;
            (*token_map_score)[start_index + 2] = map_joint_cell->row;
            (*token_map_score)[start_index + 3] = map_joint_cell->col;
            (*token_map_score)[start_index + 4] = score;
            start_index = start_index + 5;

        }
        i = i + 2; 

      
   }
  
   free(token_joint_cell);
   return (start_index == 1) ? 0 : start_index;
}

int find_best_score_position(int * token_map_score)
{
   //print_int_arr(token_map_score, token_map_score[0]);
    int j;
    int tmp; 
    int position;
    if (token_map_score[1] != -2147483648)
    {
        j = 5;
        position = 1; 
        if (j < token_map_score[0] && token_map_score[j] != -2147483648)
            tmp = token_map_score[j];
        while (j < token_map_score[0] && token_map_score[j + 1] != -2147483648)
        {
            if (token_map_score[j + 5] < tmp)
            {
                position = j + 1;
                tmp = token_map_score[j + 5]; 
            }
            j = j + 5; 
        }
        return position; 
    }
    else
        return 0;
}

int tracking_scoring(int ** map, t_dim *map_dim, int *token_coord, int *my_coord, int ** token_map_score)
{
    int start_index = 1;
    int j = 1;
    
    // ft_printf("my_coord\n");
    // print_int_arr(my_coord, my_coord[0]);
    //   ft_printf("\n\n");


// ft_printf("token_coord\n");
//     print_int_arr(token_coord, token_coord[0]);
//       ft_printf("\n\n");

    t_coord * map_joint_cell = (t_coord *)malloc(sizeof(t_coord));
   
    while (j < my_coord[0] && my_coord[j] != -2147483648)
    {
        map_joint_cell->row = my_coord[j]; 
        map_joint_cell->col = my_coord[j + 1];
        start_index += tracking_scoring_for_1_mapcell(map, map_dim, map_joint_cell, token_coord, token_map_score, start_index);
        j = j + 2; 
    }
    free(map_joint_cell);
   return find_best_score_position(*token_map_score);

}

int put_token_on_map(int *map_token_coord, int ** map)
{
    // print_int_arr(map_token_coord, map_token_coord[0]);
    int j = 1; 
    int score = 0;
   
    while (j < map_token_coord[0] && map_token_coord[j] != -2147483648)
    {
        score += map[map_token_coord[j]][map_token_coord[j + 1]];
       map[map_token_coord[j]][map_token_coord[j + 1]] = -1;
        j = j + 2;
    }
    return score + 1;
}

int put_first_token(int ** map, t_dim *map_dim, int *token_coord, int *my_coord)
{
    int score = 0;
    int * token_map_score = init_arr_coord(map_dim, 5);
    
    int position = tracking_scoring(map, map_dim, token_coord, my_coord, &token_map_score);
    if (position == 0)
        return 0;
    // ft_printf("token_map_score\n");
    // print_int_arr(token_map_score,token_map_score[0]);
    // ft_printf("\n\n");

    // ft_printf("map\n");
    // print2d_int_array(map, map_dim);
    // ft_printf("\n\n");

    t_coord * token_joint_cell = (t_coord * )malloc(sizeof(t_coord));
    token_joint_cell->row = token_map_score[position]; 
    token_joint_cell->col = token_map_score[position + 1];

    t_coord * map_joint_cell = (t_coord * )malloc(sizeof(t_coord));
    map_joint_cell->row = token_map_score[position + 2]; 
    map_joint_cell->col = token_map_score[position + 3];



   int * map_token_coord = create_map_token_coord(token_joint_cell, map_joint_cell, token_coord, map_dim);
   
//    ft_printf("map_token_coord\n");
//     print_int_arr(map_token_coord,map_token_coord[0]);
//     ft_printf("\n\n");

    score = put_token_on_map(map_token_coord, map);
    ft_putnbr_fd(map_token_coord[1], 1);
    write(1, " ", 1);
    ft_putnbr_fd(map_token_coord[2], 1);
    write(1, "\n", 1);
    add_captured_cells(map_token_coord, my_coord, map_joint_cell->row, map_joint_cell->col);
    //print_int_arr(my_coord, my_coord[0]);

   // print2d_int_array(map, map_dim);

    free(token_joint_cell);
    free(map_joint_cell);
    return score;
}


void add_my_coords(int ** my_coord, int ** map, t_dim *map_dim)
{
    int i;
	int j = 0;
	
	i = 0; 
    int pos = 1; 
	while (i < map_dim->row_max)
	{
		j = 0; 
		while(j <  map_dim->column_max)
		{
			if (map[i][j] == -1)
            {
                (*my_coord)[pos] = i;
                (*my_coord)[pos + 1] = j;
                pos = pos + 2;
            }
			j++;
		}
		i++;
	} 
}