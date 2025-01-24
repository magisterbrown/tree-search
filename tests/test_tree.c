#include "state.h"
#include <alloca.h>
#define NAN 0.0/0.0

typedef struct {
    int n_cols;
    int depth;
} SearchConfig;

typedef struct TreeNode {
    int idx;
    float state_value;
} TreeNode;
#define INAROW 3
 
void stopper() {}

float *search(float res[], LField *lf, int max_depth, Piece pic) {
    int n_cols = lf->width;
    TreeNode *branch = calloc(max_depth, sizeof(TreeNode));
    branch[0].state_value = NAN;
    for(int i=0;i<max_depth;i++)
        branch[i].idx = -1;
    stopper();
    int depth = 0;
    for(;;) {
        do {
            branch[depth].idx++;
            branch[depth].state_value = NAN;
        } while(get_cell(branch[depth].idx, 0, lf) != NO_PIECE && branch[depth].idx < n_cols);

        if(branch[depth].idx == n_cols) {
            branch[depth].idx=-1;
            depth--;
            if(depth == -1)
                return 0;
            undo_move(lf, branch[depth].idx);
            continue;
        }
        do_move(lf, branch[depth].idx, depth%2 ? Y : X);
        if(depth == max_depth-1 ) {
            stopper();
            print_field(lf);
            undo_move(lf, branch[depth].idx);
        } else { 
            depth++;
        }
    }

   return res; 
}
#define SZ 5
int main(void) {
       LField *lf = create_lfield(SZ, SZ);
       print_field(lf);
       float *b = search((float []){ [0 ... SZ] = 0}, lf, 8, X);
       free(lf);
}
