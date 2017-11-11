#include<stdio.h>
#include<math.h>
#include<stdlib.h>

int main(void){
    //CUERDAS
    //defino todas las constantes
    float L = 0.64;
    float dx = 0.005;
    double dt = 1.0/100000.0;//1 segundo y 1000 puntos
    int nx =129;
    int nt = 100000;
    float c = 250.0;
    double r = c*(dt/dx);
    //defino los arrays que serán el viejo, el actual y el nuevo para cada cuerda (la 2 es la de extremo suelto)
    double * longitud = malloc(nx*sizeof(double));
    double * phi_inicial = malloc(nx*sizeof(double));
    double * phi_inicial2 = malloc(nx*sizeof(double));
    double * phi = malloc(nx*sizeof(double));
    double * phi2 = malloc(nx*sizeof(double));
    double * phi_new = malloc(nx*sizeof(double));
    double * phi_new2 = malloc(nx*sizeof(double));
    double * phi_old = malloc(nx*sizeof(double));
    double * phi_old2 = malloc(nx*sizeof(double));
    double * toctavos1 = malloc(nx*sizeof(double));
    double * toctavos2 = malloc(nx*sizeof(double));
    double * tcuartos1 = malloc(nx*sizeof(double));
    double * tcuartos2 = malloc(nx*sizeof(double));
    double * tmedios1 = malloc(nx*sizeof(double));
    double * tmedios2 = malloc(nx*sizeof(double));
    double * amplitudes = malloc((nt-2)*sizeof(double));
    //lleno los arrays de phi inicial y longitud con el .dat dado
    FILE *file = fopen("cond_ini_cuerda.dat", "r");
    int i;
    for (i = 0; i < nx; i++){
      fscanf(file, "%lf %lf \n", &longitud[i], &phi_inicial[i]);
    }
    fclose(file);
    for (i = 0; i < nx; i++){ //el phi inicial 2 son ceros
      phi_inicial2[i] = 0.0;
    }
//condiciones de frontera
    phi_new[0] = phi_inicial[0];
    phi_new[nx-1] = phi_inicial[nx-1];
    phi_new2[0] = 0.0;
    phi_new2[nx-1] = 0.0;
//ahora lleno los nuevos con base en la condición inicial de la derivada
    for (i =  1; i < nx-1; i++){
      phi_new[i] = phi_inicial[i] + pow(r,2)*0.5* (phi_inicial[i+1] - 2.0* phi_inicial[i]+phi_inicial[i-1]);
      phi_new2[i] = phi_inicial2[i] + pow(r,2)*0.5* (phi_inicial2[i+1] - 2.0* phi_inicial2[i]+phi_inicial2[i-1]);
    }
//y actualizo: el antiguo es el inicial, el actual es el nuevo
    for (i = 0; i < nx; i++){
      phi_old[i] = phi_inicial[i];
      phi[i] = phi_new[i];
      phi_old2[i] = phi_inicial2[i];
      phi2[i] = phi_new2[i];
    }
//itero sobre el tiempo
    int j;
    for(j = 1; j < nt-1; j++){
      phi_new2[nx-1] = sin(2*3.1416*c*j*dt/L); //cambio la condición de frontera pues depende de t
      //lleno el nuevo con base en el viejo y el actual
      for(i = 1; i < nx-1; i++){
        phi_new[i] = 2.0*(1.0-pow(r,2))*phi[i] - phi_old[i] + pow(r,2)*(phi[i+1]+phi[i-1]);
        phi_new2[i] = 2.0*(1.0-pow(r,2))*phi2[i] - phi_old2[i] + pow(r,2)*(phi2[i+1]+phi2[i-1]);
      }
//actualizo
      int k;
      for (k = 0; k < nx; k++){
        phi_old[k] = phi[k];
        phi[k] = phi_new[k];
        phi_old2[k] = phi2[k];
        phi2[k] = phi_new2[k];
      }
      amplitudes[j] = phi_new[64];
//Para la 1, uso printf("%f %d \n", phi_new[64], j) y hallo una oscilación entera cuando j=513 (T=5.13 ms)
//para la otra cuerda, el periodo es L/c = 0.00256, el índice que le corresponde es j=T/dt=256
      if(j == 32){
        for (i = 0; i < nx; i++) {
          toctavos2[i] = phi_new2[i]; //T/8 cuerda suelta
        }
      }
      if(j == 64){
        for (i = 0; i < nx; i++) {
          toctavos1[i] = phi_new[i]; //T/8 cuerda fija
          tcuartos2[i] = phi_new2[i]; //T/4 cuerda suelta
        }
      }
      if(j == 128){
        for (i = 0; i < nx; i++) {
          tcuartos1[i] = phi_new[i]; //T/4 cuerda fija
          tmedios2[i] = phi_new2[i]; //T/2 cuerda suelta
        }
      }
      if(j == 256){
        for (i = 0; i < nx; i++) {
          tmedios1[i] = phi_new[i]; //T/2 cuerda fija
        }
      }
    }
    //guardo los resultados para los tiempos de ambas cuerdas
    FILE *results =fopen("datos.dat", "w");
    for (i = 0; i < nx; i++){
      fprintf(results, "%f %f %f %f %f %f \n", toctavos1[i], toctavos2[i], tcuartos1[i], tcuartos2[i], tmedios1[i], tmedios2[i]);
    }
    //e imprimo las amplitudes de la parte media
    for (j = 0; j < nt-2; j++){
      printf("%f \n", amplitudes[j]);
    }
    //-------------------------------------------------
    //TAMBOR 2D
    //conservamos los valores de nt, dt, dx y r
    float dy = dx;
    int N = 101; //cambiamos N al ser la matriz de NxN
    double * u_ini = malloc(N*N*sizeof(double));
    double * u = malloc(N*N*sizeof(double));
    double * u_new = malloc(N*N*sizeof(double));
    double * toctavos3 = malloc(N*N*sizeof(double));
    double * tcuartos3 = malloc(N*N*sizeof(double));
    double * tmedios3 = malloc(N*N*sizeof(double));
    FILE *file2 = fopen("cond_ini_tambor.dat", "r");
    for (i = 0; i < N*N; i++){
      fscanf(file2, "%lf \n", &u_ini[i]);
    }
    fclose(file);
    //vamos a llenar las fronteras de la membrana que se mantendrán fijas
    for (i = 0; i < N; i++){
      for (j = 0; j < N; j++){
        int pos = i + N*j; //como tenemos un gran array en vez de una matriz, hacemos este cambio de variable
        if (i == 0 || i == N-1 || j == 0 || j == N-1){ //
          u_new[pos] = u_ini[pos];
        }
      }
    }


    //HELLOOOO








    return 0;
}
