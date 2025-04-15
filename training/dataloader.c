#include <stdlib.h>
#include <stdio.h>
#include <string.h>

struct Position {
    int result;
    int moves_left;
    float *attacker;
    float *deffender;
};

typedef struct {
    int n_steps;
    int res;
    unsigned char moves[];
} GameRecord;



struct loader {
    int width;
    int height;
    FILE *bindone;
    int step;
    float *xfigs;
    float *yfigs;
    struct Position result;
    GameRecord last_rec;
};

struct loader *init() {
    FILE *ds = fopen("dataset.bindone", "r");
    struct loader *res = malloc(sizeof(struct loader));
    res->bindone = ds;
    res->step = 0;
    fread(&res->width, sizeof(int), 1, ds);
    fread(&res->height, sizeof(int), 1, ds);
    printf("Widht %d, Hie %d\n", res->width, res->height);
    int fieldsz = res->width*res->height;
    res->xfigs = malloc(sizeof(float)*fieldsz);
    res->yfigs = malloc(sizeof(float)*fieldsz);

    return res;
}

struct Position *get_next(struct loader *source) 
{
    int fieldsz = source->width*source->height;
    if(source->step == 0) {
        fread(&source->last_rec, sizeof(GameRecord), 1, source->bindone);
        memset(source->xfigs, 0, sizeof(float)*fieldsz);
        memset(source->yfigs, 0, sizeof(float)*fieldsz);
    }
    struct Position *res = &source->result;
    unsigned char pos;
    fread(&pos, 1, 1, source->bindone); 
    pos--;
    res->moves_left = source->last_rec.n_steps - source->step;
    res->result = 88;
    if(source->step%2) {
        source->yfigs[pos] = 1.0f;
        res->attacker = source->xfigs;
        res->deffender = source->yfigs;
    }
    else {
        source->xfigs[pos] = 1.0f;
        res->attacker = source->yfigs;
        res->deffender = source->xfigs;
    }

    source->step++;
    return res;
    
}

int main() {
    struct loader *first = init();
    struct Position *pos = get_next(first);
    pos = get_next(first);
    pos = get_next(first);
    return 0;
}
