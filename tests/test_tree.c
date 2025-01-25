#include "state.h"


void test_loose() 
{
    LField *lf = create_lfield(4, 3);
    Piece bits[] ={ 0, 0, 0, 0,
                    2, 1, 2, 0,
                    1, 2, 1, 0};
    memcpy(lf->board, bits, sizeof(bits));
    print_field(lf);
    //float *b = search((float []){ [0 ... 4] = 0}, lf, 6, Y);
    float *b = search((float [4]){}, (GameContext){lf, Y, 3}, (SearchContext){6});
    printf("VALUES: ");
    for(int i=0;i<4;i++) 
        printf("%f ", b[i]);
    printf("\n");
}
void test_diff() {
    LField *lf = create_lfield(6, 3);
    Piece bits[] ={ 0, 0, 0, 0, 0, 0,
                    0, 0, 2, 0, 2, 0,
                    0, 2, 1, 2, 1, 0 };
    memcpy(lf->board, bits, sizeof(bits));
    print_field(lf);
    float *b = search((float [6]){}, (GameContext){lf, Y, 3}, (SearchContext){6});
    //float *b = search((float []){ [0 ... 4] = 0}, lf, 6, Y);
    printf("VALUES: ");
    for(int i=0;i<6;i++) 
        printf("%f ", b[i]);
    printf("\n");
}
int main(void) {
    test_loose();
    test_diff();
       //print_field(lf);
       //free(lf);
}



