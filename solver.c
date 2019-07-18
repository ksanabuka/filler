#include "filler.h"

int *convert_token2coord(int row_max, int column_max, char **s)
{
	
	t_dim *map_dim = (t_dim *)malloc(sizeof(t_dim));
	map_dim->row_max = row_max; 
	map_dim->column_max = column_max; 

	int *tc = init_arr_coord(map_dim, 2);
	free(map_dim); 

	int i = 0;
	int j = 0;
	int k = 1;

	while (i < row_max)
	{
		j = 0; 
		while (j < column_max)
		{
			if (s[i][j] == '*')
			{
				tc[k] = i;
				tc[k + 1] = j;
				k = k + 2;
			}
			j++;
		}
		i++;
	}

	return tc;
}