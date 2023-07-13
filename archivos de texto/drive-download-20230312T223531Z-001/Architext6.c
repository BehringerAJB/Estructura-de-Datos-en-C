#include<stdio.h>
#include<conio.h>
#include<stdlib.h>
#include<string.h>
#define p printf // no funca
#define s scanf
// Captura un texto de varios renglones en un archivo
//  Borra las la palabra Nº del renglón Nº
void mostrar(FILE*);
void cargar(FILE*,FILE*);
int contar(char[]);
int error(char*);
int dim(char[]);
void larga(char*,char*);
int main()
{
 FILE *archivo,*archaux;
 char nom1[80]="c:\\pipo.txt",cad[80], nom2[80]="c:\\copia.txt",palmax[80];// nombre físico del archivo
 int j,cuenta;
 system("cls");
 fflush(stdin);
archivo=fopen(nom1,"r+");
archaux=fopen(nom2,"w+");
 p("\n El archivo %s se ha abierto satisfactoriamente",nom1);
 p("\n El archivo %s se ha abierto satisfactoriamente",nom2);
 p("\n Presione una tecla para visualizar el contenido del archivo:%s\n\n",nom1); getch();
  system("cls");
 rewind(archivo);
 p("\n El contenido del archivo %s es:\n\n",nom1);
 mostrar(archivo); getch();
 rewind(archivo);
 p("\n El contenido del archivo %s es:\n\n",nom2);
cargar(archivo,archaux);
rewind(archaux);
mostrar(archaux);
p("\n El contenido del archivo %s es:\n\n",nom1);
rewind(archivo);
mostrar(archivo);

fclose(archaux);
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

void cargar(FILE*x, FILE*y)
{
  int hasta=0, desde=0,i=1;
  char cad[81];
   while(fgets(cad,81,x)!=NULL)
    {
             hasta=palabra(cad,i);
      // p("palabra vale:%d",hasta);
       strcpy(cad,cad+hasta);
      // p("%s",cad); getch();
       //strcpy(cad+desde,cad+hasta);
        fputs(cad,y);
        ++i;
       // desde=hasta;
     }
}

int palabra(char x[],int y)
{
    int i=0,j;
    for(j=0;j<y;j++)
    {
     while(x[i] !=' ') i++;
      //  p("%3d",i); getch();
        i++;
    }
    return(i) ;
}


/*int contar(char *x)
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
int dim(char *x)
{
    int i=0;
    while(x[i]) i++;
    return (i);
}

void larga (char*x,char*y)
{
    int i=0,j,maxi=0;
    char aux[80];
    while(x[i])
    {
        while(x[i++]==' ');
        j=0;
        i--;
        while((x[i]!=' ')&&(x[i]))
          aux[j++]=x[i++];
         aux[j]='\0';
         if(dim(aux)>maxi)
         {
             maxi=dim(aux);
             strcpy(y,aux);
         }
    }
}
*/


