#include "state.h"
#include <math.h>

typedef struct {
    int n_cols;
    int depth;
} SearchConfig;

typedef struct TreeNode {
    float value;
    struct TreeNode *parrent;
    struct TreeNode *children[];
} TreeNode;

float *search(float res[], LField *lf, int max_depth, Piece pic) {
    int n_cols = lf->width;
    TreeNode *root = malloc(sizeof(TreeNode)+sizeof(TreeNode*)*n_cols);
    root->value = NAN;
    TreeNode *curr = root;

    int depth = 0;
    pic = flip(pic);
    while(1) {
        if(depth == max_depth) {
            TreeNode *up_node = curr; 
            float leaf_v = 7;
            Piece up_fig = pic;
            while(up_node->parrent != NULL){
                up_fig = flip(pic);
                use_max = !use_max;
                up_node = up_node->parrent;
                if(up_node->value == NAN) {
                    up_node->value = leaf_v;
                    continue;
                }
                float old_value = up_node->value;
                if(up_fig==X) 
                    up_node->value = up_node->value > leaf_v ? up_node->value : leaf_v;
                else
                    up_node->value = up_node->value < leaf_v ? up_node->value : leaf_v;
                if(old_value == up_node->value)
                    break;


            } 

            break;
        }
        for(int i=0;i<n_cols;i++) {
            if(curr->children[i] == NULL && get_cell(i, 0, lf) == NO_PIECE) {
                do_move(lf, i, pic);
                pic = flip(pic);
                curr->children[i] = malloc(sizeof(TreeNode)+sizeof(TreeNode*)*n_cols);
                curr->children[i]->parrent = curr;
                curr = curr->children[i];
                curr->value = NAN;
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
