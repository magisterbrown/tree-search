#include <assert.h>
#include "state.h"

#define NAN 0.0/0.0

#define max(a, b) a>b ? a : b
#define min(a, b) a<b ? a : b

typedef struct {
    float min;
    float max;
} Limits;

static int posex = 0;
float minimax(LField *lf, Piece fig, Limits lim, int depth, int inarow) 
{
    int done = field_done(lf, fig, inarow);
    if(done) {
        posex++;
        return 999*(fig==X)-999*(fig==Y);
    }

    int draw = 1;
    for(int i=0;i<lf->width;i++) 
        draw &= get_cell(i, 0, lf) != NO_PIECE;
    if(draw) {
        posex++;
        return 0;
    }

    if(depth == 0){
        posex++;
        return 0;
    }



    float value = NAN;
    Piece next = flip(fig);
    for(int i=0; i<lf->width; i++) {
        if(get_cell(i, 0, lf) == NO_PIECE) {
            do_move(lf, i, next);
            float child = minimax(lf, next, lim, depth-1, inarow);
            value = next == X ? max(value, child) : min(value, child);
            int prune = 0;
            if(next == X) {
                prune = value > lim.max;
                lim.min = max(lim.min, value);
            } else {
                prune = value < lim.min;
                lim.max = min(lim.max, value);
            }
            undo_move(lf, i);
            if(prune)
                return value;
        }
    }
    //print_field(lf);
    return value;
}
float *search(float res[], GameContext gm, SearchContext sc) {
    LField* lf = gm.field;  
    Piece pic = gm.pic;
    int depth = 0;
    posex = 0;
    for(int i=0; i<lf->width; i++) {
        res[i] = NAN;
        if(get_cell(i, 0, gm.field) == NO_PIECE) {
            do_move(lf, i, gm.pic);
            res[i] = minimax(gm.field, gm.pic, (Limits){-999, 999}, sc.max_depth-1, gm.inarow);
            undo_move(lf, i);
        }
    }
    //printf("Positions explored: %d\n", posex);
    return res;
}
