/*Se tiene una pila con información de los artículos que una empresa vende.
De cada artículo se sabe el código, la descripción, la cantidad en stock y el precio.
Se tiene otra pila con igual información de artículos que la empresa acaba de comprar.
Hacer una función que actualice la primera con los datos de la segunda.
Si en la segunda pila hay algún artículo que no está en la primera, hay que agregarlo al final de la pila.
En cambio si el artículo está hay que sumarle la cantidad de stock que trae el artículo de la segunda.
Pila Original

            Código	Descripción	        Cantidad	            Precio
            100235	Nebulizador	            50	                145.20
            100312	Tensiómetro	           120	                159.35
            200045	Caloventor	            35	                 46.00
            200511	Estufa halógena	    15	                 72.58
            400805	Afeitadora	           100	                215.40
            400322	Cortadora de cabello   210	                 29.45
Pila de compras
            Código	Descripción	        Cantidad	            Precio
            500100	Reproductor DVD	24	                200.53
            100312	Tensiómetro	            50	                159.35
            500235	Televisor 21”	        30	                565.60
            200511	Estufa halógena	    30	                  72.58

*/

#include<stdio.h> // pila dinámica común con menú
#include<conio.h> //01-09-2016
#include<stdlib.h>
#include<string.h>
#define p printf
#define s scanf;

typedef struct
{
	long int cod;
	char desc[25];
	int cant;
	float pre;
} registro;

typedef struct elemento
{
  registro datos;
  struct elemento * sig;
} nodo;
nodo * nuevonodo(nodo );
nodo* ingresarDato(int,registro[]);
int pilaVacia(nodo*);
 void volcar(FILE*,nodo**);
void apilar(nodo**,nodo*);
nodo desapilar(nodo**);
void mostrar(FILE*);
void mostrarDato(nodo);
void listarPila(nodo*,char[]);
void eliminarPila(nodo*);
void poner(nodo **,nodo);
nodo *sacapone(nodo);
void cargapila(nodo**,registro[],int);
void insertar(nodo**,nodo);
int menu(void);

int main()
{
 FILE *archivo;
 nodo *pori,*q,*qc,dato,*pcomp,*auxpori,datoc,*lista,*auxi;//*auxpcomp
 int op,ban=-1,cargar=0;
 char* nombin="datos.dat";
 registro info[]={{100235,"Nebulizador",50,145.20},{100312,"Tensiometro",120,159.35},
	             {200045,"Caloventor",35,46.00},{200511,"Estufa halogena",15,72.58},
	             {400805,"Afeitadora",100,215.40},{400322,"Cortadora de Cabello",210,29.45}}; // Datos Originales

 registro infocom[]={{500100,"Reproductor de DVD",24,200.53},{100312,"Tensiometro",50,159.35},
	             {500235,"Televisor 21",30,565.60},{200511,"Estufa halogena",30,72.58}}; // Datos Compras
  pori=NULL;
  pcomp=NULL;
  auxpori=NULL;
  lista=NULL;
  archivo=fopen(nombin,"wb+");
  system("color 9f");
    do
	 {
    op=menu();
    switch(op)
    {
        case 1:
             if(!cargar)
             {
                cargapila(&pori,info,6);
                cargapila(&pcomp,infocom,4);
                system("cls");
                p ("\n SE HAN CARGADO LOS DATOS!!!");
                p("\n PRESIONE UNA TECLA PARA VOLVER AL MENU PRINCIPAL!!!");
                cargar=1;

             } else
                    {
                     system("cls");
                     p("\n LAS PILAS YA HAN SIDO CARGADAS PREVIAMENTE!!!");
                     p("\n PRESIONE UNA TECLA PARA VOLVER AL MENU PRINCIPAL!!!");
                     }
               getch();
            break;
         case 2:
            if(pilaVacia(pcomp))
            {
                while(pcomp)
                {
                   datoc=desapilar(&pcomp);
                   qc=sacapone(datoc);
                   ban=0;
                   while(pori)
                   {
                     dato=desapilar(&pori);
                     if(dato.datos.cod==datoc.datos.cod)
                       {
                         dato.datos.cant+=datoc.datos.cant;
                         ban=1;
                       }
                        q=sacapone(dato);
                        apilar(&auxpori,q);
                   }
                      if(ban==0) apilar(&auxpori,qc);

                     while(auxpori)
                     {
                         dato=desapilar(&auxpori);
                         q=sacapone(dato);
                         apilar(&pori,q);
                     }
                }
            }

            if(ban!=-1)
            {
             system("cls");
             p("\n YA SE HAN ACTUALIZADO LOS DATOS");
             p("\n PRESIONE UNA TECLA PARA VOLVER AL MENU PRINCIPAL!!!");
            }

             getch();
                    break;
         case 3:
                system("cls");
                if(ban==-1)
                {
                    if(pilaVacia(pori)) listarPila(pori,"ORIGINAL !!!");
                    if(pilaVacia(pcomp)) listarPila(pcomp,"DE COMPRAS");
                }   else if(pilaVacia(pori)) listarPila(pori,"ACTUALIZADA !!!");
                 break;
         case 4:
                if(pilaVacia(pori))
                {
                system("cls");
                 p("\n PRESIONE UNA TECLA PARA CARGAR EL ARCHIVO !!!!\n"); getch();
                  system("cls");
                  while(pori)
                   {
                   datoc=desapilar(&pori);
                   insertar(&lista,datoc);
                   }
                  listarPila(lista,"pipo");
                  archivo=fopen(nombin,"wb+");
                  volcar(archivo,&lista);
                  p("\n LA PILA FUE DESAPILADA EN EL ARCHIVO");
                  p("\n PRESIONE UNA TECLA PARA  VER EL ARCHIVO !!!!\n"); getch();
                  system("cls");
                  fclose(archivo);
                  archivo=fopen(nombin,"rb+");
                  mostrar(archivo);
                  getch();
                }

                 p("\n\n PRESIONE UNA TECLA PARA VOLVER AL MENU PRINCIPAL!!!"); getch();
		}
	 }while(op<5);

	if(pori!=NULL)
		{
		   system("cls");
		   eliminarPila(pori);
			getch();
		}

	if(pcomp!=NULL)
		{
		   system("cls");
		   eliminarPila(pcomp);
			getch();
		}
    free(pcomp);
    free(auxpori);
    free(pori);
    fclose(archivo);
    system("cls");
	return 0;
}

