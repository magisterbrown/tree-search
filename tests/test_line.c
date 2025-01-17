#include <assert.h>
#include "state.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>


int check_line_done(LField *board, PointVec pv, Piece pic) 
{
    int xc = pv.x;
    int yc = pv.y;
    int latest, longest = 0;
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
    int latest, longest, lfinishable = 0;
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

#define WIDTH_TEST 30
void test_eval() 
{
    LField *lf = create_lfield(WIDTH_TEST, 1);
    for(int i=0;i<WIDTH_TEST;i++)
        get_cell(i,0,lf) = Y;
    int rowl = 12;
    int n = 10;
    int ct = 0;
    for(int i=rowl;i<rowl+n;i++) {
        int rann = rand()%2;
        ct += rann;
        get_cell(i,0,lf) = rann ? X : NO_PIECE;
    }
    int res = check_line_eval(lf, (PointVec){0, 0, 1, 0}, X, 4);
    assert(res == ct);
}
void test_done() 
{
    LField *lf = create_lfield(WIDTH_TEST, 1);
    int rowl = 12;
    int n = 5;
    for(int i=rowl;i<rowl+n;i++)
        get_cell(i,0,lf) = X;

    int res = check_line_done(lf, (PointVec){0, 0, 1, 0}, X);
    assert(res==n);
    free(lf);
}
int main(void) {
    //test_done();
    //test_eval();
    //lfn = create_lfield(4,4);
    return 0;
}
