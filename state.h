#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define WIDTH 4
#define HEIGHT 3

typedef enum Piece: unsigned char {
    NO_PIECE,
    X,
    Y,
} Piece;

#define flip(fig) fig == X ? Y : X

typedef struct LField {
    int width;
    int height;
    Piece board[];
} LField;
#define create_lfield(width, height) memcpy(calloc(1,sizeof(LField)+width*height),&(LField){width,height}, sizeof(LField));
#define get_cell(x,y,field) (field)->board[y*(field->width)+x]


typedef struct{
    unsigned int x;
    unsigned int y;
    int dx;
    int dy;
} PointVec;

typedef struct {
    int n_cols;
    int depth;
} SearchConfig;


int check_line_done(LField *board, PointVec pv, Piece pic);
int check_line_eval(LField *board, PointVec pv, Piece pic, int full_len);
int field_done(LField *lf, Piece fig, int ln);
float  field_eval(LField *lf, int ln);

void do_move(LField *curr, int col, Piece fig);
void undo_move(LField *curr, int col); 
void print_field(LField *curr); 


typedef struct TreeNode {
    int idx;
    float state_value;
} TreeNode;
typedef struct {
    LField *field;
    Piece pic;
    int inarow;
} GameContext;
typedef struct {
    int max_depth;
} SearchContext;

float *search(float res[], GameContext gm, SearchContext sc);

