#include "elelist.h"

/**------------------------------------------------------------------
Nombre: copyEleList
Descripcion: Copia el elemento
Entrada: elemento a copiar y elemento que va a ser copiado
Salida: ERR si ha habido error o OK si ha ido bien
------------------------------------------------------------------*/
STATUS copyEleList (ELELIST *pDest, const ELELIST *pOrigin)
{
  return copyPhone(pDest,pOrigin);
}

/**------------------------------------------------------------------
Nombre: printEleList
Descripcion: Imprime en un fichero el elemento
Entrada: Fichero en el que se imprime y el elemento a imprimir
------------------------------------------------------------------*/
void printEleList (FILE * pf, const ELELIST *pe)
{
printPhone(pf,pe);
}

/**------------------------------------------------------------------ 
* Compara dos elementos de una lista, devuelve 1, -1 o 0 según e1 sea 
* mayor, menor o igual que e2. 
*------------------------------------------------------------------*/ 
int cmpEleList(const ELELIST* e1, const ELELIST* e2)
{
  return cmpPhone(e1,e2);
}

ELELIST* iniEleList (PHONE *p){
  return iniPhone(p->prefix, p->number);
}
void freeEleList (ELELIST *pe){
   freePhone(pe);
}
