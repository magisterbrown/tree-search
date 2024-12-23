#include "state.h"

#define INAROW 3

#define min(a,b) ((a)<(b) ? (a) : (b))

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
    
    for(int i=0;i<WIDTH;i++) {
        int crow = 0;
        Piece f = NO_PIECE;
        for(int j=0;j<HEIGHT;j++) {
           Piece nf = get_cell(i, j, &stateBoard2);
           int match = f == nf; 
           crow = nf==NO_PIECE ? 0 : (crow+match)*match;
           f = nf;
           if(crow+1 == INAROW)
               printf(f==X ? "x won" : "y won");
        }
    }
    printf("\n");
    print_field(&stateBoard2);

    stateBoard2 = (Field){.board={
        NO_PIECE, NO_PIECE, Y       , NO_PIECE,
        NO_PIECE, X       , X       , X       ,
        X       , Y       , Y       , NO_PIECE,
    }};

    for(int i=0;i<HEIGHT;i++) {
        int crow = 0;
        Piece f = NO_PIECE;
        for(int j=0;j<WIDTH;j++) {
           Piece nf = get_cell(j, i, &stateBoard2);
           int match = f == nf; 
           crow = nf==NO_PIECE ? 0 : (crow+match)*match;
           f = nf;
           if(crow+1 == INAROW)
               printf(f==X ? "x won" : "y won");
        }
    }
    printf("\n");
    print_field(&stateBoard2);

    stateBoard2 = (Field){.board={
        NO_PIECE, X       , Y       , NO_PIECE,
        NO_PIECE, X       , X       , Y       ,
        X       , Y       , Y       , X       ,
    }};

    for(int i=-HEIGHT+1;i<WIDTH;i++) {
        int crow = 0;
        Piece f = NO_PIECE;
        int x_st = i<0 ? 0 : i; 
        int y_st = i<0 ? HEIGHT+i : 0; 
        for(int j=0;j<min(WIDTH-x_st, HEIGHT-y_st);j++) {
            Piece nf = get_cell(x_st+j, y_st+j, &stateBoard2);
            int match = f == nf; 
            crow = nf==NO_PIECE ? 0 : (crow+match)*match;
            f = nf;
            if(crow+1 == INAROW)
                printf(f==X ? "x won" : "y won");
        }
    }
    printf("\n");
    print_field(&stateBoard2);

    stateBoard2 = (Field){.board={
        NO_PIECE, X       , X       , NO_PIECE,
        NO_PIECE, X       , Y       , Y       ,
        X       , Y       , Y       , X       ,
    }};

    for(int i=-HEIGHT+1;i<WIDTH;i++) {
        int crow = 0;
        Piece f = NO_PIECE;
        int x_st = i<0 ? WIDTH-1 : i; 
        int y_st = i<0 ? HEIGHT+i : 0; 
        int endd = min(x_st, HEIGHT-y_st);
        for(int j=0;j<min(x_st+1, HEIGHT-y_st);j++) {
            Piece nf = get_cell(x_st-j, y_st+j, &stateBoard2);
            int match = f == nf; 
            crow = nf==NO_PIECE ? 0 : (crow+match)*match;
            f = nf;
            if(crow+1 == INAROW)
                printf(f==X ? "x won" : "y won");
        }
    }
    printf("\n");
    print_field(&stateBoard2);
    //Eval test

}       
