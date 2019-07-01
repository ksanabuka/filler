


t_coord take_shortest_path(t_coord my_coord, t_coord en_coord, t_token token, int ** map)
{
    // try to  put token on all possible positions on each my cell; select one of best one. 
    // same scoring: close area

typedef struct  s_coord
{
    int row;
    int col;
}   t_coord;
    
    
typedef struct  s_token
{
    int *token_coord;
    int len_token_coord;
}   t_token;

int calc_path_token_on_map(int my_row, int my_col, int t_row, int t_col, int tl, int * tc, int ** map)
{
    int res = 0;
    int i = 0;

    int t_r_corellation;
    int t_c_corellation; 

   
    res = 

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
            res+= tc[t_r_corellation][t_c_corellation];
        }
        i = i + 2; 

    }
}