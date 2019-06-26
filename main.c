// gcc -Wall -Werror -Wextra -g -fsanitize=address ./inc/gnl/get_next_line.c main.c -L ./inc/gnl/libft -lft -L ./inc/ft_printf -lftprintf -I ./inc/ft_printf/parser.h   -I./inc/gnl -I./inc/gnl/libft


#include "inc/gnl/get_next_line.h"
#include "inc/gnl/libft/libft.h"
#include "inc/ft_printf/parser.h"

#include <stdio.h>

int main(int ac, char ** av)
{
	ac = 0;
	av = 0;

	char * str; 

	get_next_line(0, &str);
	ft_printf("printing line... %s\n", str);
	
	return 0;
}
