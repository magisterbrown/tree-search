#include "state.h"

int check_line_done(LField *board, PointVec pv, Piece pic) 
{
    int xc = pv.x;
    int yc = pv.y;
    int latest = 0, longest = 0;
    while(xc<board->width && xc >= 0 && yc<board->height && yc >= 0) {
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
    while(xc<board->width && xc >= 0 && yc<board->height && yc>=0) {
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

int field_done(LField *lf, Piece fig, int ln)
{
    int done = 0;
    for(int x=0;x<lf->width;x++) {
       done |= check_line_done(lf, (PointVec){x, 0, 0, 1},  fig) >= ln; 
       done |= check_line_done(lf, (PointVec){x, 0, 1, 1},  fig) >= ln; 
       done |= check_line_done(lf, (PointVec){x, 0, -1, 1}, fig) >= ln; 
       if(done)
           return 1;
    }
    for(int y=0;y<lf->height;y++) {
       done |= check_line_done(lf, (PointVec){0, y, 1, 0},            fig) >= ln; 
       done |= check_line_done(lf, (PointVec){0, y, 1, 1},            fig) >= ln; 
       done |= check_line_done(lf, (PointVec){lf->width-1, y, -1, 1}, fig) >= ln; 
       if(done)
           return 1;
    }
    return 0;
}

float field_eval(LField *lf, int ln)
{
    Piece figs[2] = {X, Y};
    int maxr[2] = {0, 0};
    int tmp;
    for(int i=0;i<2;i++) { 
        for(int x=0;x<lf->width;x++) {
            tmp = check_line_eval(lf, (PointVec){x, 0, 0, 1}, figs[i], ln);
            maxr[i] = maxr[i] < tmp ? tmp : maxr[i];     
            tmp = check_line_eval(lf,(PointVec) {x, 0, 1, 1}, figs[i], ln);
            maxr[i] = maxr[i] < tmp ? tmp : maxr[i];     
            tmp = check_line_eval(lf,(PointVec) {x, 0, -1, 1}, figs[i], ln);
            maxr[i] = maxr[i] < tmp ? tmp : maxr[i];     
        }
        for(int y=0;y<lf->height;y++) {
            tmp = check_line_eval(lf,(PointVec) {0, y, 0, 1}, figs[i], ln);
            maxr[i] = maxr[i] < tmp ? tmp : maxr[i];     
            tmp = check_line_eval(lf,(PointVec) {0, y, 1, 1}, figs[i], ln);
            maxr[i] = maxr[i] < tmp ? tmp : maxr[i];     
            tmp = check_line_eval(lf,(PointVec) {lf->width-1, y, -1, 1}, figs[i], ln);
            maxr[i] = maxr[i] < tmp ? tmp : maxr[i];     
        }
    }
    return maxr[0]-maxr[1];
}
