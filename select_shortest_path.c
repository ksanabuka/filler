


t_coord take_shortest_path(t_coord my_coord, t_coord en_coord, t_token token, int ** map)
{
    // try to  put token on all possible positions on each my cell; select one of best one. 
    // same scoring: close area

int check_coord(int tr, int tc, int map_max_row, int map_max_col, int ** map)
{
    if ((tr >= map_max_row) || tr < 0 || (tc >= map_max_col) || tc < 0)
        return 0;
    return 1; 
}

int calc_path_token_on_map(int my_row, int my_col, int t_row, int t_col, int tl, int * tc, int ** map, int map_max_row, int map_max_col)
{
    int res = 0;
    int i = 0;

    int t_r_corellation;
    int t_c_corellation; 

    while (i < tl)
    {
        if (tc[i] == t_row && tc[i + 1] == t_col)
             ;
        else 
        {
            cur_row = tc[i];
            cur_col = tc[i + 1]; 
            t_r_corellation = cur_row - t_row + my_row; 
            t_c_corellation = cur_col - t_col + my_col;
            if (check_coord(t_r_corellation, t_c_corellation, map_max_row, map_max_col, map) && map[t_r_corellation][t_c_corellation] > 0)
                res+= map[t_r_corellation][t_c_corellation];
            else 
                return 0; 
        }
        i = i + 2; 

    }
}