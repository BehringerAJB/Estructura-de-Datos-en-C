#include<stdio.h>
#include<conio.h>
#define p printf
#define s scanf
// Captura un texto de varios renglones
// W+  escritura como archivo nuevo y además lee su contenido
// Probar apertura W+ R+
int main()
{
 FILE *archivo;
 char cadena[81],* nombre="texto101.txt";// nombre físico del archivo
 if((archivo=fopen(nombre,"w+"))==NULL)  // crea el archivo para escritura y lectura
        p("\n\n***El archivo %s no pudo abrirse ***\n",nombre);
        else
        {
            p("\n El archivo %s está abierto y vacio para ingresar texto",nombre);
            p("\n Para ingresar datos finalice cada linea de texto con [ENTER]\n");
            p("\n Para finalizar el ingreso de datos  introduzca marca de fin de archivo EOF [^Z]\n");
            while(gets(cadena)!=NULL)// hasta fin de archivo
            {
                fputs(cadena,archivo);
                fputc('\n',archivo);
            }
           p("\n Presione cualquier tecla para visualizar el contenido del archivo:%s\n",nombre);
           getch(); system("cls");
           rewind(archivo);  /// me posiciono al principio del archivo
           while(fgets(cadena,81,archivo) )  //!=NULL)  hasta \n n-1 o salto de linea
               p("%s",cadena);
          fclose( archivo);
        }
        return(0);
}
