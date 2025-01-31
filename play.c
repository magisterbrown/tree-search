#include "state.h"
#include <dlfcn.h>
#include <stdio.h>
#include <string.h>
#define WIDTH 4
#define HEIGHT 3
#define INAROW 3
#define MAXDEPTH 2
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
    float last_values[WIDTH];

    hotreload_search();
    
    for(;;) {
        print_field(lf);
        int move = getchar();
        while (getchar() != '\n');
        if(move > 48 && move<=48+WIDTH) { // Do a move
            if(!field_done(lf, X, INAROW) && !field_done(lf, Y, INAROW)) {
                int loc = move-49;
                do_move(lf, loc, fig);
                push_history(hs, loc);
                fig = flip(fig);
            } else {
                printf("Game done\n");
            }
        } else if(move=='u') { // Redo move  
            int uno = pop_history(hs);
            if(uno != -1)
            {
                undo_move(lf, uno);
                fig = flip(fig);
            }

        } else if(move=='e') { // Explore 
            float *b = search_inst((float [WIDTH]){}, (GameContext){lf, fig, .inarow=INAROW}, (SearchContext){ .max_depth=MAXDEPTH});
            printf("Values: ");
            for(int i=0;i<WIDTH;i++)
                printf("%d: %.3f ", i+1, b[i]);
            printf("\n");
                        
        } else if(move=='s') { // Save position
            float *b = search_inst((float [WIDTH]){}, (GameContext){lf, fig, .inarow=INAROW}, (SearchContext){ .max_depth=MAXDEPTH});
            char filename[20];
            char full_filename[50];
            printf("Input file name: ");
            scanf("%20s", filename);
            sprintf(full_filename, "%s/%s.gm", "resources/saved_positions", filename);
            FILE * file= fopen(full_filename, "wb");
            if (file != NULL) {
                fwrite(lf, field_size(lf), 1, file);
                fwrite(&fig, sizeof(Piece), 1, file);
                int tmp = INAROW;
                fwrite(&tmp, sizeof(int), 1, file);
                tmp = MAXDEPTH;
                fwrite(&tmp, sizeof(int), 1, file);
                fwrite(b, sizeof(float), WIDTH, file);

                fclose(file);
                printf("Written %s\n", filename);
            } else {
                printf("File did not open");
            }
            
        } else if(move=='r') { // Hotreload search
            dlclose(module);
            hotreload_search();
        } else if(move=='h') { // Hotreload search
            char *help = "u - undo\nr - reload\ne - explore\ns - save position";
            printf("%s\n", help);
        } else {
            printf("Wrong action %d\n", move);
        }
    }
    return 0;
}
