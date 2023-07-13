#include<stdlib.h>
#include<stdio.h>
#include<conio.h>
#include<time.h>
#include<string.h>

#define p printf
#define s scanf

typedef struct
{
  int cod_ciu;
  char nom_ciu[30];
  float t_min;
  float t_max;
} registro;


void inicio(FILE*);
void mostrar(FILE*);
void tecla(void);
void linea(int);

int main()
{
	FILE *archivo;
	char nombre[] = "Datos.dat";
	system("cls");
	srand(time(NULL));
	system("color 9f");
	if((archivo = fopen(nombre,"rb+")) == NULL)
    {
        archivo=fopen(nombre,"wb+");
    }
	p("\nEl archivo %s ha sido cargado!!\n",nombre);
	tecla();
	fflush(stdin);
	inicio(archivo);
	system("cls");
	mostrar(archivo);
	linea(80);
	tecla();
	system("cls");
	fclose(archivo);
	return(0);

}
void linea(int x)
{
 int i;
	for(i=1;i<x;i++)
	 p("*");
}

void inicio(FILE *x)
{
    int ban=0;
    int codCiudad;
    registro c;
     p("\nIngresar el codigo de ciudad: \n");
    s("%d",&codCiudad);
    do{
    fseek(x,0L,SEEK_SET);
    fread(&c,sizeof(registro),1,x);
    while(!feof(x) && ban == 0)
    {
        if(c.cod_ciu == codCiudad){
            fflush(stdin);
            ban = 1;
        }
        else {
            fread(&c,sizeof(registro),1,x);
        }
    }

    if (ban == 1) {
    p("\nLos datos ya fueron cargados\n");
   }

   else{
    c.cod_ciu=codCiudad;
    p("\nIngrese el nombre de la ciudad: \n");
    fflush(stdin);
    s("%[^\n]",&c.nom_ciu);
    do{
    p("\nIngrese la temperatura minima: \n");
    s("%f",&c.t_min);
    p("\nIngrese la temperatura maxima: \n");
    s("%f",&c.t_max);
    } while(c.t_max<c.t_min);
    fseek(x,0L,SEEK_END);
    fwrite(&c,sizeof(registro),1,x);
   }

   p("\nIngresar el codigo de ciudad o '0' para finalizar: \n");
    s("%d",&codCiudad);
    ban=0;
}   while(codCiudad>0);

}


void mostrar(FILE *x)
{
  registro c;
    rewind(x);
	system("cls");
	p("\n\n\t\t\tDatos \n\n");
	p("\nCodigo Nombre\t\t\t Minima Maxima \tAmplitud Termica\n");
	linea(80);
	fread(&c,sizeof(c),1,x);
	while(!feof(x))
	{
		p("\n%3d\t%-20s\t%6.2f\t%6.2f\t%6.2f\n",c.cod_ciu,c.nom_ciu,c.t_max,c.t_min,(c.t_max)-(c.t_min));
		fread(&c,sizeof(c),1,x);
	}
}

void tecla(void)
{
	p("\n\nPRESIONE CUALQUIER TECLA PARA CONTINUAR!!!");
	getch();
}




