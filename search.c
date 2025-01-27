#include <assert.h>
#include "state.h"

#define NAN 0.0/0.0

#define max(a, b) a>b ? a : b
#define min(a, b) a<b ? a : b
float *search(float res[], GameContext gm, SearchContext sc) {
    LField* lf = gm.field;  
    Piece pic = gm.pic;
    int n_cols = lf->width;
    sc.max_depth=3;
    TreeNode *branch = calloc(sc.max_depth, sizeof(TreeNode));
    branch[0].state_value = NAN;
    for(int i=0;i<sc.max_depth;i++)
        branch[i].idx = -1;
    int depth = 0;
    int ct = 0;
    for(;;) {
        do {
            if(depth == 0 && branch[depth].idx>=0)
                res[branch[depth].idx] = branch[depth].state_value;
            branch[depth].idx++;
            branch[depth].state_value = NAN;
        } while(get_cell(branch[depth].idx, 0, lf) != NO_PIECE && branch[depth].idx < n_cols);

        if(branch[depth].idx == n_cols) {
            branch[depth].idx=-1;
            depth--;
            if(depth == -1)
                break;
            undo_move(lf, branch[depth].idx);
            continue;
        }

        Piece fig = depth%2 ? flip(pic) : pic;
        do_move(lf, branch[depth].idx, fig);
        int done = field_done(lf, fig, gm.inarow);
        int draw = 1;// ct == 27 && done
        for(int i=0;i<n_cols;i++) 
            draw &= get_cell(i, 0, lf) != NO_PIECE;

        if(done || depth == sc.max_depth-1 || draw) {
            float value = done ? 999*(fig==X)-999*(fig==Y) : 0;

            if(branch[0].idx == 0 ) {
                ct++;
                print_field(lf);
                printf("Vlaue %f\n", value);
            }
            //fig = flip(fig);
            for(int i=depth;i>=0;i--) {
                float old_value = branch[i].state_value;
                if(i==0 && gm.pic != fig)
                    printf("ERRORR\n");

                branch[i].state_value = fig==Y ? min(branch[i].state_value, value) : max(branch[i].state_value, value);
                fig = flip(fig);
                if(branch[i].state_value==old_value)
                    break;
            }

            undo_move(lf, branch[depth].idx);
        } else { 
            depth++;
        }
    }
    free(branch); 
    return res; 
}
