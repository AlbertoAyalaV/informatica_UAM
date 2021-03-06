/**
*@brief El ejercicio 6 de la Practica 1 SOPER
*
*@file ejercicio6.c
*@author Oscar Garcia de Lara Parreño
*@author Santiago Gomez Aguirre
*@version 1.0
*@date 18-02-2016
**/

#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <sys/types.h>
/**
*@brief Comprobar si se comparte memoria
*-No, ya que los punteros aunque tengan el mismo valor apuntan a la memoria de cada proceso.
*Podemos usar memoria compartida pero el valor del puntero tiene distinto valor pero apuntan a la misma direcion
*-En los dos ya que esta reservado
*@return EXIT_FAILURE en caso de error, EXIT_SUCCESS si funciona
**/
int main(void){
  int pid,estadoHijo;
  char *frase=(char*)malloc(20*sizeof(frase[0]));
  strcpy(frase,"HOLA");
  pid=fork();

  switch (pid) {
    case -1:
    printf("Error al emplear fork\n");
    exit(EXIT_FAILURE);
    break;
    case 0:
    printf("Escribe un nombre (limite 20 caracteres): ");
    scanf("%s",frase );
    break;
    default:
    wait(&estadoHijo);
    printf("Si imprime HOLA no ve lo que escribre en el hijo: %s",frase);
    break;
  }
    free(frase);
exit(EXIT_SUCCESS);
}
