#define WIDTH 4
#define HEIGHT 3

typedef enum Piece: unsigned char {
    NO_PIECE,
    X,
    Y,
} Piece;

#define flip(fig) fig == X ? Y : X

typedef struct Field {
    Piece board[WIDTH*HEIGHT];
} Field;

typedef struct TreeNode {
    int depth;
    int move;
    Piece fig;
    struct TreeNode *parrent;
    struct TreeNode *children[WIDTH];
} TreeNode;

void do_move(Field *curr, int col, Piece fig) 
{
   for(int y=HEIGHT-1;y>=0;y--) {
        if(curr->board[y*WIDTH+col] == NO_PIECE) {
            curr->board[y*WIDTH+col] = fig;
            break;
        }
   }
}

void undo_move(Field *curr, int col) 
{
    for(int y=0;y<HEIGHT;y++) {
        if(curr->board[y*WIDTH+col] != NO_PIECE) {
            curr->board[y*WIDTH+col] = NO_PIECE;
            break;
        }
    }
}

void print_field(Field *curr) 
{
    for(int y=0;y<HEIGHT;y++) {
        for(int x=0;x<WIDTH;x++) {
            switch(curr->board[y*WIDTH+x]) {
                case NO_PIECE: printf("0");break;
                case X:        printf("x");break;
                case Y:        printf("y");break;
            }
            if(x!=WIDTH-1)
                printf(" ");
        }
        printf("\n");
    }
}

#define empty_field()
