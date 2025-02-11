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

typedef struct {
    int widh;
    int height;
    int n_steps;
    int res;
    unsigned char moves[];
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

int main(void)
{
    srand(time(NULL));
    signal(SIGINT, sig_handler);
    unsigned char buffer[WIDTH*HEIGHT];
    FILE *bindone = fopen("resources/dataset.bindone", "a");
    struct Stats results = {0};
    for(int played=1;keepgoing;played++) {
        LField *lf = create_lfield(WIDTH, HEIGHT);
        int buffpt = 0;
        Piece fig = X;
        GameRecord record = {.widh=WIDTH, .height=HEIGHT, .res=0};
        for(;;) {
            float estimates[WIDTH];
            search(estimates,(GameContext){lf, fig, INAROW}, (SearchContext){6});           
            if(fig == Y)
                for(int i=0;i<WIDTH;i++)
                    estimates[i] *= -1.0f;
            int move = softmax_choice(WIDTH, estimates);
            if(move == -1)
                break;

            do_move(lf, move, fig);
            buffer[buffpt++] = move;

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
        buffpt = 0;
        printf("Last result: %d\n", record.res);
        printf("Played: %d Draws: %d X wins: %d Y wins: %d\n", played, results.draws, results.xs, results.ys);
    }
    fclose(bindone);
}
