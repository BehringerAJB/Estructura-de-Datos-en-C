#include<stdio.h>
#include<conio.h>
#include<stdlib.h>
#define p printf
#define s scanf
// Captura un texto de varios renglones en un archivo
//  Cuenta las palabras por renglones
void mostrar(FILE*);
void cargar(FILE*);
int contar(char[]);
int error(char*);
int main()
{
 FILE *archivo;
 char nom1[80],cad[80];// nombre físico del archivo
 int j,cuenta;
 system("cls");
 p("\n Ingrese el nombre del archivo a crear:"); s("%[^\n]", nom1);
 fflush(stdin);
 if((archivo=fopen(nom1,"w+"))==NULL)  exit(error(nom1)) ;// crea el archivo para escritura y lectura;
 p("\n El archivo %s se ha abierto satisfactoriamente",nom1);
 cargar(archivo);
 p("\n Presione una tecla para visualizar el contenido del archivo:%s\n\n",nom1); getch();
  system("cls");
 rewind(archivo);
 p("\n El contenido del archivo %s es:\n\n",nom1);
 mostrar(archivo); getch();
 rewind(archivo);
 j=0;
while(fgets(cad,81,archivo)!=NULL)
{
   cuenta=contar(cad);
   p("\n En el renglon %d cantidad de palabras:%d",++j,cuenta);
}
p("\n \nPresione una tecla para salir del Programa******");
getch();
fclose(archivo);

 return(0);
}

void mostrar(FILE *x)
{
    char cad[80];
    while(fgets(cad,81,x)!=NULL)
    p("%s",cad);
    }

    int error(char*x)
    {
        fprintf(stderr, "No se pudo abrir el archivo %s",x);
        return(1);
    }

void(cargar(FILE*x))
{
   char cad[81];
    p("\n Para ingresar datos finalice cada linea de texto con [ENTER]\n");
            p("\n Para finalizar el ingreso de datos  introduzca marca de fin de archivo EOF [^Z]\n");
            while(gets(cad)!=NULL)// hasta fin de archivo
            {
                fputs(cad,x);
                fputc('\n',x);
            }
}



int contar(char *x)
{
    int contapal=0,i=0;
    while(x[i]!='\n' )
    {
       while(x[i]==' ' )  i++;
     ++contapal;
        while((x[i]!=' ')&& (x[i]!='\n' )) i++;

    }
return(contapal);
}
