#include<stdio.h>
#include<stdlib.h> // Hecho bien hasta 12/08/2016
#include<conio.h>
#include<time.h>
#define p printf
#define s scanf
// Muestra el ingreso, cuenta los nodos
typedef struct arbol nodo;
struct arbol
{
	int info;
	int cont;
	nodo *izq;
	nodo *der;
};

void mostrarinord(nodo*);
void mostrarpreord(nodo*);
void mostrarposord(nodo*);
void insertar(int,nodo**);
void mostrar(nodo*,int);
void mostrar1(nodo*,int);
void borrar(nodo*);
void copiar(nodo*,nodo**);
nodo *nuevo(void);
int main()
{
 int n,c=0,can,i;
 int vec[]={10,7,18,28,15,9,5,3,6,8,18};
 nodo*raiz=NULL;
 nodo*aux=NULL;
 system("color 9f");
 for(i=0;i<11;i++)
{
    p("%3d",vec[i]);
    insertar(vec[i],&raiz);
}

 getch();
 p("\n\n Arbolescencia de Datos en el Arbol !!!\n\n");
 mostrar(raiz,0);
 p("\n Arbol Espejo\n\n");
 mostrar1(raiz,0);
 copiar(raiz,&aux);
  p("\n\n Nodos en Orden!!\n\n"); mostrarinord(raiz);
  p("\n \nNodos  en Preorden!!\n\n"); mostrarpreord(raiz);
  p("\n\n Nodos  en Posorden!!\n\n"); mostrarposord(raiz);
  borrar(raiz);
  p("\n\n Arbol Aux !!\n\n");
  mostrar(aux,0);
  p("\n\n Arbol Raiz borrado !!\n\n");
 getch();

 borrar(aux);
 p("\n\n Arbol Aux borrado !!\n\n");
 return(0);
 }

void copiar(nodo*x,nodo**y) /// para el espejo
{
    if(x!=NULL)
    {
        insertar(x->info,&(*y));
        copiar(x->der,&(*y));
        copiar(x->izq,&(*y));
        //insertar(x->info,y);
       // copiar(x->der,y);
       // copiar(x->izq,y);

    }
}


void insertar(int x, nodo** y)
{
	nodo *a;
	a=*y;
	if(a==NULL) // si no esta x en el arbol lo inserta
	{
	 a=nuevo();
	 a->info=x;
	 a->cont=1;
	 a->izq=a->der=NULL;

	} else if(x< a->info) insertar(x,&a->izq); // por la izquierda
                else if(x> a->info) insertar(x,&a->der);// por derecha
                        else a->cont++; // incrementa el contador si exist¡a
	*y=a;
}
nodo* nuevo()
{
 nodo *x=(nodo*)malloc(sizeof(nodo));
 return (x);

}

void mostrar(nodo*x,int y) // en orden como arbol
{
	int i;
	if(x!=NULL)
	{
		mostrar(x->der,y+1);
			for(i=1;i<=y;i++)
			p("        ");

		p("%d (%d)\n",x->info,x->cont);
		mostrar(x->izq,y+1);
	 }
}

void mostrar1(nodo*x,int y) // en orden como arbol
{
	int i;
	if(x!=NULL)
	{
		mostrar1(x->izq,y+1);
		//mostrar(x->der,y+1);
			for(i=1;i<=y;i++)
			p("        ");

		p("%d (%d)\n",x->info,x->cont);
		mostrar1(x->der,y+1);
		//mostrar(x->izq,y+1);
	 }
}
void borrar(nodo* x)
{

if(x!=NULL)
 {
	borrar(x->izq);
	borrar(x->der);
	free(x);

 }
}
void mostrarinord(nodo*x) // en orden izq raiz der
{
	if(x!=NULL)
	{
		mostrarinord(x->izq);
		p("%3d",x->info);
		mostrarinord(x->der);
	 }
}

void mostrarpreord(nodo*x) // raiz izq y der
{
	if(x!=NULL)
	{
		p("%3d",x->info);
		mostrarpreord(x->izq);
		mostrarpreord(x->der);
	 }
}

void mostrarposord(nodo*x) // izq y der y raiz
{
	if(x!=NULL)
	{
		mostrarposord(x->izq);
		mostrarposord(x->der);
		p("%3d",x->info);
	 }
}
