#include "state.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

typedef struct {
    int widh;
    int height;
    int n_steps;
    unsigned char moves[];
} GameRecord;

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

int main(void)
{
    srand(time(NULL));
    LField *lf = create_lfield(WIDTH, HEIGHT);
    unsigned char buffer[WIDTH*HEIGHT];
    Piece fig = X;
    int res = 0;
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
        if(field_done(lf, fig, INAROW)) {
            res = fig==X ? 1 : -1;
            break;
        }
        fig = flip(fig);
    }
    print_field(lf);
    printf("Result %d\n", res);
}
