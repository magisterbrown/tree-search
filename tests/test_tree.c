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
    root->fig = pic;
    TreeNode *curr = root;
    int depth = 0;
    int ct = 0;
    for(;;) {
        int win = field_done(lf, flip(curr->fig), INAROW);
        int backtrack = 0;
        if(win)
        {
            print_field(lf);
            backtrack = 1;
        }
        else if(depth == max_depth) {
            TreeNode *up_node = curr; 
            float leaf_v = 7;
            curr->state_value = leaf_v;
            Piece up_fig = pic;

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
                do_move(lf, i, curr->fig);
                curr->children[i] = malloc(sizeof(TreeNode)+sizeof(TreeNode*)*n_cols);
                curr->children[i]->parrent = curr;
                curr->children[i]->fig = flip(curr->fig);
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
       float *b = search((float []){ [0 ... SZ] = 0}, lf, 5, X);
       free(lf);
}
