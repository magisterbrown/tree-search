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
#define max(a, b) a>b ? a : b
#define min(a, b) a<b ? a : b

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
                goto cleanup;
            undo_move(lf, branch[depth].idx);
            continue;
        }
        Piece fig = depth%2 ? Y : X;
        do_move(lf, branch[depth].idx, fig);
        int done = field_done(lf, fig, INAROW);
        if(done || depth == max_depth-1 ) {
            float value = done ? 999*(fig==X)-999*(fig==Y) : field_eval(lf, INAROW-1);
            stopper();
            for(int i=depth;i>=0;i--) {
                float old_value = branch[i].state_value;
                branch[i].state_value = i%2 ? min(branch[i].state_value, value) : max(branch[i].state_value, value);
                if(branch[i].state_value==old_value)
                    break;
            }


            print_field(lf);
            printf("Vlaue %f\n", value);
            undo_move(lf, branch[depth].idx);
        } else { 
            depth++;
        }
    }
cleanup:
    free(branch); 
    return res; 
}
#define SZ 5
int main(void) {
       LField *lf = create_lfield(SZ, SZ);
       print_field(lf);
       float *b = search((float []){ [0 ... SZ] = 0}, lf, 6, X);
       free(lf);
}
