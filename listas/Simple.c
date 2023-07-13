#include<stdio.h> //
#include<stdlib.h> //
#include<conio.h> // Kista simple que carga en orden
#include<time.h>
#define p printf
#define s scanf

typedef struct nodo
{
    int dato;
    int cont;
    struct nodo*sig;
}  nodo;

int buscar(nodo*,int);
void insertar(nodo**,int);
nodo*nuevonodo(int);
void listar(nodo*);
void eliminar(nodo**);


int main()
{
 int i, cant,num,enc=0;
 nodo*cabeza=NULL,*aux;
 srand(time(NULL));
 system("color 9f");
 p("\n Ingrese la cantidad de elementos:");
 s("%d",&cant);
 for(i=0;i<cant;i++)
 {
     // p("\n Ingrese dato:");s("%d",&num);
	 // insertar(&cabeza,num);
	  insertar(&cabeza,rand()%10+1);
 }
 p("\n\n Lista Ingresada\n\n");
 listar(cabeza);
 p("\n\n Ingrese el Nro a buscar:"); s("%d",&num);
 //aux=buscar(cabeza,num);
 enc=buscar(cabeza,num);
 if(enc==1) p("\n El nro fue encontrado");
	else p("\n El nro no fue encontrado");

 getch();
 p("\n Presione una Tecla para borrar los nodos!!!!"); getch();
 eliminar(&cabeza);
 getch();
 free(cabeza);
 if(cabeza)    listar(cabeza);
 else p ("\n\nLista vac%ca!!!\n\n\n",214);
 getch(); system("cls");
 free(cabeza);

 return(0);
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
	{	 p("%4d (%d)",x->dato,x->cont);
	 listar(x->sig);
	 }
}

/*nodo*buscar(nodo*x,int y)
{
	if(!x) return (NULL);
	 else if(y==x->dato) return(x);
		 else return(buscar(x->sig,y));
}*/
int buscar(nodo*x,int y)
{
	if(x==NULL) return (0);
	 else if(y==x->dato) return(1);
		 else return(buscar(x->sig,y));
}

void eliminar(nodo**x)
 {
  nodo*aux;
  if(*x)
  {
	 aux=*x;
	 p("\nNodo a eliminar:%3d (%d)",(*x)->dato,(*x)->cont);getch();
	 *x=aux->sig;
	 free(aux);
	 eliminar(x);
  }
}





