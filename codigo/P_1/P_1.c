#include <stdio.h>
#include <sys/time.h>

int main(void)
{
    struct timeval t_inicial, t_final;
    double tiempo_total;
    int contador = 0;
    gettimeofday(&t_inicial, NULL);   // Instante inicial
    
    for (int i = 0; i < 1000000000; i++){
        contador = contador + i;
    }   
    gettimeofday(&t_final, NULL);   // Instante final
    
    //Conversión del tiempo a milisegundos
    tiempo_total = (t_final.tv_sec - t_inicial.tv_sec)*1000 + (t_final.tv_usec - t_inicial.tv_usec)/1000.0;
    

    printf("Tiempo total consumido: %f milisegundos\n", tiempo_total);
}