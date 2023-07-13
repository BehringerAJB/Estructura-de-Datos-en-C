#include<stdio.h>
#include<conio.h>
#define p printf
#define s scanf
// Lee caracteres almacenados en texto01.txt
//los muestra caracter a caracter y por linea
int main()
{
 FILE *archivo;
char ch, cadena[81];
 char* nombre="texto01.txt";// nombre físico del archivo
 if((archivo=fopen(nombre,"r"))==NULL)
        p("\n\n***El archivo %s no pudo abrirse ***\n",nombre);
        else
        {
            // lectura por caracter
            p("\n\n Este es el contenido del archivo %s caracter a caracter\n\n",nombre);
            while((ch=getc(archivo))!=EOF)
                p("%c",ch);
              p("\n\n Este es el contenido del archivo %s renglon a renglon\n\n",nombre);
              rewind(archivo);
            // lectura por linea
              while(fgets(cadena,81,archivo) )  // Almacena en un cadena !=NULL)  hasta \n n-1 o salto de linea
               p("%s",cadena);

                p("\n\n**FIN**\n"); getch();

            fclose(archivo)    ;
        }
        return(0);
}
