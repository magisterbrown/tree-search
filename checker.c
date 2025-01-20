#include "state.h"

int check_line_done(LField *board, PointVec pv, Piece pic) 
{
    int xc = pv.x;
    int yc = pv.y;
    int latest = 0, longest = 0;
    while(xc<board->width && yc<board->height) {
        int eq = get_cell(xc, yc, board) == pic;
        latest = (latest*eq)+eq;
        longest = latest>longest ? latest : longest;
        xc+=pv.dx;
        yc+=pv.dy;
    }
    return longest;
}

int check_line_eval(LField *board, PointVec pv, Piece pic, int full_len) 
{
    int xc = pv.x;
    int yc = pv.y;
    int latest = 0, longest = 0, lfinishable = 0;
    while(xc<board->width && yc<board->height) {
        int eq = get_cell(xc, yc, board) == pic;
        int matching = eq || get_cell(xc, yc, board) == NO_PIECE;
        latest = (latest*matching)+eq;
        lfinishable=(lfinishable*matching)+matching;
        if(lfinishable>=full_len)
            longest = latest>longest ? latest : longest;
        xc+=pv.dx;
        yc+=pv.dy;
    }
    return longest;
}
