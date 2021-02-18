#include <pthread.h>
#include <cstdio>
#include <iostream>

using namespace std;

//Estructura de paso de datos de funcion
struct print_parms
{
    //caracter a imprimir
    char character;
    //cuantas veces se imprimira
    int count;
};

//imprime un numero de caracteres de stderr
void* char_print(void* parameters)
{
    struct print_parms* p = (struct print_parms*) parameters;
    int i;
    for(i = 0; i< p->count; i++)
    cout<<p->character;
    return NULL;
}

int main()
{
    pthread_t th1;
    pthread_t th2;
    pthread_t th3;

    struct print_parms th1_args;
    struct print_parms th2_args;
    struct print_parms th3_args;

    th1_args.character = 'x';
    th1_args.count = 1000;
    pthread_create(&th1,NULL,&char_print,&th1_args);

    th2_args.character = 'o';
    th2_args.count = 1000;
    pthread_create(&th2,NULL,&char_print,&th2_args);

    th3_args.character = 'y';
    th3_args.count = 1000;
    pthread_create(&th3,NULL,&char_print,&th3_args);

    pthread_join(th1,NULL);
    pthread_join(th2,NULL);
    pthread_join(th3,NULL);

    return 0;

    
}
