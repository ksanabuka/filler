// gcc -Wall -Werror -Wextra -g -fsanitize=address ./inc/gnl/get_next_line.c main.c solver.c -L ./inc/gnl/libft -lft -L ./inc/ft_printf -lftprintf -I ./inc/ft_printf/parser.h   -I./inc/gnl -I./inc/gnl/libft -o obuksha.filler
//./filler_vm -f maps/map00 -p1 players/abanlin.filler -p2 players/champely.filler -sjk
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
		ft_printf("We are here\n");
	}
}

int get_num_players(char *s, t_filler * filler)
{
	if ((*(s + 10) != '1') && (*(s + 10) != '2'))
		return (0); 
	filler->me = (*(s + 10) == '1')? -1 : -2;
	filler->enemy = (*(s + 10) == '1')? -2 : -1;
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
	print_2d_map(filler->char_map, filler->map_dim->row_max);
}

void get_token(int fd, t_filler * filler)
{
	filler->token->char_token = char_map_init(filler->token->token_dim->row_max, filler->token->token_dim->column_max);
	int i = 0;
	char *str = 0;
	ft_printf("%s\n", str);
	while (i < filler->token->token_dim->row_max)
	{
		get_next_line(fd, &str);
		filler->token->char_token[i] = ft_strcpy(filler->token->char_token[i], str);
		i++;
	}
	print_2d_map(filler->token->char_token, filler->token->token_dim->row_max);
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
	free2darray(filler->char_map, filler->map_dim->row_max);
	free2darray(filler->token->char_token, filler->token->token_dim->row_max);
	free(filler->token->token_dim);
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


int mark1cell(int level, int ** map, t_coord *coords, t_dim *map_dim)
{
	int was_marked = 0; 
	if ((coords->row + level <  map_dim->row_max) && (map[coords->row + level][coords->col] == 0))
	{
		map[coords->row + level][coords->col] = level;
		was_marked++;
	}
	if ((coords->row - level >=  0) && (map[coords->row - level][coords->col] == 0))
	{	
		map[coords->row - level][coords->col] = level; 
		was_marked++;
	}
	if ((coords->col + level <  map_dim->column_max) && (map[coords->row][coords->col + level] == 0))
	{	
		map[coords->row][coords->col + level] = level;
		was_marked++;
	}

	if ((coords->col - level >=  0) && (map[coords->row][coords->col - level] == 0))
	{	
		map[coords->row][coords->col - level] = level; 
		was_marked++;
	}
	
	if ((coords->row + level <  map_dim->row_max) && (coords->col - level >= 0)\
		&& (map[coords->row + level][coords->col - level] == 0))
	{
		map[coords->row + level][coords->col - level] = level;
		was_marked++;
	}
	
	if ((coords->row + level <  map_dim->row_max) && (coords->col + level < map_dim->column_max)\
		&& (map[coords->row + level][coords->col + level] == 0))
	{
		map[coords->row + level][coords->col + level] = level;
		was_marked++;
	}

	if ((coords->row - level >= 0) && (coords->col - level >= 0)\
		&& (map[coords->row - level][coords->col - level] == 0))
	{
		map[coords->row - level][coords->col - level] = level;
		was_marked++;
	}

	if ((coords->row - level >= 0) && (coords->col + level < map_dim->column_max)\
		&& (map[coords->row - level][coords->col + level] == 0))
	{
		map[coords->row - level][coords->col + level] = level;
		was_marked++;
	}

return was_marked;
}

void check_mark_neibours(int *level, int ** map, t_coord *coords, t_dim *map_dim, int value_to_surround)
{
	int was_marked = 1;
	t_coord newcoord; 

		if ((coords->row + *level <  map_dim->row_max) && (map[coords->row + *level][coords->col] == value_to_surround))
		{
			newcoord.row = coords->row + *level;
			newcoord.col = coords->col; 
			was_marked+= mark1cell(*level, map, &newcoord, map_dim);
			check_mark_neibours(level, map, &newcoord, map_dim, value_to_surround); 
		}
		if ((coords->row - *level >=  0) && (map[coords->row - *level][coords->col] == value_to_surround))
		{
			newcoord.row = coords->row - *level;
			newcoord.col = coords->col; 
			was_marked+= mark1cell(*level, map, &newcoord, map_dim);
			check_mark_neibours(level, map, &newcoord, map_dim, value_to_surround); 
		}
		
		if ((coords->col + *level <  map_dim->column_max) && (map[coords->row][coords->col + *level] == value_to_surround))
		{
			newcoord.row = coords->row;
			newcoord.col = coords->col + *level; 
			was_marked+= mark1cell(*level, map, &newcoord, map_dim);
			check_mark_neibours(level, map, &newcoord, map_dim, value_to_surround); 
		}	
		if ((coords->col - *level >=  0) && (map[coords->row][coords->col - *level] == value_to_surround))
		{
			newcoord.row = coords->row;
			newcoord.col = coords->col - *level; 
			was_marked+= mark1cell(*level, map, &newcoord, map_dim);
			check_mark_neibours(level, map, &newcoord, map_dim, value_to_surround); 
		}	
		if ((coords->row + *level <  map_dim->row_max) && (coords->col - *level >= 0)\
			&& (map[coords->row + *level][coords->col - *level] == value_to_surround))
		{
			newcoord.row = coords->row + *level;
			newcoord.col = coords->col - *level; 
			was_marked+= mark1cell(*level, map, &newcoord, map_dim);
			check_mark_neibours(level, map, &newcoord, map_dim, value_to_surround); 
		}	
		if ((coords->row + *level <  map_dim->row_max) && (coords->col + *level < map_dim->column_max)\
			&& (map[coords->row + *level][coords->col + *level] == value_to_surround))
		{
			newcoord.row = coords->row + *level;
			newcoord.col = coords->col + *level; 
			was_marked+= mark1cell(*level, map, &newcoord, map_dim);
			check_mark_neibours(level, map, &newcoord, map_dim, value_to_surround); 
		}	
		if ((coords->row - *level >= 0) && (coords->col - *level >= 0)\
			&& (map[coords->row - *level][coords->col - *level] == value_to_surround))
		{
			newcoord.row = coords->row - *level;
			newcoord.col = coords->col - *level; 
			was_marked+= mark1cell(*level, map, &newcoord, map_dim);
			check_mark_neibours(level, map, &newcoord, map_dim, value_to_surround); 
		}	
		if ((coords->row - *level >= 0) && (coords->col + *level < map_dim->column_max)\
			&& (map[coords->row - *level][coords->col + *level] == value_to_surround))
		{
			newcoord.row = coords->row - *level;
			newcoord.col = coords->col + *level; 
			was_marked+= mark1cell(*level, map, &newcoord, map_dim);
			check_mark_neibours(level, map, &newcoord, map_dim, value_to_surround); 
		}	
}

void int_map2digs(int ** map, t_coord *en_coords, t_dim *map_dim)
{
	int value_to_surround = map[en_coords->row][en_coords->col];
	int value = 1;

	mark1cell(value, map, en_coords, map_dim);
	print2d_int_array(map, map_dim);
	check_mark_neibours(&value, map, en_coords, map_dim, value_to_surround);
	print2d_int_array(map, map_dim);
}


int ** convert_map_2_int_map(char **char_map, t_dim *map_dim, int enemy)
{
	int row = 0;
	int col = 0; 
	t_coord *en_coords = (t_coord *)malloc(sizeof(t_coord));

	int ** int_map = init_int_map(map_dim);

	while (row < map_dim->row_max)
	{
		col = 0;
		while (col < map_dim->column_max)
		{
			if (char_map[row][col] == 'o' || char_map[row][col] == 'O')
			{
				if (enemy == -1)
				{
					int_map[row][col] = -1; 
					en_coords->row = row;
					en_coords->col = col; 
				}
				else 
					int_map[row][col] = -2; 
			}
			else if (char_map[row][col] == 'x' || char_map[row][col] == 'X')
			{
				if (enemy == -1)
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
	print2d_int_array(int_map, map_dim);
	int_map2digs(int_map, en_coords, map_dim);
	return (int_map);
}




int main(int ac, char ** av)
{
	ac = 0;
	av = 0;
	char * str = 0; 
	int fd;
	t_filler * filler = init_struct(); 

	if ((fd = open("test.txt", O_RDONLY)) != -1)
	{
		get_next_line(fd, &str);
		if (!get_num_players(str, filler))
			error("reading player num");
		get_next_line(fd, &str);
		if (!get_map_dim(str, filler))
			error("reading map dimensions");
		get_map(fd, filler);
		get_next_line(fd, &str);
		if (!get_token_dim(str, filler))
			error("reading token dimensions");
		get_token(fd, filler);

		convert_token2coord(filler->token->token_dim->row_max, filler->token->token_dim->column_max, filler->token->char_token, &filler->token->token_coord);
	//	print_int_arr(filler->token->token_coord, 84);

		filler->int_map = convert_map_2_int_map(filler->char_map, filler->map_dim, filler->enemy);
		print2d_int_array(filler->int_map, filler->map_dim);

		cleanup(filler);
	}
	
	// ft_printf("%d %d\n", filler->enemy, filler->me);
	// ft_printf("%d %d\n", filler->map_dim->row_max, filler->map_dim->column_max);
	close(fd);
	return 0;
}
