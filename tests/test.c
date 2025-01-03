#include "state.h"

#define INAROW 3

#define min(a,b) ((a)<(b) ? (a) : (b))
#define max(a,b) ((a)>(b) ? (a) : (b))

Piece winner(Field *board);
Piece check_line(Field *board, int xst, int yst, int dx, int dy);
int eval_position(Field *board);
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
    printf("Value %d\n", eval_position(&stateBoard1));
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
    printf("Value %d\n", eval_position(&stateBoard2));
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
    printf("Value %d\n", eval_position(&stateBoard1));
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
    printf("Value %d\n", eval_position(&stateBoard1));
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
    printf("Value %d\n", eval_position(&stateBoard1));
    print_field(&stateBoard2);
    //Eval test

}       
