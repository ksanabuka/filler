// gcc -Wall -Werror -Wextra -g -fsanitize=address ./inc/gnl/get_next_line.c main.c solver.c selecting_hod.c -L ./inc/gnl/libft -lft -L ./inc/ft_printf -lftprintf -I ./inc/ft_printf/parser.h   -I./inc/gnl -I./inc/gnl/libft -o obuksha.filler
//./filler_vm -f maps/map00 -p1 players/abanlin.filler -p2 players/champely.filler -sjk

//./filler_vm -f maps/map00 -p2 players/abanlin.filler -p1 ../obuksha.filler  | less
#include "filler.h"

void	error(char *message)
{
	perror(message);
	exit(1);
}

void print_int_arr(int * arr, int len)
{
	int a = 0;
	while (a < len)
		ft_printf("%d\t", arr[a++]);
}

void print2d_int_array(int ** arr, t_dim *map_dim)
{
	int i = 0;

	while (i < map_dim->row_max)
	{
		print_int_arr(arr[i++], map_dim->column_max);
		ft_printf("printing map...\n");
	}
}

int get_num_players(char *s, int * me, int * enemy)
{
	if ((*(s + 10) != '1') && (*(s + 10) != '2'))
		return (0); 

	*me = (*(s + 10) == '1')? 'O' : 'X';
	*enemy = (*(s + 10) == '1')? 'X' : 'O';

	// filler->me = (*(s + 10) == '1')? -1 : -2;
	// filler->enemy = (*(s + 10) == '1')? -2 : -1;
	return (1);
}

int get_map_dim(char *s, t_filler * filler)
{
	int len;

	if ((*(s + 8) <= '0') && (*(s + 8) > '9'))
		return (0); 
	filler->map_dim->row_max = ft_atoi(s + 8);
	len = ft_strlen((ft_itoa(filler->map_dim->row_max)));
	if ((*(s + 8 + 1 + len) <= '0') &&  (*(s + 8 + 1 + len) > '9'))
		return (0); 
	filler->map_dim->column_max = ft_atoi(s + 8 + 1 + len);
	return (1);
}

int get_token_dim(char *s, t_filler * filler)
{
	int len;

	if ((*(s + 6) <= '0') && (*(s + 6) > '9'))
		return (0); 
	filler->token->token_dim->row_max = ft_atoi(s + 6);
	len = ft_strlen((ft_itoa(filler->token->token_dim->row_max)));
	if ((*(s + 6 + 1 + len) <= '0') &&  (*(s + 6 + 1 + len) > '9'))
		return (0); 
	filler->token->token_dim->column_max = ft_atoi(s + 6 + 1 + len);
	return (1);
}


void print_2d_map(char ** map, int rows)
{
	int i = 0;
	while (i < rows)
		ft_printf("%s\n", map[i++]);
	ft_printf("\n");
}

char  ** char_map_init(int rows, int columns)
{
	char ** char_map = (char**)malloc(sizeof(char *) * rows);
	int i = 0;
	while (i < rows)
	{
		char_map[i] = ft_strnew(columns);
		i++; 
	}
	return (char_map);
}

void get_map(int fd, t_filler * filler)
{
	filler->char_map = char_map_init(filler->map_dim->row_max, filler->map_dim->column_max);
	int i = 0;
	char *str;
	get_next_line(fd, &str);
	while (i < filler->map_dim->row_max)
	{
		get_next_line(fd, &str);
		filler->char_map[i] = ft_strcpy(filler->char_map[i], str + 4);
		i++;
	}
//	print_2d_map(filler->char_map, filler->map_dim->row_max);
}

void get_token(int fd, t_filler * filler)
{
	filler->token->char_token = char_map_init(filler->token->token_dim->row_max, filler->token->token_dim->column_max);
	int i = 0;
	char *str = 0;
//	ft_printf("%s\n", str);
	while (i < filler->token->token_dim->row_max)
	{
		get_next_line(fd, &str);
		filler->token->char_token[i] = ft_strcpy(filler->token->char_token[i], str);
		i++;
	}
//	print_2d_map(filler->token->char_token, filler->token->token_dim->row_max);
}

void free2darray(char ** s, int num_rows)
{
	int i;

	i = 0; 
	while (i < num_rows)
	{
		free(s[i]);
		i++;
	}
	free(s);
	s = 0; 
}

void cleanup(t_filler * filler)
{
	free2d_int_array(filler->int_map, filler->map_dim->row_max); 
	free2darray(filler->char_map, filler->map_dim->row_max);
	free2darray(filler->token->char_token, filler->token->token_dim->row_max);
	free(filler->token->token_dim);
	free(filler->token->token_coord);
	free(filler->token);
	free(filler->map_dim);
	free(filler);

}

