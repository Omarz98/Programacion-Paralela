#include <pthread.h>
#include <cstdio>
#include <cstdlib>
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <iostream>

using namespace std;

void* thread_routine(void* arg)
{
    int nr_lines = *((int*)arg);
    int fd;
    char buf[] = "Nueva linea\n";

    cout << "El hilo comienza a ejecutarse...\n";

    for (int i = 0; i < nr_lines; i++)
    {
        fd = open("/home/omar/Escritorio/paralela/archivo.txt", O_WRONLY|O_APPEND);
        write(fd,buf, sizeof(buf)-1);
        close(fd);
    }

    return NULL;
    
}

int main(int argc, char *argv[])
{
    pthread_t thread1;
    int value = atoi(argv[1]);

    if(0 != pthread_create(&thread1,NULL,thread_routine,&value))
        return -1;
    pthread_join(thread1,NULL);

    return 0;
}