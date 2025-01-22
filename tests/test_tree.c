#include "state.h"
#define NAN 0.0/0.0

typedef struct {
    int n_cols;
    int depth;
} SearchConfig;

typedef struct TreeNode {
    unsigned char idx;
    float state_value;
    Piece fig;
    struct TreeNode *parrent;
    struct TreeNode *children[];
} TreeNode;
#define INAROW 3
void stopper() {};

float *search(float res[], LField *lf, int max_depth, Piece pic) {
    int n_cols = lf->width;
    TreeNode *root = malloc(sizeof(TreeNode)+sizeof(TreeNode*)*n_cols);
    root->state_value = NAN;
    root->fig = flip(pic);
    TreeNode *curr = root;
    int depth = 0;
    float max_est = 0;
    for(;;) {
        int backtrack = 0;
        int win = field_done(lf, curr->fig, INAROW);
        if(win || depth == max_depth) {
            float leaf_v;
            if(win)
                leaf_v = curr->fig == X ? 999 : -999;
            else {
                leaf_v = field_eval(lf, INAROW);
                //if(leaf_v >= max_est) {
                //    print_field(lf);
                //    printf("Value %f\n", leaf_v);
                //    max_est = leaf_v;
                //}
            }

            TreeNode *up_node = curr; 
            curr->state_value = leaf_v;
            do {
                up_node = up_node->parrent;
                if(up_node->state_value != up_node->state_value) {
                    up_node->state_value = leaf_v;
                    continue;
                }
                else {
                }
            } while(up_node->parrent != NULL);

            backtrack = 1;
        }
        else for(int i=0;i<n_cols;i++) {
            if(curr->children[i] == NULL && get_cell(i, 0, lf) == NO_PIECE) {
                Piece next = flip(curr->fig);
                do_move(lf, i, next);
                curr->children[i] = malloc(sizeof(TreeNode)+sizeof(TreeNode*)*n_cols);
                curr->children[i]->parrent = curr;
                curr->children[i]->fig = next;
                curr = curr->children[i];
                curr->state_value = NAN;
                curr->idx=i;
                depth++;
                break;
            }
            backtrack = i == n_cols-1;
        }
        if(backtrack) {
            undo_move(lf, curr->idx);
            curr = curr->parrent;
            depth--;
            if(curr == NULL)
                goto cleanup;
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
