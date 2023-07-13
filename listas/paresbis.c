#include<stdio.h>
#include<stdlib.h>
#include<conio.h> //OK 02/06/2017
#include<time.h>
#define p printf
#define s scanf
//  Ingresa una lista en orden sin repeticiones, y extrae de la lista original los nodos con datos pares
//  y los almacena en una lista par OK 21/06/2016
//  Si el dato del el nodo apuntado por la lista es par los asigna a la
//  lista par y lista original apunta al siguiente.
typedef struct elemento
{
	int dato;
	int cont;
	struct elemento*sig;
} nodo;
void borranodo(nodo**,int);
void insertar(nodo**,int);
nodo*nuevonodo(int);
//nodo *sacar(nodo**);
//void poner(nodo**,nodo*);
void listar(nodo*);
void eliminar(nodo**);
void creapar(nodo**,nodo**);
int main()
{
 int i, cant,n;
 nodo*cabeza,*par;
 cabeza=NULL;
 par=NULL;
 srand(time(NULL));
 system("color 9f");
 p("\n Ingrese la cantidad de elementos:");
 s("%d",&cant);
 for(i=0;i<cant;i++)
		{
		     insertar(&cabeza,rand()%8+1);
		   // p("\n Ingrese Nro:"); s("%d",&n);
		    //insertar(&cabeza,n);
		}

 system("cls");
 p("\n\n Lista Ingresada\n\n");
 listar(cabeza);
 p("\n\n");
 creapar(&cabeza,&par);
 p("\n\n Lista de Impares\n\n"); listar(cabeza);
 p("\n\n Lista de Pares\n\n"); listar(par);
 p("\n\n Presione una Tecla para borrar los nodos de la lista de Impares!!!"); getch();
 eliminar(&cabeza);
 p("\n\n Presione una Tecla para borrar los nodos de la lista de Pares!!!!"); getch();
 eliminar(&par);
 //getch();
 free(cabeza);
 if(cabeza)    listar(cabeza);
      else p ("\n\nLista Impar vac¡a!!!\n\n\n");
 free(par);
  if(par)    listar(par);
       else p ("\n\nLista Par vac¡a!!!\n\n\n");
 return(0);
 }

void creapar(nodo**x,nodo**y)
{
    if(*x)
    {
       if((*x)->dato%2==0)
        {
            *y=*x;
            *x=(*x)->sig;
            (*y)->sig=NULL;
            p("\nNodo Par a Extraer de la lista Original:%3d (%d)",(*y)->dato,(*y)->cont);getch();
            creapar(&(*x),&(*y)->sig);
         } else  creapar(&(*x)->sig, y);
    }
}

 void insertar(nodo** x,int y)
 {
	nodo *nuevo;
	nuevo=nuevonodo(y);
	if(*x==NULL)    *x=nuevo;
		   else if((*x)->dato>y)
                {
                 nuevo->sig=*x;
                 *x=nuevo;
                }
                else if (y==(*x)->dato)(*x)->cont++;
                      else insertar(&(*x)->sig,y);
 }
nodo * nuevonodo(int x)
{
 nodo *a;
 a=(nodo*)malloc(sizeof(nodo));
 a->dato=x;
 a->cont=1;
 a->sig=NULL;
 return a;
 }

void listar(nodo*x)
{
	if(x)
	{	 p("%4ld (%d)",x->dato,x->cont);
         listar(x->sig);
	 }
}

void eliminar(nodo**x)
 {
  nodo*aux;
  if(*x)
  {
	 aux=*x;
	 p("\nNodo a Borrar:%3d",(*x)->dato);getch();
	 *x=aux->sig;
	 free(aux);
	 eliminar(x);
  }
}


