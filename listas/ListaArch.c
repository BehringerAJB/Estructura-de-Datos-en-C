#include<stdio.h> // Lista abierta con repeticiones
#include<stdlib.h> // Inserta por la cola en forma secuencial.
#include<conio.h> // busca un elemento y borra la lista nodo a nodo.
#include<time.h>
#define p printf
#define s scanf

typedef struct lista
{
    int dato;
    int cont;
    struct lista*sig;
}  nodo;

nodo*buscar(nodo*,int);
void insertar(nodo**,int,int);
nodo*nuevonodo(int,int);
void listar(nodo*);
void eliminar(nodo**);
void cargar(nodo*,FILE*);
void mostrar(FILE*);
void cargar_lista(nodo**,FILE*);
int main()
{
 int i, cant,num;
 nodo*cabeza,*aux;
 FILE *archi;
 cabeza=NULL;  srand(time(NULL));
 system("color 9f");
 p("\n Ingrese la cantidad de elementos:");
 s("%d",&cant);
 for(i=0;i<cant;i++)
 {
     // p("\n Ingrese dato:");s("%d",&num);
	 // insertar(&cabeza,num);
	  insertar(&cabeza,rand()%8+1,1);
 }
 p("\n\n Lista Ingresada\n\n");
 listar(cabeza);
 /*p("\n\n Ingrese el Nro a buscar:"); s("%d",&num);
 aux=buscar(cabeza,num);
 if(aux==NULL) p("\n El nro no fue encontrado");
	else p("\n El nro fue encontrado");*/
//if((cli=fopen(nomarchcli,"wb+"))==NULL)
  getch();
  if((archi=fopen("lista.dat","rb+"))==NULL)
      archi=fopen("lista.dat","wb+");
  cargar(cabeza,archi);// cargar de la lista al archivo
  p("\nLa Lista se cargo en el archivo !!!!\n");
  getch();
  rewind(archi);
  p("\n El contenido del archivo!!\n");
  mostrar(archi);

  getch();
 p("\n Presione una Tecla para borrar los nodos de la Lista!!!!"); getch();
 eliminar(&cabeza);
 getch();
 free(cabeza);
 if(cabeza)    listar(cabeza);
 else p ("\n\nLista vacía!!!\n\n\n");
 fclose(archi);
 // Guardar del archivo a la lista
 archi=fopen("lista.dat","rb+");
 cargar_lista(&cabeza,archi);
 p("\n Del archivo a la Lista!!\n\n");
 listar(cabeza);
 eliminar(&cabeza);
 p("\n En el archivo despues de eliminar la lista!!!\n");
 rewind(archi);
 mostrar(archi);
 getch();
 fclose(archi);
 return(0);
 }

//Cargar del archivo a la lista
void cargar_lista(nodo**l,FILE*x)
{
   nodo dato;
   fread(&dato,sizeof(nodo),1,x);
    while(!feof(x))
    {
   	   insertar(l,dato.dato,dato.cont);
   	   fread(&dato,sizeof(nodo),1,x);
    }
}

void insertar(nodo** x,int y,int z)
 {
	nodo *nuevo;
	nuevo=nuevonodo(y,z);
	if(*x==NULL)    *x=nuevo;
		   else if((*x)->dato>y)
                {
                 nuevo->sig=*x;
                 *x=nuevo;
                }
                else if (y==(*x)->dato)(*x)->cont++;
                      else insertar(&(*x)->sig,y,z);
 }
/*void insertar(nodo** x,int y)  // por la cola
 {
	nodo *nuevo;
	if(*x==NULL)
	{
	    nuevo=nuevonodo(y);
	    *x=nuevo;
	}	else insertar(&(*x)->sig,y);
 }
*/
/* void insertar(nodo** x,int y)   // por la cabeza
 {
	nodo *nuevo;
	nuevo=nuevonodo(y);
	if(*x==NULL) *x=nuevo;
		else
		     {
		         nuevo->sig=*x;
		         *x=nuevo;
		     }
 }
*/

nodo * nuevonodo(int x,int z)
{
 nodo *a;
 a=(nodo*)malloc(sizeof(nodo));
 a->dato=x;
 a->cont=z;
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

nodo*buscar(nodo*x,int y)
{
	if(!x) return (NULL);
	 else if(y==x->dato) return(x);
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

void mostrar(FILE*x)
{
   nodo dato_nuevo; //Aca guardo el nodo que recibo desde el archivo.
   fread(&dato_nuevo,sizeof(nodo),1,x);
   while(!feof(x))
   {
   	printf("%4d(%d)",dato_nuevo.dato,dato_nuevo.cont);
   	fread(&dato_nuevo,sizeof(nodo),1,x);
   }
}

/*void cargar(nodo*lista,FILE* x)
{
   while(lista!=NULL)
   {
   	fwrite(lista,sizeof(nodo),1,x);
      lista = lista->sig;
   }
}*/

void cargar(nodo*lista,FILE* x)
{
   if(lista!=NULL)
   {
   	fseek(x,0L,SEEK_END);//opcional si es R+
   	fwrite(lista,sizeof(nodo),1,x);
      cargar(lista->sig,x);
   }
}

