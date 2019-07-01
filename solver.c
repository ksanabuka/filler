#include "filler.h"

void convert_token2coord(int row_max, int column_max, char **s, int **int_token)
{
	int len;

	len = row_max * column_max * 2; 
	*int_token = (int*)malloc(sizeof(int) * len);
	int * tc = *int_token;
	int i = 0;
	while (i < len)
	{
		tc[i] = -2147483648;
		i++;
	}
	int real_row = 0;
	int real_col = 0;
	int init_row = 0;
	int init_col = 0;
	int is_init_coorrd = 0;
	i = 0; 
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
}