t_filler *init_struct(void)
{
		t_filler * filler = (t_filler *)malloc(sizeof(t_filler));
		filler->map_dim = (t_dim *)malloc(sizeof(t_dim));
		filler->token = (t_token *)malloc(sizeof(t_token));
		filler->token->token_dim = (t_dim *)malloc(sizeof(t_dim));
		return (filler);
}



int ** init_int_map(t_dim* map_dim)
{
	int i = 0;
	int j = 0;
	int ** int_map;
	int_map = (int**)malloc(sizeof(int*) * map_dim->row_max);
	while (i < map_dim->row_max)
	{
		int_map[i] = (int*)malloc(sizeof(int) * map_dim->column_max);
		i++;
	}
	i = 0; 
	while (i < map_dim->row_max)
	{
		j = 0; 
		while(j <  map_dim->column_max)
		{
			int_map[i][j]= 0;
			j++;
		}
		i++;
	}
	return (int_map);
}

void free2d_int_array(int ** ar, int num_rows)
{
	int i;

	i = 0; 
	while (i < num_rows)
	{
		free(ar[i]);
		i++;
	}
	free(ar);
	ar = 0; 
}

void mark_checked(t_coord *newcoord, int *checked_coord_stack)
{
	int i = 1;

	while (i < checked_coord_stack[0] && checked_coord_stack[i] != -2147483648)
	{
		i++;
	}
	checked_coord_stack[i] = newcoord->row;
	checked_coord_stack[i + 1] = newcoord->col; 
}

void mark_cell(int level, int ** map, t_coord *coords, t_dim *map_dim, int ** checked_coord_stack)
{
	int r = 1;
	int c = 1; 

	while (r <= level)
	{
		if ((coords->row + r <  map_dim->row_max) && (map[coords->row + r][coords->col] == 0))
		{
			map[coords->row + r][coords->col] = level;
			
		}
		r++;
	}

	r = 1;
	c = 1; 
	while (r <= level)
	{
		if ((coords->row - r >=  0) && (map[coords->row - r][coords->col] == 0))
		{	
			map[coords->row - r][coords->col] = level; 
			
		}
		r++;
	}

	r = 1;
	c = 1; 
	while (c <= level)
	{
		if ((coords->col + c <  map_dim->column_max) && (map[coords->row][coords->col + c] == 0))
		{	
			map[coords->row][coords->col + c] = level;
			
		}
		c++;
	}
	
	r = 1;
	c = 1; 
	while (c <= level)
	{
		if ((coords->col - c >=  0) && (map[coords->row][coords->col - c] == 0))
		{	
			map[coords->row][coords->col - c] = level; 
			
		}
		c++;
	}
	
	r = 1;
	c = 1;
	while (r <= level)
	{
		c = 1; 
		while (c <= level)
		{
			if ((coords->row + r <  map_dim->row_max) && (coords->col - c >= 0)\
			&& (map[coords->row + r][coords->col - c] == 0))
			{
				map[coords->row + r][coords->col - c] = level;
				
			}
			c++; 
		}
		r++;
	}
	
	
	r = 1;
	c = 1;
	while (r <= level)
	{
		c = 1; 
		while (c <= level)
		{
			if ((coords->row + r <  map_dim->row_max) && (coords->col + c < map_dim->column_max)\
			&& (map[coords->row + r][coords->col + c] == 0))
			{
				map[coords->row + r][coords->col + c] = level;
				
			}
			c++; 
		}
		r++;
	}

	r = 1;
	c = 1;
	while (r <= level)
	{
		c = 1; 
		while (c <= level)
		{
			if ((coords->row - r >= 0) && (coords->col - c >= 0)\
			&& (map[coords->row - r][coords->col - c] == 0))
			{
				map[coords->row - r][coords->col - c] = level;
				
			}
			c++; 
		}
		r++;
	}

	
	r = 1;
	c = 1;
	while (r <= level)
	{
		c = 1; 
		while (c <= level)
		{
			if ((coords->row - r >= 0) && (coords->col + c < map_dim->column_max)\
			&& (map[coords->row - r][coords->col + c] == 0))
			{
				map[coords->row - r][coords->col + c] = level;
				
			}
			c++; 
		}
		r++;
	}

	mark_checked(coords, *checked_coord_stack); 

}


int r_coord_in_list(int r, int c, int *checked_coord_stack)
{
	int i;
	
	i = 1;
	 
	if (checked_coord_stack && checked_coord_stack[0] > 0 && checked_coord_stack[i] != -2147483648)
	{
		while (i < checked_coord_stack[0] && checked_coord_stack[i] != -2147483648)
		{
			if (checked_coord_stack[i] == r && checked_coord_stack[i + 1] == c)
				return 1;
			i = i + 2; 
		}
	}
	return 0; 
}


