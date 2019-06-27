// gcc -Wall -Werror -Wextra -g -fsanitize=address ./inc/gnl/get_next_line.c main.c -L ./inc/gnl/libft -lft -L ./inc/ft_printf -lftprintf -I ./inc/ft_printf/parser.h   -I./inc/gnl -I./inc/gnl/libft -o obuksha.filler
//./filler_vm -f maps/map00 -p1 players/abanlin.filler -p2 players/champely.filler -sjk
#include <fcntl.h>
#include "inc/gnl/get_next_line.h"
#include "inc/gnl/libft/libft.h"
#include "inc/ft_printf/parser.h"
#include <stdlib.h>
#include <stdio.h>

typedef struct  s_filler
{
    int me;
    int enemy;
    
    int row_max;
    int column_max;

    char ** charmap;
    int **intmap;
}				t_filler;


void	error(char *message)
{
	perror(message);
	exit(1);
}


int get_num_players(char *s, t_filler * filler)
{
	if ((*(s + 10) != '1') && (*(s + 10) != '2'))
		return (0); 
	filler->me = (*(s + 10) == '1')? 1 : 2;
	filler->enemy = (*(s + 10) == '1')? 2 : 1;
	return (1);
}

int get_dim(char *s, t_filler * filler)
{
	int len;

	if ((*(s + 8) <= '0') && (*(s + 8) > '9'))
		return (0); 
	filler->row_max = ft_atoi(s + 8);
	len = ft_strlen((ft_itoa(filler->row_max)));
	if ((*(s + 8 + 1 + len) <= '0') &&  (*(s + 8 + 1 + len) > '9'))
		return (0); 
	filler->column_max = ft_atoi(s + 8 + 1 + len);
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
	char ** charmap = (char**)malloc(sizeof(char *) * rows);
	int i = 0;
	while (i < rows)
	{
		charmap[i] = (char*)malloc(sizeof(char) * (columns + 1));
		charmap[i][columns] = '\0'; 
		i++; 
	}
	print_2d_map(charmap, rows);
	return (charmap);
}



void skip_map_row_enumeration(char **str)
{
	*str = *(str + 4); 
}

void get_map(int fd, t_filler * filler)
{
	filler->charmap = char_map_init(filler->row_max, filler->column_max);
	int i = 0;
	char *str;  
	while (i < filler->row_max)
	{
		get_next_line(fd, &str);

	}
}

int main(int ac, char ** av)
{
	ac = 0;
	av = 0;
	char * str = 0; 
	int fd;
	t_filler * filler = (t_filler *)malloc(sizeof(t_filler));

	if ((fd = open("test.txt", O_RDONLY)) != -1)
	{
		get_next_line(fd, &str);
		if (!get_num_players(str, filler))
		error("reading player num");
		get_next_line(fd, &str);
		if (!get_dim(str, filler))
		error("reading map dimensions");
		get_map(fd, filler);

	}
	
	// ft_printf("%d %d\n", filler->enemy, filler->me);
	// ft_printf("%d %d\n", filler->row_max, filler->column_max);
	close(fd);
	return 0;
}
