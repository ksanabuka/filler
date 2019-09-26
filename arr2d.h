
#ifndef arr2d_h
#define arr2d_h

typedef struct arr2d {
    int num_cols;
    int num_rows;
    int *arr;
} t_arr2d;

struct arr2d createArr2d(int rows, int cols);
void arr2dDispose(struct arr2d arr);
int arr2dGetItemAt(struct arr2d arr, int r, int c);
void arr2dSetItemAt(struct arr2d arr, int val, int r, int c);

#endif