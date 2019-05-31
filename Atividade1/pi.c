#include <stdio.h>
#include <stdlib.h>
#include <time.h>
    
float MonteCarlosPi(int n){
    float x = 0, y = 0;
    int acertos = 0, i;
    for( i = 0; i < n; i++){
        x=((float)rand()/(float)(RAND_MAX));
        y=((float)rand()/(float)(RAND_MAX));
        if((x * x + y * y < 1))
            acertos += 1;
    }
    return 4 * (float)acertos / (float)n;
}

int main(int argc, char **argv){
    srand((unsigned int ) time(0));
    printf("%.5f\n", MonteCarlosPi(atoi(argv[1])));
    return 0;
}