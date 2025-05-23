#include "state.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <signal.h>


int softmax_choice(size_t sz, float scores[sz])
{
    float max = -999;
    for(int i=0;i<sz;i++)
        max = scores[i] > max ? scores[i] : max;

    float denom = 0;
    for(int i=0;i<sz;i++)
        if(scores[i] == scores[i]) 
            denom += exp(scores[i]-max);
    if(denom == 0)
        return -1;

    int idx = -1;
    float entropy = (float)rand()/(float)(RAND_MAX);
    float total = 0;
    for(int i=0;i<sz;i++) {
        if(scores[i] == scores[i]) {
            float vl = exp(scores[i]-max)/denom;
            total += vl;

            if(total >= entropy)
                return i;
        }
    }
}
#define WIDTH 6
#define HEIGHT 5
#define INAROW 4
#define MAGIC 0xDEADBEEF

typedef struct {
    //int widh;
    //int height;
    int n_steps;
    int res;
    unsigned int magic; 
    //unsigned char moves[];
} GameRecord;

int keepgoing = 1;
void sig_handler(int signo)
{
    keepgoing = 0;
}

struct Stats {
    int draws;
    int xs;
    int ys;
};

#define OUTPUT "resources/test.bindone"
int main(void)
{
    srand(time(NULL));
    signal(SIGINT, sig_handler);
    unsigned char buffer[WIDTH*HEIGHT];
    FILE *check = fopen(OUTPUT, "r");
    FILE *bindone = fopen(OUTPUT, "a");
    if(bindone == NULL) {
        fprintf(stderr, "Make a resources folder\n"); 
        return 1;
    }
    // TODO: put only if file does not exist

    if(check) {
        int side;        
        fread(&side, sizeof(int), 1, check);
        if(side!=WIDTH){
            fprintf(stderr, "File width %d does not match search width %d\n", side, WIDTH); 
            return 1;
        }
        fread(&side, sizeof(int), 1, check);
        if(side!=HEIGHT){
            fprintf(stderr, "File height %d does not match search height %d\n", side, HEIGHT); 
            return 1;
        }
        fprintf(stderr, "Appending\n");
        fclose(check);
    } else {
        putw(WIDTH,  bindone);
        putw(HEIGHT, bindone);
    }
    struct Stats results = {0};
    int width = WIDTH;
    int height = HEIGHT;

    for(int played=1;keepgoing;played++) {
        LField *lf = create_lfield(WIDTH, HEIGHT);
        int buffpt = 0;
        Piece fig = X;
        GameRecord record = {.res=0, .magic=MAGIC};
        for(;;) {
            float estimates[WIDTH];
            search(estimates,(GameContext){lf, fig, INAROW}, (SearchContext){6});           
            if(fig == Y)
                for(int i=0;i<WIDTH;i++)
                    estimates[i] *= -1.0f;
            int move = softmax_choice(WIDTH, estimates);
            if(move == -1)
                break;
            int place = do_move(lf, move, fig);
            buffer[buffpt++] = place;
            //printf("Place %d\n", place);

            if(field_done(lf, fig, INAROW)) {
                record.res = fig==X ? 1 : -1;
                break;
            }
            fig = flip(fig);
        }
        print_field(lf);
        results.draws += record.res == 0;
        results.xs += record.res == 1;
        results.ys += record.res == -1;
        record.n_steps = buffpt;
        fwrite(&record, sizeof(GameRecord), 1, bindone);
        fwrite(buffer, 1, buffpt, bindone);
        printf("Moves  %d \n", buffpt);
        printf("Last result: %d\n", record.res);
        printf("Played: %d Draws: %d X wins: %d Y wins: %d\n", played, results.draws, results.xs, results.ys);
    }
    fclose(bindone);
}
