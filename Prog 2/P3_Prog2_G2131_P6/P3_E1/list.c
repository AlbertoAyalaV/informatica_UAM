#include "list.h"

/**------------------------------------------------------------------
Nombre: getNode
Descripcion: Inicializa un nodo
Salida: el nodo inicializado
------------------------------------------------------------------*/
NODE *getNode()
{
  NODE   *nodo;
  
  nodo=(NODE*)malloc(sizeof(NODE));
  if(!nodo)
    return NULL;
  
  NEXT(nodo)=NULL;
  
  return nodo;
}

/**------------------------------------------------------------------
Nombre: freeNode
Descripcion: Libera un nodo de la lista
Entrada: la lista 
------------------------------------------------------------------*/
void freeNode(NODE *node)
{
  NEXT(node)=NULL;
  free(node);
  node=NULL;
}

/**------------------------------------------------------------------
Nombre: iniList
Descripcion: Inicializa una lista
Entrada: la lista a inicializar
Salida: ERR si ha habido error o OK si ha ido bien
------------------------------------------------------------------*/
STATUS iniList(LIST *list)
{
  
  *list=NULL;
  
  return OK;
}

/**------------------------------------------------------------------
Nombre: insertFirstEleList
Descripcion: inserta un elemento al principio de la lista
Entrada: un elemento y la lista donde insertarlo
Salida: ERR si ha habido error o OK si ha ido bien
------------------------------------------------------------------*/
STATUS insertFirstEleList (LIST *list, const ELELIST *pElem)
{
  
  NODE *nodo;
  
  if(!list||!pElem)
    return ERROR;
  
  nodo=getNode();
  
  if(!nodo||copyEleList (&DATA(nodo),pElem)!=OK)
    return ERROR;

  NEXT(nodo)=*list;
  *list=nodo;
  
  return OK;
}

/**------------------------------------------------------------------
Nombre: insertLastEleList
Descripcion: inserta un elemento al final de la lista
Entrada: un elemento y la lista donde insertarlo
Salida: ERR si ha habido error o OK si ha ido bien
------------------------------------------------------------------*/
STATUS insertLastEleList  (LIST *list, const ELELIST *pElem)
{
  NODE *nodo,*anterior;
  
  if(!list||!pElem)
    return ERROR;
  
  nodo=getNode();
  
  if(!nodo||copyEleList (&DATA(nodo),pElem)!=OK)
    {
     if(nodo)
       freeNode(nodo);
    return ERROR;
    }
  
  if(isEmptyList(list)==TRUE)
    {
      *list=nodo; 
    }
  
  else
    {
      anterior=*list;
      while(NEXT(anterior)!=NULL)
        {
            anterior=NEXT(anterior);
        }
  
       NEXT(anterior)=nodo;
    }
   
  return OK; 
}

/**------------------------------------------------------------------
Nombre: extractFirstEleList
Descripcion: Extrae primer elemento de la lista
Entrada: un elemento y la lista de donde extraerlo
Salida: ERR si ha habido error o OK si ha ido bien
------------------------------------------------------------------*/
STATUS extractFirstEleList (LIST *list, ELELIST *pElem)
{
  NODE *nodo; 
  
  if(!list||!pElem||isEmptyList(list)!=FALSE)
    return ERROR;
  
  
  nodo=*list;
  
  if(copyEleList (pElem,&DATA(nodo))!=OK)
    return ERROR;

  *list=NEXT(nodo);

  freeNode(nodo);

  return OK;
  
}

/**------------------------------------------------------------------
Nombre: extractLastEleList
Descripcion: Extrae el último elemento de la lista
Entrada: un elemento y la lista de donde extraerlo
Salida: ERR si ha habido error o OK si ha ido bien
------------------------------------------------------------------*/
STATUS extractLastEleList (LIST *list, ELELIST *pElem)
{
  NODE *nodo,*anterior;
  if(!list||!pElem||isEmptyList(list)!=FALSE)
    return ERROR;
  
  nodo=*list;
  
  if(NEXT(nodo)==NULL)
    {    
        if(copyEleList (pElem,&DATA(nodo))!=OK)
            return ERROR;
        freeNode(nodo);
        *list=NULL;
    }
  
  else
    {
        while(NEXT(nodo)!=NULL)
        { 
            anterior=nodo;
            nodo=NEXT(nodo);
        }
  
        if(copyEleList (pElem,&DATA(nodo))!=OK)
            return ERROR;

        freeNode(nodo);
        NEXT(anterior)=NULL;
    }
  
  
  return OK;
}

/**------------------------------------------------------------------
Nombre: freeList
Descripcion: Libera la lista
Entrada: la lista
Salida: ERR si ha habido error o OK si ha ido bien
------------------------------------------------------------------*/
STATUS freeList(LIST *list)
{
  
  if(!list)
    return ERROR;
  
  if(isEmptyList(list)==TRUE)
    return OK;
  
 
   if( freeList(&NEXT(*list))!=OK)
     return ERROR;
  
  freeNode(*list);
  
  *list=NULL;
 
  return OK;
}

/**------------------------------------------------------------------
Nombre: isEmptyList
Descripcion: Comprueba si la lista está vacía
Entrada: la lista
Salida: TRUE si la lista está vacía y FALSE en caso contrario
------------------------------------------------------------------*/
BOOL isEmptyList(const LIST *list)
{
  if(*list==NULL)
    return TRUE;
  return FALSE;
}

/**------------------------------------------------------------------
Nombre: numElemsList
Descripcion: Devuelve el número de elementos de la lista
Entrada: la lista
Salida: el número de elementos de la lista
------------------------------------------------------------------*/
int numElemsList(const LIST *list)
{
  int contador;
  
  NODE *aux;
  if(!list)
    return -1;
  if(isEmptyList(list)!=FALSE)
    return 0;
  aux=*list;
  for(contador=0;NEXT(aux)!=NULL;contador++)
    {
      aux=NEXT(aux);
    }
  
  contador++;
  
  return contador;
  
}

/**------------------------------------------------------------------
Nombre: printList
Descripcion: imprime toda la lista
Entrada: lista a imprimir y fichero donde imprimirla
------------------------------------------------------------------*/

void printList(FILE *fd, const LIST *list)
{
  NODE *aux;
  
  if(isEmptyList(list)==TRUE)
    return;
  aux=*list;
  
  while(NEXT(aux)!=NULL)
    { 
      printEleList (fd, &DATA(aux));
      aux=NEXT(aux);
    }
  
  printEleList (fd, &DATA(aux));
 
}