#include<stdio.h>
#include<conio.h>
#include<stdlib.h>
#define p printf
#define s scanf
// Captura un texto de varios renglones en un archivo
// Copia en un 2º archivo hasta EOF
// Probar apertura W+ R+
void mostrar(FILE*);
void cargar(FILE*);
void grabar(FILE*,FILE*);
int error(char*);
int main()
{
 FILE *origen, *destino;
 char nom1[80], nom2[80];// nombre físico de los archivos
 system("cls");
 p("\n Ingrese el nombre del archivo a crear:"); s("%[^\n]", nom1);
 fflush(stdin);
 if((origen=fopen(nom1,"w+"))==NULL)  exit(error(nom1)) ;// crea el archivo para escritura y lectura;
 p("\n El archivo %s se ha abierto satisfactoriamente",nom1);
 cargar(origen);
 p("\n Presione una tecla para visualizar el contenido del archivo:%s\n\n",nom1);
 rewind(origen);
 mostrar(origen); getch();
 fflush(stdin);
 p("\n Ingrese el nombre del archivo destino a crear:"); s("%[^\n]", nom2);
 if((destino=fopen(nom2,"w+"))==NULL)  exit(error(nom2));
 p("\n El archivo %s se ha abierto satisfactoriamente",nom2);
rewind(origen);
 grabar(origen, destino);
 p("\n El archivo destino es :\n\n");
 p("\n El archivo %s se ha abierto satisfactoriamente\n\n",nom2);
 p("\n Su contenido es :\n\n");
rewind(destino);
 mostrar(destino);
 fclose(origen);
 fclose(destino);
 getch();
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

     /* void grabar(FILE *x,FILE *y) //  caracter a caracter
      {
          char c[80];
         while(!feof(x))
          {
              c=fgetc(x);  //probar fgets
              fputc(c,y);
          }

      }*/

 void grabar(FILE *x,FILE *y)
      {
          char c[80];

        while(fgets(c,81,x)!=NULL)
        {
            fputs(c,y); // linea a linea
           // fputc('\n',y);
        }
      }