void poner(nodo **x,nodo y)
{
    nodo aux;
    if(*x==NULL) **x=y;
     else poner(&(*x)->sig,y);
}
void volcar(FILE*x,nodo**y)
{
  registro r;
  nodo datoc;
  rewind(x);
  while(*y)
  {
      datoc=desapilar(y);
      r.cod=datoc.datos.cod;
      strcpy(r.desc,datoc.datos.desc);
      r.cant=datoc.datos.cant;
      r.pre=datoc.datos.pre;
      fseek(x,0L,SEEK_END);
	 fwrite(&r,sizeof(r),1,x);
  }
}
void mostrar(FILE*x)
{
   registro r;
    p("\n\t\t CONTENIDO DE LOS REGISTROS EN EL ARCHIVO\n\n");
    p("\n\n Codigo\t\tNombre\t\t\tCantidad\t\tPrecio\n\n");
    rewind(x);
    fread(&r,sizeof(r),1,x);
	while(!feof(x))
	{
		p("\n\n%3d\t\t%-20s\t%6d\t\t\t%6.2f",r.cod,r.desc,r.cant,r.pre);
		fread(&r,sizeof(r),1,x);
	}
}

void cargapila(nodo**x,registro y[], int z)
{
    int i;
    nodo *q;
    for(i=0;i<z;i++)
    {
          q=ingresarDato(i,y);
          apilar(&(*x),q);
     }
}
nodo* sacapone(nodo x)
{
  nodo* qx;
       qx=(nodo*)malloc(sizeof(nodo));
       qx->datos.cod=x.datos.cod;
       strcpy(qx->datos.desc,x.datos.desc);
       qx->datos.cant=x.datos.cant;
       qx->datos.pre=x.datos.pre;
       qx->sig=NULL;

        return(qx);
}

nodo* ingresarDato(int x,registro info[])
{
	     nodo *q;
	     q=(nodo*)malloc(sizeof(nodo));
	     q->datos.cod=info[x].cod;
         strcpy(q->datos.desc,info[x].desc);
         q->datos.cant=info[x].cant;
         q->datos.pre=info[x].pre;
         q->sig=NULL;

	 return q; //getch();
}

int pilaVacia(nodo*x)
{
    if(x==NULL)
	 {
		system("cls");
		printf("PILA VACIA\n\n");
		system("pause");
		return 0;
	 }
}
void insertar(nodo** x,nodo y)
 {
	nodo *nuevo;
	nuevo=nuevonodo(y);
	if(*x==NULL)    *x=nuevo;
       else if((*x)->datos.cod>y.datos.cod)
            {
             nuevo->sig=*x;
             *x=nuevo;
            }
              else insertar(&(*x)->sig,y);
 }
nodo * nuevonodo(nodo x)
{
 nodo *a;
 a=(nodo*)malloc(sizeof(nodo));
 a->datos.cod=x.datos.cod;
 strcpy(a->datos.desc,x.datos.desc);
 a->datos.cant=x.datos.cant;
 a->datos.pre=x.datos.pre;
 a->sig=NULL;
 return a;
 }



void apilar(nodo**x,nodo*y)
{
	 y->sig=*x;
	*x=y;
}

nodo desapilar(nodo**x)
{
	nodo dato,*aux;
    aux=*x;
	dato=**x;
	*x=(*x)->sig;
	 free(aux);
	 return dato;
}

void mostrarDato(nodo dato)
{
	 system("cls");
	 printf("\n\n\nDato desapilado: %ld",dato.datos.cod);
	 printf("\n\n");
	 system("pause");
}

void listarPila(nodo*x,char y[])
{
   	 printf("CONTENIDO DE LA PILA %s\n\n",y);
	 while(x)
	 {
		printf("\n%ld %-25s\t%6d\t%6.2f\n",x->datos.cod,x->datos.desc,x->datos.cant,x->datos.pre);
		x=x->sig;
	 }
    printf("\n\n");
    system("pause");
    printf("\n\n");
}

void eliminarPila(nodo*x)
{
	nodo *aux;
	 if(x)
	 {
		aux=x;
		printf("\n\nDato Eliminado: %d \n\n",x->datos.cod);
		system("pause");
		free(aux);
		eliminarPila(x->sig);
	 }

}
int menu(void)
{
	int op;
	 do
	 {
		system("cls");
		printf("\n\t\t\t\t MENU DE OPCIONES (PILAS)\n\n");
		printf("\n\n\t\t\t\t - CARGAR  DATOS     <1>\n");
		printf("\n\n\t\t\t\t - AGREGAR DATOS     <2>\n");
		printf("\n\n\t\t\t\t - LISTAR DATOS      <3>\n");
		printf("\n\n\t\t\t\t - CARGAR EN ARCHIVO <4>\n");
		printf("\n\n\t\t\t\t - BORRAR Y SALIR    <5>\n");
		printf("\n\n\t\t\t\t - INGRESE OPCION [1-5]:  ");
		scanf("%d",&op);
	 }while(op<1||op>5);
	 return op;
}

