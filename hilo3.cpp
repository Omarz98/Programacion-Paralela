/*
Universidad Autonoma del estado de mexico
UA: Programacion paralela
Alumno: Zamora Ramon Omar
Descripcion: Programa que crea 4 hilos uno abre un archivo
otro escribe un archivo, otro imprime numeros aleatorios
y el ultimo imprime una cadena "Hola hilos"
*/
//librerias
#include <pthread.h>
#include <cstdio>
#include <cstdlib>
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <iostream>

using namespace std;

//estructura principal
struct print_parms
{
    int num, count,fd;
    string cadena;
};

//funcion que crea e imprime numeros aleatorios
void* aleatorio(void* parameters)
{
    struct print_parms* p = (struct print_parms*) parameters;
    
    srand(time(NULL));
    for(int i=0; i<p->count;i++){
        cout<< (p->num = 1 + rand() % (11 - 1));
    }
    return NULL;
    
}

//funcion que imprime la cadena
void* cadena(void* parameters)
{
    struct print_parms* p = (struct print_parms*) parameters;
    for(int i=0; i<p->count;i++){
        cout<< p->cadena;
    }
    return NULL;
}

//funcion que lee un archivo
void* leer(void* parameters)
{
    struct print_parms* p = (struct print_parms*) parameters;

    cout<<"Abriendo archivo...\n";

    open("/home/omar/Escritorio/paralela/archivo.txt", O_RDONLY);
    return NULL;
}


//funcion que escribe en un archivo
void* escribir(void* parameters)
{
    struct print_parms* p = (struct print_parms*) parameters;
    char buf[] = "Nueva linea\n";
    int fd;
    cout << "Escribiendo archivo...\n";

    for (int i = 0; i < p->count; i++)
    {
        fd = open("/home/omar/Escritorio/paralela/archivo.txt", O_WRONLY|O_APPEND);
        write(fd,buf, sizeof(buf)-1);
        close(fd);
    }

    return NULL;
    
}


//main
int main()
{

    //nombre de hilos
    pthread_t th1;
    pthread_t th2;
    pthread_t th3;
    pthread_t th4;

    //parametros de los hilos
    struct print_parms th1_args;
    struct print_parms th2_args;
    struct print_parms th3_args;
    struct print_parms th4_args;

    //creacion del primer hilo
    th1_args.count = 1000;
    pthread_create(&th1,NULL,&aleatorio,&th1_args);

    //creacion del sgundo hilo
    th2_args.count = 1000;
    th2_args.cadena = "Hola hilos ";
    pthread_create(&th2,NULL,&cadena,&th2_args);

    
    //creacion del tercer hilo
    pthread_create(&th3,NULL,&leer,&th3_args);

    
    //cuarto hilo
    pthread_create(&th4,NULL,&leer,&th4_args);

    //funcion join para que se esperen los hilos
    pthread_join(th1,NULL);
    pthread_join(th2,NULL);
    pthread_join(th3,NULL);
    pthread_join(th4,NULL);
    
    return 0;
}
