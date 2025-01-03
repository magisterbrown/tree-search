#include <assert.h>
#include "state.h"
#include <stdlib.h>
#include <string.h>

int main(void) {
    //LField *lf = create_lfield(1,2);
    LField *lf = create_lfield(4,4);
    //lf->board[15] = X;
    //LField *lfn = create_lfield(4,4);
    free(lf);
    //lfn = create_lfield(4,4);
    return 0;
}