int * init_arr_coord(t_dim *map_dim, int qtycoord)
{
	int stack_size = qtycoord * map_dim->column_max * map_dim->row_max + 1; 
	int * checked_coord_stack = (int *)malloc(sizeof(int) * stack_size);
	int i = 0;
	while (i < stack_size)
	{
		checked_coord_stack[i] = -2147483648;
		i++;
	}
	checked_coord_stack[0] = stack_size;
	return checked_coord_stack;
}


void check_mark_neibours(int *level, int ** map, t_coord *coords, t_dim *map_dim, int value_to_surround, int ** checked_coord_stack)
{
	t_coord * newcoord = (t_coord * )malloc(sizeof(t_coord));
		if ((coords->row + 1 <  map_dim->row_max) && (map[coords->row + 1][coords->col] == value_to_surround))
		{
			newcoord->row = coords->row + 1;
			newcoord->col = coords->col;
			if (!r_coord_in_list(newcoord->row, newcoord->col, *checked_coord_stack))
			{
				mark_cell(*level, map, newcoord, map_dim, checked_coord_stack);
  
				check_mark_neibours(level, map, newcoord, map_dim, value_to_surround, checked_coord_stack); 
			}
		}
		if ((coords->row - 1 >=  0) && (map[coords->row - 1][coords->col] == value_to_surround))
		{
			newcoord->row = coords->row - 1;
			newcoord->col = coords->col; 
			if (!r_coord_in_list(newcoord->row, newcoord->col, *checked_coord_stack))
				{
					mark_cell(*level, map, newcoord, map_dim, checked_coord_stack);
	  
					check_mark_neibours(level, map, newcoord, map_dim, value_to_surround, checked_coord_stack); 
				}
		}
		
		if ((coords->col + 1 <  map_dim->column_max) && (map[coords->row][coords->col + 1] == value_to_surround))
		{
			newcoord->row = coords->row;
			newcoord->col = coords->col + 1; 
			if (!r_coord_in_list(newcoord->row, newcoord->col, *checked_coord_stack))
				{
					mark_cell(*level, map, newcoord, map_dim, checked_coord_stack);
	  
					check_mark_neibours(level, map, newcoord, map_dim, value_to_surround, checked_coord_stack); 
				}
		}	

		if ((coords->col - 1 >=  0) && (map[coords->row][coords->col - 1] == value_to_surround))
		{
			newcoord->row = coords->row;
			newcoord->col = coords->col - 1; 
			if (!r_coord_in_list(newcoord->row, newcoord->col, *checked_coord_stack))
				{
					mark_cell(*level, map, newcoord, map_dim, checked_coord_stack);
	  
					check_mark_neibours(level, map, newcoord, map_dim, value_to_surround, checked_coord_stack); 
				}
		}

		if ((coords->row + 1 <  map_dim->row_max) && (coords->col - 1 >= 0)\
			&& (map[coords->row + 1][coords->col - 1] == value_to_surround))
		{
			newcoord->row = coords->row + 1;
			newcoord->col = coords->col - 1; 
			if (!r_coord_in_list(newcoord->row, newcoord->col, *checked_coord_stack))
				{
					mark_cell(*level, map, newcoord, map_dim, checked_coord_stack);
	  
					check_mark_neibours(level, map, newcoord, map_dim, value_to_surround, checked_coord_stack); 
				}
		}	
		if ((coords->row + 1 <  map_dim->row_max) && (coords->col + 1 < map_dim->column_max)\
			&& (map[coords->row + 1][coords->col + 1] == value_to_surround))
		{
			newcoord->row = coords->row + 1;
			newcoord->col = coords->col + 1; 
			if (!r_coord_in_list(newcoord->row, newcoord->col, *checked_coord_stack))
			{
				mark_cell(*level, map, newcoord, map_dim, checked_coord_stack);
  
				check_mark_neibours(level, map, newcoord, map_dim, value_to_surround, checked_coord_stack); 
			}

		}	
		if ((coords->row - 1 >= 0) && (coords->col - 1 >= 0)\
			&& (map[coords->row - 1][coords->col - 1] == value_to_surround))
		{
			newcoord->row = coords->row - 1;
			newcoord->col = coords->col - 1; 
			if (!r_coord_in_list(newcoord->row, newcoord->col, *checked_coord_stack))
				{
					mark_cell(*level, map, newcoord, map_dim, checked_coord_stack);
	  
					check_mark_neibours(level, map, newcoord, map_dim, value_to_surround, checked_coord_stack); 
				}
		}	
		if ((coords->row - 1 >= 0) && (coords->col + 1 < map_dim->column_max)\
			&& (map[coords->row - 1][coords->col + 1] == value_to_surround))
		{
			newcoord->row = coords->row - 1;
			newcoord->col = coords->col + 1; 
			if (!r_coord_in_list(newcoord->row, newcoord->col, *checked_coord_stack))
				{
					mark_cell(*level, map, newcoord, map_dim, checked_coord_stack);
					check_mark_neibours(level, map, newcoord, map_dim, value_to_surround, checked_coord_stack); 
				}
		}	
		free(newcoord);
		return ;
}



