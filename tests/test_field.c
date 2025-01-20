#include <stdio.h>
#include <assert.h>
#include <time.h>
#include "state.h"

#define SZ 8
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
int field_eval(LField *lf, int ln)
{
    int max_x = 0;
    int max_y = 0;
    Piece figs[2] = {X, Y};
    int maxr[2] = {0, 0};
    int tmp
    for(int i=0;i<2;i++) { 
        for(int x=0;x<lf->width;x++) {
            tmp = check_line_eval(lf, {x, 0, 0, 1}, figs[i], ln);
            maxr[i] = maxr[i] < tmp ? tmp : maxr[i];     
            tmp = check_line_eval(lf, {x, 0, 1, 1}, figs[i], ln);
            maxr[i] = maxr[i] < tmp ? tmp : maxr[i];     
            tmp = check_line_eval(lf, {x, 0, -1, 1}, figs[i], ln);
            maxr[i] = maxr[i] < tmp ? tmp : maxr[i];     
        }
        for(int y=0;y<lf->height;y++) {
            tmp = check_line_eval(lf, {0, y, 0, 1}, figs[i], ln);
            maxr[i] = maxr[i] < tmp ? tmp : maxr[i];     
            tmp = check_line_eval(lf, {0, y, 1, 1}, figs[i], ln);
            maxr[i] = maxr[i] < tmp ? tmp : maxr[i];     
            tmp = check_line_eval(lf, {lf->width-1, y, -1, 1}, figs[i], ln);
            maxr[i] = maxr[i] < tmp ? tmp : maxr[i];     
        }
    }
    return maxr[0]-maxr[1];
}

int only_done(int rowl, int printer) 
{
    LField *lf = create_lfield(SZ, SZ);
    Piece fig = X;
    int done=0;
    for(int i=0;i<SZ&&!done;i++) {
        for(int j=0;j<SZ&&!done;j++) {
            if(rand()%2)
                fig = flip(fig);
            do_move(lf, rand()%SZ, fig);
            if(field_done(lf, fig, rowl) ){
                done=1;
            }
        }
    }
    if(!done)
        return 0;
    if(printer)
        print_field(lf);
    int ess = 0;
    for(int i=0;i<SZ;i++) {
        for(int j=0;j<SZ;j++) {
            get_cell(i, j, lf) = NO_PIECE;
            if(!field_done(lf, fig, rowl)) {
                get_cell(i,j,lf) = fig;
                ess++;
            }
        }
    }
    assert(ess==rowl);
    if(printer)
        print_field(lf);
}
void refill(int printer) {

    LField *lf = create_lfield(SZ, SZ);
    for(int i=0;i<SZ;i++) 
        for(int j=0;j<SZ;j++) 
            do_move(lf, j, X);
    if(printer)
        print_field(lf);
    for(int i=0;i<SZ;i++) 
        for(int j=0;j<SZ;j++) 
            assert(get_cell(i, j,lf) == X);

    for(int i=0;i<SZ;i++) 
        for(int j=0;j<SZ;j++) 
            undo_move(lf, j);
    if(printer)
        print_field(lf);

    for(int i=0;i<SZ;i++) 
        for(int j=0;j<SZ;j++) 
            assert(get_cell(i, j,lf) == NO_PIECE);

}

int main(void)
{
    srand(time(NULL));
    only_done(5, 1);
    refill(0);
}
