#include <stdio.h>
#include "../state.h"

#define NUM_PARAM_TENSORS 4
typedef struct {
    float* transformer;
    float* l1;
    float* l2;
    float* decoder;
} Parameters;

#define NUM_ACTIVATION_TENSORS 6
typedef struct {
    float* encoded_us;
    float* encoded_them;
    float* combined;
    float* l1_out;
    float* l2_out;
    float* logits;
    float* probs;
} Activations;

void fill_activation_sizes(size_t* acts) 
{
    acts[0] = 256;
    acts[1] = 256;
    acts[2] = 256;
    acts[3] = 32;
    acts[4] = 1;
    acts[5] = 1;
}

typedef struct {
    Parameters params;
    size_t param_sizes[NUM_PARAM_TENSORS];
    Activations acts;
    size_t activation_sizes[NUM_ACTIVATION_TENSORS];
    float* acts_memory;
} Model;

void nn_forward(Model* nn, int* us, int* them, size_t field_size)
{
    fill_activation_sizes(nn->activation_sizes);
    if(nn->acts_memory == NULL) {
        Activations acts = nn->acts;
        size_t total_acts = 0;
        for(int i=0;i<NUM_ACTIVATION_TENSORS;i++)
            total_acts+=nn->activation_sizes[i];
        float* mem_block = malloc(total_acts*sizeof(float));

        float** ptrs[] = { &acts.encoded_us, &acts.encoded_them, &acts.l1_out, &acts.l2_out, &acts.logits, &acts.probs };
        acts.combined = mem_block;
        for(int i=0;i<NUM_ACTIVATION_TENSORS;i++) {
            *(ptrs[i]) = mem_block;
            mem_block+=nn->activation_sizes[i];
        }
    }
}



#define WIDTH 6
#define HEIGHT 5
int main()
{
    Model nn = {};
    printf("Hey model\n");
    LField *lf = create_lfield(WIDTH, HEIGHT);
    do_move(lf, 0, X);
    do_move(lf, 0, Y);
    do_move(lf, 0, X);
    do_move(lf, 3, X);
    int us[WIDTH*HEIGHT];
    int them[WIDTH*HEIGHT];

    for(int i=0;i<WIDTH*HEIGHT;i++) {
        if(lf->board[i] == X)
            us[i]=1;
        else if(lf->board[i] == Y)
            them[i]=1;
    }

    nn_forward(&nn, us, them, WIDTH*HEIGHT);

    return 0;
}
