#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <malloc.h>
#define p printf
#define s scanf

typedef struct elemento{
    int dato;
    int cont;
    struct elemento *sig;
}nodo;


/*
 * FUNCION LIMPIA BUFFER para linux
 */
void clean_stdin(void){
    int c;
    do{
        c=getchar();
    }while(c!='\n' && c!=EOF);
}

void insertar(nodo**, int);
void insertarAlPrincipio(nodo**, int);
void insertarOrdenado(nodo**, int);
void insertarOrdenado2(nodo**, int);
nodo* nuevoNodo(int);
void listar(nodo*);
void eliminar(nodo**);
int buscar(nodo*, int);


int main(){
    nodo *cabeza = NULL;
    int i, n, cant, enc;
    srand(time(NULL));
    p("\n ingrese cantidad de datos\n");
    s("%d", &cant);
    clean_stdin();
    for(i=0; i<cant; i++)
    {
        p("ingrese un dato:");
        s("%d", &n);

        //insertarOrdenado2(&cabeza,n);
        insertar(&cabeza,n);
        //insertarAlPrincipio(&cabeza,n);
    }
    //rand()%20+1
    p("\ncabeza antes:%X\n",cabeza);
    p("\nlista ingresada\n");
    listar(cabeza);
    p("\n cabeza despues%X\n",cabeza);
    clean_stdin();
    p("\nInserte dato a buscar: ");
    s("%d", &n);
    clean_stdin();
    //buscar(cabeza, n);
    //if(enc) p("\nEl dato %d esta en la lista\n", n);
    //else p("\nEl dato %d no esta en la lista\n", n);
    p("\nPresionar una tecla para eliminar la lista\n");
    clean_stdin();
    eliminar(&cabeza);
    free(cabeza);

return 0;
}

void listar(nodo*x){
    if(x){
        //p("nodo {%x}: %3d sig->{%x}\n", x,x->dato,x->sig);
        //insertarOrdenado2
        p(" [%X:]dato: %3d contador: %3d contenido %X sig->[%X]\n",&(*x), x->dato, x->cont,&x->dato,x->sig);
        listar(x->sig);
    }
}
//********************
// insertar por Cola *
//********************
void insertar(nodo **x, int y){
    nodo *nuevo;
    //nuevo = nuevoNodo(y);

    if(*x==NULL){
            nuevo = nuevoNodo(y);
            p("\nnuevo->%X\n",nuevo);
            *x=nuevo;
    } else {
        insertar(&(*x)->sig, y);
    }
}

nodo* nuevoNodo(int x){
    nodo *a;
    a=(nodo*)malloc(sizeof(nodo));
    a->cont=1;
    a->dato=x;
    a->sig = NULL;
    return a;
}
//***********************
// insercion por cabeza *
//***********************
void insertarAlPrincipio(nodo **head, int dato){
    nodo *nuevo = nuevoNodo(dato);
    if(*head==NULL){
    //    nodo *nuevo = nuevoNodo(dato);
        *head=nuevo;
    } else {
        nuevo->sig = *head;
        *head = nuevo;
    }
}

void insertarOrdenado(nodo **head, int dato){
    nodo *nuevo = nuevoNodo(dato);
    if(*head == NULL ){
        *head = nuevo;
    } else if (dato<(*head)->dato){
        nuevo->sig = *head;
        *head = nuevo;
    } else {
        insertarOrdenado(&(*head)->sig, dato);
    }
}

void insertarOrdenado2(nodo **head, int dato){
    nodo *nuevo = nuevoNodo(dato);
    if(*head == NULL ){
        *head = nuevo;
    } else if (dato==(*head)->dato){
        (*head)->cont+=1;
    } else if (dato< (*head)->dato ){
        nuevo->sig = *head;
        *head = nuevo;
        } else {
            insertarOrdenado2(&(*head)->sig, dato);
    }

}

void eliminar(nodo **head){
    nodo *aux;
    if(*head){
        aux=*head;
    p("\nNodo a eliminar: %3d(%d)", (*head)->dato, (*head)->cont);
    clean_stdin();
    *head = aux->sig;
    free(aux);
    eliminar(head);
    }
}

int buscar(nodo *head, int dato){
    if(head==NULL){
        return 0;
    } else if (dato==head->dato){
        return 1;
    } else {
        return buscar(head->sig, dato);
    }
}

/*
ejercicios para hacer
pdf en carpeta clase 8
hacer 1, 3, 5
*/
