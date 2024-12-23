#include <stdio.h>
#include "state.h"

#include <stdlib.h>
#include <string.h>

#define MAX_DEPTH 2

int main(void) 
{
    // Initialization 
    Field stateBoard = {};
    TreeNode rootNode = {.fig=X};
    printf("%d\n", sizeof(stateBoard.board[0]));
    for(int i=0;i<sizeof(stateBoard.board)/sizeof(stateBoard.board[0]);i++)
        stateBoard.board[i] = NO_PIECE;

    // Tree searh
    int c_depth = 0;
    TreeNode *currNode = &rootNode;
    while(1) {
        // TODO: check for endgame or that field is full
        if(0)
            continue;

        if(c_depth==MAX_DEPTH){
            // TODO: evaluate
            // TODO: update value
            print_field(&stateBoard);
            printf("\n");
            c_depth--;
            undo_move(&stateBoard, currNode->move);
            currNode = currNode->parrent;
            continue;
            //return 0;
        }
        for(int i=0;i<WIDTH;i++) {
            if(stateBoard.board[i] == NO_PIECE && currNode->children[i] == NULL) {
                TreeNode *nextNode = memcpy(malloc(sizeof(TreeNode)),&(TreeNode){.move=i, .parrent=currNode, .fig=flip(currNode->fig)},sizeof(TreeNode));
                currNode->children[i] = nextNode;
                c_depth++;
                do_move(&stateBoard, i, currNode->fig);
                currNode = nextNode;
                break;
            }
            // TODO: back track
            if(i==WIDTH-1) {
                if(currNode->parrent == NULL) {
                    printf("Search is done\n"); 
                    return 0;
                }
                c_depth--;
                undo_move(&stateBoard, currNode->move);
                currNode = currNode->parrent;
            }
                 
        }
    }

    printf("Heoolll\n");
    //do_move(&stateBoard, 2, X);
    //do_move(&stateBoard, 2, X);
    //undo_move(&stateBoard, 2);
    return 0;
}
