#include<stdio.h> // Carga de un archivo de Texto separado los campos por comas
#include<stdlib.h> // Convierte e inserta en un Archivo binario
#include<conio.h> //
#include<string.h>
#define p printf
#define s scanf
typedef struct
{
 int cod_cli;
 char nom_cli[30];
 int cuenta;
 } registro;

typedef struct lista
{
registro datos;
struct lista*sig;
} nodo;

void cargar_lista(nodo**,FILE*);
void insertar(nodo**,int,char[],int);
nodo * nuevonodo(int,char[],int);
int sacapal(char [],int d, char [] );
void cargar(FILE*,int,char[],int,char[]);
void cargarar(nodo*,FILE*);
void listar(nodo*);
void tecla(void);
void eliminar(nodo**);
void mostrar(FILE*);
int main()
{

 FILE *archivo,*binario,*orden;
 char* nombre="texto.txt";// nombre físico del archivo
 char* nombin="datos.dat";
 char* nomord="ordenar.dat";
 char cadena[80],nom_cli[80],pri[80],seg[80],ter[80];
 int cod, ventas,i,j;
 nodo*cabeza;
 system("color 9f");
 cabeza=NULL;
 cadena[0]='\0';nom_cli[0]='\0';pri[0]='\0';seg[0]='\0';ter[0]='\0'; // vacío las cadenas
 if((archivo=fopen(nombre,"r+"))==NULL) p("\n\n***El archivo %s no pudo abrirse ***\n",nombre); // crea el archivo para escritura y lectura
   else
    {
        p("\n CONTENIDO DEL ARCHIVO DE TEXTO\n\n");
         while(fgets(cadena,81,archivo) )  //!=NULL)  hasta \n n-1 o salto de linea
           p("%s",cadena);
         rewind(archivo);
         tecla();
         p("\n\n CONTENIDO DE LOS CAMPOS EN MEMORIA");
         p("\n\n C%cDIGO\t\tNOMBRE\t\t\tCUENTA\n\n",224);
         while(fgets(cadena,81,archivo) ) // Recorro el Archivo de Texto
         {
              i=0;
              while(cadena[i]!='\0')
              {
                   i=sacapal(cadena,0,pri); // Saco la primer palabra y la convierto a entero (COD)
                   cod=atoi(pri);
                   p("%3d",cod); getch();
                   i+=1;
                   i=sacapal(cadena,i,seg); // Saco la segunda palabra y la guardo en una variable
                   p("\t\t%-20s ",seg);     // que será el nombre del cliente
                   getch();
                   i++;
                   i=sacapal(cadena,i,ter); // Saco la tercer palabra y la convierto a entero (CUENTA)
                   ventas=atoi(ter);
                   j=0;
                   p("\t%6d",ventas);

              } // Salgo del renglón
           ///Inserto en orden en la lista sin repeticiones de registros
           insertar(&cabeza,cod,seg,ventas);

           p("\n\n");
          }
      p("\n\n Se cargo la lista !!!!\n\n"); getch();
      listar(cabeza);
      getch();
      orden=fopen(nomord,"wb+");//Elimina el archivo anterior
      ///Cargo la lista en el archivo
      cargarar(cabeza,orden);
      p("\n\n LA LISTA SE CARGO EN EL ARCHIVO %s !!!!\n",nomord);
      rewind(orden);
      mostrar(orden);
      getch();
      eliminar(&cabeza);
      fclose(orden);
      } // else de la apertura de Archivo
 tecla();
 system("cls");

 free(cabeza);
 fclose(archivo);
 return(0);
}

 void eliminar(nodo**x)
 {
  nodo*aux;
  if(*x)
  {
	 aux=*x;
	 *x=aux->sig;
	 free(aux);
	 eliminar(x);
  }
}

void tecla(void)
{
	p("\n\nPresione cualquier tecla para continuar!!!");
	getch();
}
int sacapal(char x[],int d, char y[] )
{
   int ter=0,i,j=0;
   i=d;
   while(x[i]!=','&&x[i]!='\0')
     y[j++]=x[i++];
    y[j]='\0';
   return(i);
}

void mostrar(FILE*x)
{
   registro r;
    p("\n CONTENIDO DE LOS REGISTROS EN EL ARCHIVO\n\n");
    p("\n\n C%cDIGO\t\tNOMBRE\t\t\tCUENTA\n\n",224);
    rewind(x);
    fread(&r,sizeof(r),1,x);
	while(!feof(x))
	{
		p("\n\n%3d\t\t%-20s\t%6d",r.cod_cli,r.nom_cli,r.cuenta);
		fread(&r,sizeof(r),1,x);
	}
}

nodo * nuevonodo(int x,char y[],int z)
{
 nodo *a;
 a=(nodo*)malloc(sizeof(nodo));
 a->datos.cod_cli=x;
 strcpy(a->datos.nom_cli,y);
 a->datos.cuenta=z;
 a->sig=NULL;
 return a;
 }

void insertar(nodo** x,int y,char nc[],int cu)
 {
	nodo *nuevo;
	nuevo=nuevonodo(y,nc,cu);
	if(*x==NULL) *x=nuevo;
       else if((*x)->datos.cod_cli>y)
            {
             nuevo->sig=*x;
             *x=nuevo;
            }
            else if (y==(*x)->datos.cod_cli)((*x)->datos.cuenta)+=cu;
                  else insertar(&(*x)->sig,y,nc,cu);
}

void listar(nodo*x)
{
	if(x)
	{	 p("%4d\t\t%-20s\t %6d",x->datos.cod_cli,x->datos.nom_cli,x->datos.cuenta);
	     p("\n\n");
	 listar(x->sig);
	 }
}

void cargarar(nodo*lista,FILE* x) /// Carga de la lista al Archivo
{
  registro r;
  if(lista!=NULL)
   {
    r.cod_cli=lista->datos.cod_cli;
    strcpy(r.nom_cli,lista->datos.nom_cli);
    r.cuenta=lista->datos.cuenta;
   	fwrite(&r,sizeof(r),1,x);
    cargarar(lista->sig,x);
   }
}

