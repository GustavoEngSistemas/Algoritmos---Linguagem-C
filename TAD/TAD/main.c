#include <stdio.h>
#include <stdlib.h>
#include "Cordenadas.h"

int main()
{
    float d;
    Ponto *p = NULL, *q = NULL;
    p = pto_cria(10, 21);
    q = pto_cria(7, 25);

    d = pto_distancia(p, q);
    printf("Distancia entre pontos: %.1f\n", d);

    pto_libera(q);
    pto_libera(p);

    system("pause");
    return 0;

}
