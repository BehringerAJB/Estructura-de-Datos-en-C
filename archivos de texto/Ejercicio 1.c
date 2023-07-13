#include<stdio.h>
#include<conio.h>
#define p printf
#define s scanf
// Ingresar caracteres en un archivo hasta [Enter]
//verificar el archivo con el bloc de notas
int main()
{
    FILE *archivo;
    char ch;
    char* nombre="texto01.txt";// nombre físico del archivo
    if((archivo=fopen(nombre,"w"))==NULL)
        p("\n\n***El archivo %s no pudo abrirse ***\n",nombre);
    else
    {
        p("\n\n Ingrese caracteres hasta [Enter]  ");
        while((ch=getchar())!='\n')
            putc(ch,archivo); // almacena en el archivo hasta [ENTER]
    fclose(archivo);
    }

    return 0;

}
