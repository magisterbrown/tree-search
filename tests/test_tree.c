#include "state.h"
#define NAN 0.0/0.0

typedef struct {
    int n_cols;
    int depth;
} SearchConfig;

typedef struct TreeNode {
    float state_value;
    struct TreeNode *parrent;
    struct TreeNode *children[];
} TreeNode;

void stopper() {};

float *search(float res[], LField *lf, int max_depth, Piece pic) {
    int n_cols = lf->width;
    TreeNode *root = malloc(sizeof(TreeNode)+sizeof(TreeNode*)*n_cols);
    root->state_value = NAN;
    TreeNode *curr = root;
    int move_stack[lf->width*lf->height];
    int depth = 0;
    pic = flip(pic);
    for(;;) {
        if(depth == max_depth) {
            TreeNode *up_node = curr; 
            float leaf_v = 7;
            curr->state_value = leaf_v;
            Piece up_fig = pic;

             do {
                //up_fig = flip(pic);
                //use_max = !use_max;
                up_node = up_node->parrent;
                if(up_node->state_value != up_node->state_value) {
                    up_node->state_value = leaf_v;
                    continue;
                }
                else {
                }
                //float old_state_value = up_node->state_value;
                //if(up_fig==X) 
                //    up_node->state_value = up_node->state_value > leaf_v ? up_node->state_value : leaf_v;
                //else
                //    up_node->state_value = up_node->state_value < leaf_v ? up_node->state_value : leaf_v;
                //if(old_state_value == up_node->state_value)
                //    break;
            } while(up_node->parrent != NULL);

            stopper();
            undo_move(lf, move_stack[depth-1]);
            pic = flip(pic);
            depth--;
            break;
        }
        for(int i=0;i<n_cols;i++) {
            if(curr->children[i] == NULL && get_cell(i, 0, lf) == NO_PIECE) {
                do_move(lf, i, pic);
                move_stack[depth] = i;
                pic = flip(pic);
                curr->children[i] = malloc(sizeof(TreeNode)+sizeof(TreeNode*)*n_cols);
                curr->children[i]->parrent = curr;
                curr = curr->children[i];
                curr->state_value = NAN;
                depth++;
                break;
            }
            //if(i == n_cols-1) {
            //    if(curr == root)
            //        goto cleanup;

            //}
       }
    }

cleanup:
   return res; 
}
#define SZ 5
int main(void) {
       LField *lf = create_lfield(SZ, SZ);
       print_field(lf);
       float *b = search((float []){ [0 ... SZ] = 0}, lf, 8, X);
       free(lf);
}
