#include "state.h"

#define INAROW 3

#define min(a,b) ((a)<(b) ? (a) : (b))

Piece winner(Field *board);
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

    //Done test
    Field stateBoard2 = {.board={
        NO_PIECE, NO_PIECE, Y       , NO_PIECE,
        NO_PIECE, X       , Y       , NO_PIECE,
        X       , Y       , Y       , NO_PIECE,
    }};
    printf("\n");
    Piece wn = winner(&stateBoard2);
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

Piece winner(Field *board_field) {

    for(int i=0;i<WIDTH;i++) {
        int crow = 0;
        Piece f = NO_PIECE;
        for(int j=0;j<HEIGHT;j++) {
           Piece nf = get_cell(i, j, board_field);
           int match = f == nf; 
           crow = nf==NO_PIECE ? 0 : (crow+match)*match;
           f = nf;
           if(crow+1 == INAROW)
               return f;
        }
    }

    for(int i=0;i<HEIGHT;i++) {
        int crow = 0;
        Piece f = NO_PIECE;
        for(int j=0;j<WIDTH;j++) {
           Piece nf = get_cell(j, i, board_field);
           int match = f == nf; 
           crow = nf==NO_PIECE ? 0 : (crow+match)*match;
           f = nf;
           if(crow+1 == INAROW)
               return f;
        }
    }

    for(int i=0;i<HEIGHT;i++) {
        int crow = 0;
        Piece f = NO_PIECE;
        for(int j=0;j<min(HEIGHT-i, WIDTH);j++) {
            Piece nf = get_cell(j, i+j, board_field);
            int match = f == nf && f != NO_PIECE; 
            int crow = (crow+match)*match;
            f = nf;
            if(crow+1 == INAROW)
                return f;
        }
    }
    for(int i=1;i<WIDTH;i++) {
        int crow = 0;
        Piece f = NO_PIECE;
        for(int j=0;j<min(HEIGHT, WIDTH-i);j++) {
            Piece nf = get_cell(j, i+j, board_field);
            int match = f == nf && f != NO_PIECE; 
            int crow = (crow+match)*match;
            f = nf;
            if(crow+1 == INAROW)
                return f;
        }
    }

    for(int i=0;i<HEIGHT;i++) {
        int crow = 0;
        Piece f = NO_PIECE;
        int stx = WIDTH-1;
        int sty = i;
        for(int j=0;j<min(HEIGHT-sty, WIDTH);j++) {
            Piece nf = get_cell(stx-j, sty+j, board_field);
            int match = f == nf && f != NO_PIECE; 
            int crow = (crow+match)*match;
            f = nf;
            if(crow+1 == INAROW)
                return f;
        }
    }
    for(int i=1;i<WIDTH;i++) {
        int crow = 0;
        Piece f = NO_PIECE;
        int stx = i;
        int sty = 0;
        for(int j=0;j<min(HEIGHT, stx+1);j++) {
            Piece nf = get_cell(stx-j, sty+j, board_field);
            int match = f == nf && f != NO_PIECE; 
            int crow = (crow+match)*match;
            f = nf;
            if(crow+1 == INAROW)
                return f;
        }
    }

}
