#include <assert.h>
#include "state.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>



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
    if(res!=ct) {
        printf("Real: %d\n", ct);
        printf("Conunted: %d\n", res);
        print_field(lf);
        assert(0);
    }
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
}
int main(void) {
    test_eval();
    test_done();
    return 0;
}
