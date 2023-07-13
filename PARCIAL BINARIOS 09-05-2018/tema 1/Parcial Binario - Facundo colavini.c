//facu_colavini@hotmail.com

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
} ciudades;

void  ingresar (FILE * ciu);
void mostrar (FILE*ciu);
int cargar (FILE * ,int);

int main(){
    ciudades c;
	FILE*ciu;
	char nomarch[]= "ciudad.dat";

	system("cls");
	srand(time(NULL));
	system("color 9f");

	if((ciu = fopen(nomarch,"wb+"))!= NULL)//CHECK APERTURA DE ARCHIVO
	{
	    p("\nEl archivo %s ha sido cargado!!\n",nomarch);
        ciu= fopen(nomarch,"wb+"); // apertura del archivo

    ingresar (ciu);
    mostrar (ciu);
    }
    else
    {
        p("No se pudo cargar el archivo");
    }

}



void  ingresar (FILE * ciu){

 ciudades c;

    int cod_ciudad;
    char nom_ciudad[30];
    float temp_min;
    float temp_max;


p("INGRESE EL CODIGO DE CIUDAD  O PRESIONE 0 PARA FINALIZAR:");
            s("%d",&cod_ciudad);
            system("cls");



if (cargar(ciu,cod_ciudad)==0){

    p("Existe el cod de ciudad");

do
{



            if (cod_ciudad!=0 && !feof(ciu))
            {
                    fflush(stdin);
                    p("INGRESE EL NOMBRE DE LA CIUDAD:");
                    gets(nom_ciudad);
                    strcpy(c.nom_ciu,nom_ciudad);

                    fflush(stdin);
                    p("INGRESE LA TEMPERATURA MIN:");
                    s("%f",&temp_min);

                    c.t_min =temp_min;

                    fflush(stdin);
                    p("INGRESE LA TEMPERATURA MAX:");
                    s("%f",&temp_max);
                    c.t_max=temp_max;
                      if (c.t_max>c.t_min){
                        c.t_max=c.t_max - c.t_min;
                        fseek(&c,sizeof(c),SEEK_SET);
                        fwrite(&c,sizeof(c),1,ciu);
                      }
            }




        }while (cod_ciudad!=0);
}
}

int cargar (FILE * ciu,int cod_ciudad)
{
ciudades c;
int flag=0;

    rewind(ciu);
    fread(&c,sizeof(c),1,ciu);

    while (!feof(ciu))
    {
        if (c.cod_ciu==cod_ciudad)
        {
        flag=1;

        break;
        }

        else
        {
            fread(&c,sizeof(c),1,ciu);
        }

    }
    p("%d",flag);
        return flag;

 }



void mostrar (FILE * ciu){

ciudades c;

 rewind(ciu);



   // p ("\n|Temperatura Min|Temperatura Max| Amplitud Termica  | " );

    fread(&c,sizeof(c),1,ciu);
    while (!feof(ciu)){
        p("\n|%5d| %18s  |%5d  |%10d   |",c.cod_ciu,c.nom_ciu,c.t_min,c.t_max,c.t_max);
        p("n------------------------------------------------------------------------");
        fread(&c,sizeof(c),1,ciu);

}

}
