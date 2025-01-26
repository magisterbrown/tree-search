#include "state.h"
#include <dlfcn.h>
#define WIDTH 5
#define HEIGHT 6
struct History {
    int pointer;
    int moves[WIDTH*HEIGHT];
};
#define push_history(hist, val) hist.moves[hist.pointer++] = val
#define pop_history(hist) hist.pointer>=0 ? hist.moves[--hist.pointer] : -1

//typedef 
float *(*search_inst)(float res[], GameContext gm, SearchContext sc);
int make_status;
void* module = 0;
#define hotreload_search()                                    \
 do {                                                         \
     make_status = system("make search");                     \
     if(make_status != 0)                                     \
         continue;                                            \
     module = dlopen("libsearch.so", RTLD_NOW);               \
     if(module == NULL) {                                     \
         printf("%s", dlerror());                             \
         continue;                                            \
     }                                                        \
     search_inst = dlsym(module, "search");                   \
 } while((make_status != 0 || module == NULL) && (getchar() || 1))                                                                     


int main(void) 
{
    int move;
    LField *lf = create_lfield(WIDTH, HEIGHT);
    Piece fig = X;
    struct History hs = {};

    hotreload_search();
    
    for(;;) {
        print_field(lf);
        int move = getchar();
        while (getchar() != '\n');
        if(move > 48 && move<48+WIDTH) { // Do a move
            int loc = move-48;
            do_move(lf, loc, fig);
            push_history(hs, loc);
            fig = flip(fig);
        } else if(move=='r') { // Redo move  
            int uno = pop_history(hs);
            if(uno != -1)
                undo_move(lf, uno);

        } else if(move=='s') { // Explore 
            float *b = search_inst((float [WIDTH]){}, (GameContext){lf, fig, .inarow=3}, (SearchContext){ .max_depth=6});
            printf("Values: ");
            for(int i=0;i<WIDTH;i++)
                printf("%d: %.3f ", i+1, b[i]);
            printf("\n");
                        
        } else if(move=='s') { // Save position

        } else if(move=='l') { // Hotreload search
            dlclose(module);
            hotreload_search();
        } else {
            printf("Wrong action %d\n", move);
        }
    }
    return 0;
}
