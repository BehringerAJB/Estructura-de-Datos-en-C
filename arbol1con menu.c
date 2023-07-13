// Ingresa Datos en un Árbol Binario con repeticiones
// Inserta muestra borra ( TODO el árbol)
#include<stdio.h>
#include<stdlib.h> // árbol para pre,pos in y arbolescencia
#include<conio.h>  //
#include<time.h>
#define p printf
#define s scanf
typedef struct arbol nodo;
struct arbol
{
	int info;
	int cont;
	nodo *izq;
	nodo *der;
};

void vaciopausa(void);
void consarbol(int,nodo**);
void mostrararb(nodo*,int );
void mostrarinord(nodo*);
void mostrarpreord(nodo*);
void mostrarposord(nodo*);
void mostrar(nodo*,int);
void borrar(nodo**);
int menu(void);
nodo *nuevo(void);
int main()
{
 int num;
 nodo*raiz=NULL;
 system("color 9f");
 int op;
 do
   {
    op=menu();
    system("cls");
    switch(op)
	{
	case 1:
		p("\n Ingrese Elemento al Arbol:");
        s("%d",&num);
 	    consarbol(num,&raiz);
		break;

	case 2:
		   if(raiz)
		   {
            p("\n\n Arbol en Orden\n\n");
            mostrarinord(raiz); getch();
		   } else vaciopausa();
           break;

	case 3:
		   if(raiz)
		   {
            p("\n\n Arbol en PreOrden\n\n");
            mostrarpreord(raiz);getch();
		   } else vaciopausa();
		break;

	case 4:
		   if(raiz)
		   {
		    p("\n\n Arbol en PosOrden\n\n");
            mostrarposord(raiz);getch();
		   } else vaciopausa();
		break;

	case 5:
		   if(raiz)
		   {
		    p("\n\n Arbolescencia en Orden\n\n");
            mostrar(raiz,0);getch();
		   } else vaciopausa();
		break;

	case 6:
		   if(raiz)
		   {
		     p("\n\n Borrar el Arbol \n\n");
             p("\n Presione una tecla y comenzar  a borrar nodos!!");getch();
             borrar(&raiz);
            } else vaciopausa();
		  break;
	  }
	}while(op<7);

 getch();
 return(0);

}

void vaciopausa()
{
  p("\n Arbol Vacio\n\n"); getch();
}

void consarbol(int x,nodo**y)
{
    nodo *a;
	a=*y;
	if(a==NULL) // si no esta x en el arbol lo inserta
	{
	 a=nuevo();
	 a->info=x;
	 a->cont=1;
	 //*(z)++;
	 a->izq=a->der=NULL;

	} else
        if(x< a->info)
            consarbol(x,&a->izq); // por la izquierda
        else
            if(x> a->info)
                consarbol(x,&a->der);// por derecha
            else
                a->cont++; // incrementa el contador si existe el nodo
	*y=a;
}



nodo* nuevo()
{
 nodo *x=(nodo*)malloc(sizeof(nodo));
 return (x);

}

void mostrar(nodo*x,int y) // en orden
{
	int i;
	if(x!=NULL)
	{
		mostrar(x->der,y+1);
			for(i=1;i<=y;i++)
			p("        ");

	   p("%d(%d)\n",x->info,x->cont);
		mostrar(x->izq,y+1);
	 }
}
void mostrarinord(nodo*x) // en orden izq raiz der
{
	if(x!=NULL)
	{
		mostrarinord(x->izq);
		p("%3d(%d)",x->info,x->cont);
		mostrarinord(x->der);
	 }
}

void mostrarpreord(nodo*x) // raiz izq y der
{
	if(x!=NULL)
	{
		p("%3d(%d)",x->info,x->cont);
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
		p("%3d(%d)",x->info,x->cont);
	 }
}

void borrar(nodo**x)
 {
  nodo*aux;
  if(*x)
  {
	 aux=*x;
	 p("\nNodo a eliminar:%3d",(*x)->info);getch();
     borrar(&(*x)->izq);
	 borrar(&(*x)->der);
	 free(aux);
	}
  *x=NULL;
}

int menu(void)
{
	int op;
	 do
	 {
		system("cls");
		printf("\n\t\t\t MENU DE OPCIONES DEL ARBOL\n");
		printf("\n\n\t\t\t - Ingresar Datos           <1>\n");
		printf("\n\n\t\t\t - Mostrar en Orden         <2>\n");
		printf("\n\n\t\t\t - Mostrar en PreOrden      <3>\n");
		printf("\n\n\t\t\t - Mostrar en PosOrden      <4>\n");
		printf("\n\n\t\t\t - Mostrar en Arbolescencia <5>\n");
		printf("\n\n\t\t\t - Borrar Arbol             <6>\n");
		printf("\n\n\t\t\t - Salir                    <7>\n");
		printf("\n\n\t\t\t   Ingrese Opcion [1-7]  :  ");
		scanf("%d",&op);
	 }while(op<1||op>7);
	 return op;
}
