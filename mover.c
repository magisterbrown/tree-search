#include "state.h"

void do_move(LField *curr, int col, Piece fig) 
{
   for(int y=curr->height-1;y>=0;y--) {
        if(curr->board[y*curr->width+col] == NO_PIECE) {
            curr->board[y*curr->width+col] = fig;
            break;
        }
   }
}

void undo_move(LField *curr, int col) 
{
    for(int y=0;y<curr->height;y++) {
        if(curr->board[y*curr->width+col] != NO_PIECE) {
            curr->board[y*curr->width+col] = NO_PIECE;
            break;
        }
    }
}

void print_field(LField *curr) 
{
    for(int y=0;y<curr->height;y++) {
        for(int x=0;x<curr->width;x++) {
            switch(curr->board[y*curr->width+x]) {
                case NO_PIECE: printf("0");break;
                case X:        printf("x");break;
                case Y:        printf("y");break;
            }
            if(x!=curr->width-1)
                printf(" ");
        }
        printf("\n");
    }
    printf("\n");
}
