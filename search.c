#include <assert.h>
#include "state.h"

#define NAN 0.0/0.0

#define max(a, b) a>b ? a : b
#define min(a, b) a<b ? a : b
float minimax(LField *lf, Piece fig, int depth, int inarow) 
{
    int done = field_done(lf, fig, inarow);
    if(done)
        return 999*(fig==X)-999*(fig==Y);

    int draw = 1;
    for(int i=0;i<lf->width;i++) 
        draw &= get_cell(i, 0, lf) != NO_PIECE;
    if(draw)
        return 0;

    if(depth == 0)
        return 0;



    float value = NAN;
    Piece next = flip(fig);
    for(int i=0; i<lf->width; i++) {
        if(get_cell(i, 0, lf) == NO_PIECE) {
            do_move(lf, i, next);
            float child = minimax(lf, next, depth-1, inarow);
            value = next == X ? max(value, child) : min(value, child);
            undo_move(lf, i);
        }
    }
    print_field(lf);
    return value;
}
float *search(float res[], GameContext gm, SearchContext sc) {
    LField* lf = gm.field;  
    Piece pic = gm.pic;
    sc.max_depth=6;
    int depth = 0;
    for(int i=0; i<lf->width; i++) {
        res[i] = NAN;
        if(get_cell(i, 0, gm.field) == NO_PIECE) {
            do_move(lf, i, gm.pic);
            res[i] = minimax(gm.field, gm.pic, sc.max_depth-1, gm.inarow);
            undo_move(lf, i);
        }
    }
    return res;
}
