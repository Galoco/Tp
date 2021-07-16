//funciones para la pelotita
double computar_velocidad (double vi, double a, double dt, double rozamiento){
    return  (dt * a + vi)/rozamiento;//ESTA BIEN ESTO??
    //return (dt*a+vi)- (dt*rozamiento) se me ocurre esto, lo consulto por discord  
}

double computar_posicion (double pi, double vi, double dt){
    return  dt * vi + pi;
}