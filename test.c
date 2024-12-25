#include "state.h"

#define INAROW 3

#define min(a,b) ((a)<(b) ? (a) : (b))
#define max(a,b) ((a)>(b) ? (a) : (b))

Piece winner(Field *board);
Piece check_line(Field *board, int xst, int yst, int dx, int dy);
int main(void)
{
    Field stateBoard1 = {.board={
        NO_PIECE, NO_PIECE, NO_PIECE, NO_PIECE,
        NO_PIECE, NO_PIECE, NO_PIECE, NO_PIECE,
        NO_PIECE, NO_PIECE, NO_PIECE, NO_PIECE,
    }};


    //FULL test
    stateBoard1 = (Field){.board={
        X       , Y       , X       , Y       ,
        NO_PIECE, NO_PIECE, NO_PIECE, NO_PIECE,
        NO_PIECE, NO_PIECE, NO_PIECE, NO_PIECE,
    }};

    int full = 1;
    for(int i=0;i<WIDTH;i++) {
        full &= stateBoard1.board[i]!=NO_PIECE;
    }
    printf("Full %d\n", full);
    print_field(&stateBoard1);

    printf("\n");
    Piece wn = winner(&stateBoard1);
    if(wn==X) 
        printf("x winner");
    else if(wn==Y) 
        printf("y winner");
    else 
        printf("no winner");
    printf("\n");
    print_field(&stateBoard1);

    //Done test
    Field stateBoard2 = {.board={
        NO_PIECE, NO_PIECE, Y       , NO_PIECE,
        NO_PIECE, X       , Y       , NO_PIECE,
        X       , Y       , Y       , NO_PIECE,
    }};
    printf("\n");
    wn = winner(&stateBoard2);
    if(wn==X) 
        printf("x winner");
    else if(wn==Y) 
        printf("y winner");
    else 
        printf("no winner");
    printf("\n");
    print_field(&stateBoard2);

    stateBoard2 = (Field){.board={
        NO_PIECE, NO_PIECE, Y       , NO_PIECE,
        NO_PIECE, X       , X       , X       ,
        X       , Y       , Y       , NO_PIECE,
    }};

    printf("\n");
    wn = winner(&stateBoard2);
    if(wn==X) 
        printf("x winner");
    else if(wn==Y) 
        printf("y winner");
    else 
        printf("no winner");
    printf("\n");
    print_field(&stateBoard2);

    stateBoard2 = (Field){.board={
        NO_PIECE, X       , Y       , NO_PIECE,
        NO_PIECE, X       , X       , Y       ,
        X       , Y       , Y       , X       ,
    }};

    printf("\n");
    wn = winner(&stateBoard2);
    if(wn==X) 
        printf("x winner");
    else if(wn==Y) 
        printf("y winner");
    else 
        printf("no winner");
    printf("\n");
    print_field(&stateBoard2);


    Field stateBoard3 = {.board={
        NO_PIECE, X       , X       , NO_PIECE,
        NO_PIECE, X       , Y       , Y       ,
        X       , Y       , Y       , X       ,
    }};

    printf("\n");
    wn = winner(&stateBoard2);
    if(wn==X) 
        printf("x winner");
    else if(wn==Y) 
        printf("y winner");
    else 
        printf("no winner");
    printf("\n");
    print_field(&stateBoard2);
    //Eval test

}       
int check_line_eval(Field *board, int xst, int yst, int dx, int dy, Piece pic) {
    int best_full = 0;

    int fullrow = 0;
    int emprow = 0;

    while(1) {
        if(xst<0 || xst>=WIDTH || yst<0 || yst>=HEIGHT)
            return NO_PIECE;
        Piece nf = get_cell(xst, yst, board);
        if(nf == pic) 
            fullrow, emprow = 0;
        int match = nf == flip(pic); 
        fullrow = (fullrow+match)*match;

        int rowmatch = match || nf == NO_PIECE; 
        emprow = (emprow+rowmatch)*rowmatch;

        xst+=dx;
        yst+=dy;
        if(emprow>=INAROW){
            best_full = max(best_full, fullrow);
        }
    }
}
Piece check_line(Field *board, int xst, int yst, int dx, int dy) {
    Piece f = NO_PIECE;
    int crow = 0;
    while(1) {
        if(xst<0 || xst>=WIDTH || yst<0 || yst>=HEIGHT)
            return NO_PIECE;
        Piece nf = get_cell(xst, yst, board);
        int match = f == nf; 
        crow = nf==NO_PIECE ? 0 : (crow+match)*match;
        f = nf;
        xst+=dx;
        yst+=dy;
        if(crow+1 == INAROW)
            return f;
    }
}
Piece winner(Field *board_field) {

    for(int i=0;i<WIDTH;i++) {
        Piece res = check_line(board_field, i, 0, 0, 1);
        if(res)
            return res;
    }

    for(int i=0;i<HEIGHT;i++) {
        Piece res = check_line(board_field, 0, i, 1, 0);
        if(res)
            return res;
    }

    for(int i=0;i<HEIGHT;i++) {
        Piece res = check_line(board_field, 0, i, 1, 1);
        if(res)
            return res;
    }
    for(int i=1;i<WIDTH;i++) {
        Piece res = check_line(board_field, i, 0, 1, 1);
        if(res)
            return res;
    }

    for(int i=0;i<HEIGHT;i++) {
        Piece res = check_line(board_field, WIDTH-1, i, -1, 1);
        if(res)
            return res;
    }
    for(int i=0;i<WIDTH-1;i++) {
        Piece res = check_line(board_field, i, 0, -1, 1);
        if(res)
            return res;
    }
    return NO_PIECE;

}
