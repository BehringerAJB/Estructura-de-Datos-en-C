#include<stdlib.h>
#include<stdio.h>
#include<conio.h>
#include<string.h>

#define p printf
#define s scanf

typedef struct{
int cod_ciu;
char nom_ciu[30];
float t_min;
float t_max;
} registro;

int error(char *);
void ingresar(FILE *);
void mostrar(FILE *);

int main(){
FILE *ciudades;
char nomArchCiu[]= "ciudades.dat";

system("cls");
system("color 9f");

if ((ciudades=fopen(nomArchCiu,"wb+"))==NULL)
    exit(error(nomArchCiu));
    p("\nEl archivo %s ha sido cargado!!\n",nomArchCiu);

ingresar(ciudades);
mostrar(ciudades);

return 0;
}

void mostrar(FILE * x){
    registro c;
    float amplitudter;

    rewind(x);
    system("cls");

    p("\nCodigo de ciudad\tNombre de la ciudad\tTemp min\tTemp Max\tAmplitud\n");

    fread(&c,sizeof(c),1,x);

    amplitudter=c.t_max-c.t_min;

    while (!feof(x)){
        p("%d \t\t\t %s \t %f \t\t %f \t\t %f\n",c.cod_ciu,c.nom_ciu,c.t_min,c.t_max,amplitudter);
        fread(&c,sizeof(c),1,x);
        amplitudter=c.t_max-c.t_min;
    }
}


void ingresar(FILE *ciu){
registro ciudadA, ciudadB; //ciudadA=en el archivo //ciudadB = variables

do {
    p("\nIngrese el codigo de la ciudad. Para finalizar la carga ingrese el 0:\n");
    s("%d",&ciudadB.cod_ciu);

    fseek(ciu,ciudadA.cod_ciu * sizeof(ciudadA),SEEK_SET);
    fread(&ciudadA,sizeof(ciudadA),1,ciu);

    if (ciudadB.cod_ciu==ciudadA.cod_ciu){
        p("Ese codigo ya fue ingresado\n");
    }

    else{
        p("Ingrese el nombre de la ciudad:\n");
        s("%s",&ciudadB.nom_ciu);

        if(ciudadB.nom_ciu==ciudadA.nom_ciu){
        p("Esa ciudad ya fue ingresada\n");
    }
    else{
        p("Ingrese la temp minima:\n");
        s("%f",&ciudadB.t_min);
        p("Ingrese la temp maxima:\n");
        s("%f",&ciudadB.t_max);
    }
        fseek(ciu,0L,SEEK_END);
        fwrite(&ciudadB,sizeof(ciudadB),1,ciu);
    }

} while (ciudadB.cod_ciu!=0);

}


int error(char *x)
{
     fprintf(stderr,"no se puede abrir el archivo %s",x);
     return(1);
}
