///Un programa que lee una cadena de texto y la trabaja
#include<stdio.h>
#include<conio.h>
#include<stdlib.h>
#define p printf
#define s scanf
int dim(char[]);
char mayor(char);
void inverso(char[],int);
void recu(char[],int);
void mayu(char[],char[]);
int main()
{
 char cad[80]="En un lugar de la Mancha";
 char aux[80];
 int i;
 system("cls");system("color 9f");
 p("\nCADENA ORIGINAL:\n%s",cad);
 p("\n\nCADENA CARACTER A CARACTER!!!\n");
 i=0;
 while(cad[i])
    p("%3c",cad[i++]);

 p("\nLARGO DE LA CADENA:%d",dim(cad));
 p("\nAL REVES\n");
 inverso(cad,dim(cad));
 p("\nAL REVES RECURSIVO\n");
 recu(cad,0);
 mayu(cad,aux);
 p("\nCADENA EN MAYUSCULAS\n");
 p("%s",aux);
 getch();
 system("cls");
 return(0);
}
void mayu(char x[],char y[])
{
   int i=0;
    while(x[i])
    {
      y[i]=mayor(x[i]);
      i++;
    }
    y[i]='\0';
}
char mayor(char x)
{
  return((x>='a'&&x<='z')?x-32:x);
}

void inverso(char x[],int y)
{
 while(y>=0)
 {
  p("%c",x[y--]);
  //y--;
 }
}
void recu(char x[],int y)
{
  if(x[y])
    recu(x,y+1);
  p("%c",x[y]);
}

int dim( char x[])
{
  int i;
  while(x[i++]);
  return(i-1);
}
