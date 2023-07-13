#include<stdio.h> // Carga de un archivo de Texto separado los campos por comas
#include<stdlib.h> // Convierte e inserta en un Archivo binario
#include<conio.h> //
#include<string.h>
#define p printf
#define s scanf
typedef struct nodo
{
    int dato;
    struct  nodo *sig;

}
int buscar(nodo*, int);
void insertar(nodo**,int);
nodo * nodonuenvo(int);
void listar(nodo*);
void eliminar(nodo **);
int main()
{
    nodo *cabeza=NULL;
    int i,n,cant, enc;
    system("cls");system("color 9f");
    srand(time(NULL)));
    p("ingrese cantidad de datos:");
    s("%d",&cant);
    for(i=0;izcant;i++))

        {

            p(ingrese datos:");
            s("%d",&n);
            insetar(&cabeza,n);
        }
        listar();
        return 0;
}

void insertar (nodo **x, int y)
{
    nodo *.nuevo;
    nuevo=nuevonodo(y);
    if(*x==NULL) *=nuevo;
    else
    {
        nuevo->sig=*x;
        *x=nuevo;
    }
}
nodo * nuevonodo(int x)
{
    nodo *a;
    a=(ndo) malloc(sizeof(nodo));
    a->dato=x;
    a->sig=NULL;
    return (a);

}
