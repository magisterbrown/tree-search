
int check_line_eval(Field *board, int xst, int yst, int dx, int dy, Piece pic) {
    int best_full = 0;

    int fullrow = 0;
    int emprow = 0;

    while(1) {
        if(xst<0 || xst>=WIDTH || yst<0 || yst>=HEIGHT)
            return NO_PIECE;
        Piece nf = get_cell(xst, yst, board);
        if(nf == pic) 
            fullrow, emprow = 0;
        int match = nf == flip(pic); 
        fullrow = (fullrow+match)*match;

        int rowmatch = match || nf == NO_PIECE; 
        emprow = (emprow+rowmatch)*rowmatch;

        xst+=dx;
        yst+=dy;
        if(emprow>=INAROW){
            best_full = max(best_full, fullrow);
        }
    }
    return best_full;
}
Piece check_line(Field *board, int xst, int yst, int dx, int dy) {
    Piece f = NO_PIECE;
    int crow = 0;
    while(1) {
        if(xst<0 || xst>=WIDTH || yst<0 || yst>=HEIGHT)
            return NO_PIECE;
        Piece nf = get_cell(xst, yst, board);
        int match = f == nf; 
        crow = nf==NO_PIECE ? 0 : (crow+match)*match;
        f = nf;
        xst+=dx;
        yst+=dy;
        if(crow+1 == INAROW)
            return f;
    }
}
int eval_position(Field *board) 
{
    int x_max = 0;
    int y_max = 0;
    for(int i=0;i<WIDTH;i++) {
        int tmp=0;
        tmp = check_line_eval(board, i, 0, 0, 1, X);
        x_max = max(x_max, tmp);
        tmp = check_line_eval(board, i, 0, 1, 1, X);
        x_max = max(x_max, tmp);
        tmp = check_line_eval(board, i, 0, -1, 1, X);
        x_max = max(x_max, tmp);

        tmp = check_line_eval(board, i, 0, 0, 1, Y);
        y_max = max(y_max, tmp);
        tmp = check_line_eval(board, i, 0, 1, 1, Y);
        y_max = max(y_max, tmp);
        tmp = check_line_eval(board, i, 0, -1, 1, Y);
        y_max = max(y_max, tmp);
    }
    for(int i=0;i<HEIGHT;i++) {
        int tmp=0;
        tmp = check_line_eval(board, 0, i, 1, 0, X);
        x_max = max(x_max, tmp);
        tmp = check_line_eval(board, 0, i, 1, 1, X);
        x_max = max(x_max, tmp);
        tmp = check_line_eval(board, WIDTH-1, i, -1, 1, X);
        x_max = max(x_max, tmp);

        tmp = check_line_eval(board, 0, i, 1, 0, Y);
        y_max = max(y_max, tmp);
        tmp = check_line_eval(board, 0, i, 1, 1, Y);
        y_max = max(y_max, tmp);
        tmp = check_line_eval(board, WIDTH-1, i, -1, 1, Y);
        y_max = max(y_max, tmp);
    }
    return x_max;
}
Piece winner(Field *board_field) 
{
    Piece res = NO_PIECE;
    for(int i=0;i<WIDTH;i++) {
        res = check_line(board_field, i, 0, 0, 1);
        if(res) return res;
        res = check_line(board_field, i, 0, 1, 1);
        if(res) return res;
        res = check_line(board_field, i, 0, -1, 1);
        if(res) return res;
    }

    for(int i=0;i<HEIGHT;i++) {
        res = check_line(board_field, 0, i, 1, 0);
        if(res) return res;
        res = check_line(board_field, 0, i, 1, 1);
        if(res) return res;
        res = check_line(board_field, WIDTH-1, i, -1, 1);
        if(res) return res;
    }
    return NO_PIECE;
}
