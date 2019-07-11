#include "filler.h"

int *convert_token2coord(int row_max, int column_max, char **s)
{
	int len;
	len = row_max * column_max * 2 + 1; 

	t_dim *map_dim = (t_dim *)malloc(sizeof(t_dim));
	map_dim->row_max = row_max; 
	map_dim->column_max = column_max; 

	int *tc = init_arr_coord(map_dim, 2);
	free(map_dim); 

	int real_row = 0;
	int real_col = 0;
	int init_row = 0;
	int init_col = 0;
	int is_init_coorrd = 0;
	int i = 1; 
	while (real_row < row_max)
	{
		real_col = 0; 
		while (real_col < column_max)
		{
			if (s[real_row][real_col] == '*')
			{
				if (is_init_coorrd == 0)
				{
					init_row = real_row;
					init_col = real_col; 
					is_init_coorrd = 1;
				}
				tc[i] = real_row - init_row;
				tc[i + 1] = real_col - init_col;
				i = i + 2; 
			}
			real_col++;
		}
		real_row++; 
	}
	print_int_arr(tc, tc[0]);
	return tc;
}