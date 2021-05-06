#include <stdio.h>
#include <stdlib.h>

int main()
{
    Lista *li;
    li = cria_lista();

    libera_lista(li);
    return 1;
}
