#include<stdlib.h>
#include<stdio.h>
#include<conio.h>
#include<time.h>
#include<string.h>
#define p printf
#define s scanf

void cargar(FILE *);
void mostrar(FILE *);
void tecla();

typedef struct
{
    int cod_ciu;
    char nom_ciu[30];
    float t_min;
    float t_max;
}registro;

int main(){
FILE *archivo;
char *nomarch="archivo.dat";
system("cls");
system("color 4f");

archivo=fopen(nomarch,"ab+");
p("\n ARCHIVO ABIERTO PARA ESCRITURA\n\n");
tecla();
cargar(archivo);
tecla();
p("\n PRESIONE UNA TECLA PARA MOSTRAR LAS TEMPERATURAS DE LAS CIUDADES:\n\n",214);
getch();
mostrar(archivo);
tecla();

fclose(archivo);

getch();

return 0;
}


void cargar(FILE *x)
{
registro datos;
int b,cod;
float tmin, tmax;


    p("\n INGRESE CODIGO DE LA CIUDAD, 0 PARA SALIR-> ");
    fflush(stdin);
    s("%d",&cod);
    while(cod!=0){

            rewind(x);
            b=0;
            fread(&datos, sizeof(datos), 1, x);

            while(!feof(x) && b==0)
                {

                if(cod!=datos.cod_ciu){
                    fread(&datos, sizeof(datos), 1, x);
                }

                else{
                    p("\n LA CIUDAD QUE INTENTA CARGAR YA FUE INGRESADA ANTERIORMENTE, INTENTE CON OTRA");
                    getch();
                    b = 1;
                    break;
                }

            }

            if(b==0){
                fseek(x,0L,SEEK_END);
                fflush(stdin);
                datos.cod_ciu=cod;

                p("\n INGRESAR NOMBRE DE LA CIUDAD -> ");
                s("%[^\n]", datos.nom_ciu);

                do{
                p("\n INGRESAR TEMPERATURA MINIMA DE LA CIUDAD %s -> ", datos.nom_ciu);
                fflush(stdin);
                s("%f",&tmin);
                datos.t_min = tmin;

                p("\n INGRESAR TEMPERATURA MAXIMA DE LA CIUDAD %s -> ", datos.nom_ciu);
                s("%f",&tmax);

                if(tmax<tmin){
                        printf("LA TEMPERATURA MINIMA NO PUEDE SER MAYOR A LA TEMPERATURA MAXIMA!!\n");

                }
                }while(tmax<tmin);

                datos.t_max = tmax;

                fwrite(&datos, sizeof(datos), 1, x);

            }

            system("cls");
                p("\n INGRESE CODIGO DE LA CIUDAD, 0 PARA SALIR ");
                s("%d",&cod);
    }
}


void mostrar(FILE *x)
{
registro r;
rewind(x);

    p("\n COD \t CIUDAD\t\t  TEMP MINIMA\t  TEMP MAXIMA\t  AMPLITUD\n");

    fread(&r,sizeof(registro),1,x);

 while(!feof(x))
 {
    p("\n %3d\t%-20s %.2f%\t    %.2f%\t   %.2f%\n\n",r.cod_ciu,r.nom_ciu,r.t_min,r.t_max,(float)r.t_max-r.t_min);
    fread(&r,sizeof(registro),1,x);
 }
}


void tecla(void)
{
 p("\n PRESIONE UNA TECLA PARA CONTINUAR\n");
 getch();
 system("cls") ;
}
