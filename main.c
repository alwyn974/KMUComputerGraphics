#include <stdio.h>
#include <stdlib.h>

struct Thaco_s {
    int taco_number;
    struct Thaco_s *next;
};
typedef struct Thaco_s Thaco;

Thaco *createThaco(int taco_number) {
    Thaco *taco = malloc(sizeof(Thaco));
    if (!taco) exit(84);
    taco->taco_number = taco_number;
    taco->next = NULL;
    return taco;
}

int main(int ac, char **av) {
    Thaco *tacos = createThaco(1);
    tacos->next = createThaco(2);
    printf("%d\n", tacos->taco_number);
    printf("%d\n", tacos->next->taco_number);
    return 0;
}