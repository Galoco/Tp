#include <fisica.h>
#include <math.h>

//funciones para la pelotita
double computar_velocidad (double vi, double a, double dt){
    return  (dt * a + vi);//ESTA BIEN ESTO??
    //return (dt*a+vi)- (dt*rozamiento) se me ocurre esto, lo consulto por discord  
}

double computar_posicion (double pi, double vi, double dt){
    return  dt * vi + pi;
}