int is_any_empty(int ** map, t_dim *map_dim)
{
	int r;
	int c; 

	r = 0; 
	while (r < map_dim->row_max)
	{
		c = 0; 
		while (c < map_dim->column_max)
		{
			if (map[r][c] == 0)
				return 1;
			c++; 
		}
		r++; 
	}
	return 0;
}


void int_map2digs(int ** map, t_coord *en_coords, t_dim *map_dim)
{
	int value_to_surround = map[en_coords->row][en_coords->col];
	int level = 1;
	int * checked_coord_stack;
	// int was_marked = 1; 
	// int max = (map_dim->row_max > map_dim->column_max)? map_dim->row_max : map_dim->column_max; 
	while (is_any_empty(map, map_dim) && value_to_surround)
	{	
		checked_coord_stack = init_arr_coord(map_dim, 2);
		mark_cell(level, map, en_coords, map_dim, &checked_coord_stack);
		check_mark_neibours(&level, map, en_coords, map_dim, value_to_surround, &checked_coord_stack);
	//	print2d_int_array(map, map_dim);
	//	ft_printf("\n");
		level++; 
		free(checked_coord_stack);
	}
}


int ** convert_map_2_int_map(char **char_map, t_dim *map_dim, int enemy)
{
	int row = 0;
	int col = 0; 
	t_coord *en_coords = (t_coord *)malloc(sizeof(t_coord));
	en_coords->row = -1;
	en_coords->col = -1; 

	int ** int_map = init_int_map(map_dim);

	while (row < map_dim->row_max)
	{
		col = 0;
		while (col < map_dim->column_max)
		{
			if (char_map[row][col] == 'o' || char_map[row][col] == 'O')
			{
				if (enemy == 'o' || enemy == 'O')
				{
					int_map[row][col] = -2; 
					en_coords->row = row;
					en_coords->col = col; 
				}
				else 
					int_map[row][col] = -1; 
			}
			else if (char_map[row][col] == 'x' || char_map[row][col] == 'X')
			{
				if (enemy == 'x' || enemy == 'X')
				{
					int_map[row][col] = -2; 
					en_coords->row = row;
					en_coords->col = col; 
				}
				else 
					int_map[row][col] = -1; 
			}
			else 
				int_map[row][col] = 0;
			col++;
		}
		row++;
	}
//	print2d_int_array(int_map, map_dim);
	if (en_coords->row > -1 && en_coords->col > -1)
		int_map2digs(int_map, en_coords, map_dim);
	free(en_coords);
	return (int_map);
}



#include <fcntl.h>
int main(int ac, char ** av)
{
	ac = 0;
	av = 0;
	char * str = 0; 
	// int fd = 0;
	int fd;
	int me = 0;
	int enemy = 0; 

	t_filler * filler; 
	int *my_coord;
	int score; 
	
	fd = open("test.txt", O_RDONLY); 

	get_next_line(fd, &str);
	if (!get_num_players(str, &me, &enemy))
		error("reading player num");

	int i = 0; 
	while (i < 4)
	{
		score = 0; 
		filler = init_struct(); 
		get_next_line(fd, &str);
		if (!get_map_dim(str, filler))
			error("reading map dimensions");
		get_map(fd, filler);
		get_next_line(fd, &str);
		if (!get_token_dim(str, filler))
			error("reading token dimensions");
		get_token(fd, filler);

		filler->token->token_coord = convert_token2coord(filler->token->token_dim->row_max, filler->token->token_dim->column_max, filler->token->char_token);
		filler->int_map = convert_map_2_int_map(filler->char_map, filler->map_dim, enemy);
		
		my_coord = init_arr_coord(filler->map_dim, 2);

		add_my_coords(&my_coord, filler->int_map, filler->map_dim);
		
		//print2d_int_array(filler->int_map, filler->map_dim);
		ft_printf("\n\n Token_coord\n");
		print_int_arr(filler->token->token_coord, filler->token->token_coord[0]);
		ft_printf("\n\n my-coord\n");
		print_int_arr(my_coord, my_coord[0]);

		ft_printf("\n\n");

		score = put_first_token(filler->int_map, filler->map_dim, filler->token->token_coord, my_coord);
		cleanup(filler);
		free(my_coord);
		if (score == 0)
			break; 

		// system("leaks obuksha.filler");
		i++;
		//print2d_int_array(filler->int_map, filler->map_dim);
		
		}
		close(fd);
	
		
	
	return 0;


}
