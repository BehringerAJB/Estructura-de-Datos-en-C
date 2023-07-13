#include <stdio.h>
#include <string.h>

#define out printf
#define in scanf

typedef struct {
    int cod_ciu;
    char nom_ciu[30];
    float t_min;
    float t_max;
} registro;

void cargar (int cod, char[30], float, float, registro);
int chequearSiEsta(FILE*, registro, int, int);
int ingresar3 (int, char[30], float, float);

int main () {
int cod;
char nombre[30];
float tMin;
float tMax;
registro aux;
ingresar3(cod,nombre,tMin,tMax);
return 0;}


void cargar (int cod, char nombre[30], float tMin, float tMax, registro aux) {
        aux.cod_ciu = cod;
        fflush(stdin);
        out("Ingrese un nombre\n");
        in("%s", nombre);
        strcpy(aux.nom_ciu, nombre);
        fflush(stdin);
        out("Ingrese una temp minima\n");
        in("%f",&tMin);
        aux.t_min = tMin;
        out("Ingrese una temp maxima\n");
        in("%f",&tMax);
        aux.t_max = tMax;
        out("este es el primero(dentro de cargar)\n%d\t%s\t%f\t%f\n", aux.cod_ciu,aux.nom_ciu,aux.t_min,aux.t_max);
}

int chequearSiEsta (FILE *x, registro r, int cod, int flag) {
    flag = 0;
    rewind(x);
    while (!feof(x)) {
        fread(&r,sizeof(registro),1,x);
        if (cod == r.cod_ciu) {
            out("el codigo ya se encuentra ingresado\n");
            flag = 1;
        }
        }
return flag;
}

int ingresar3 (int cod, char nombre[30], float tMin, float tMax) {
    int flag = 0;
    registro aux, delRead; // para el fread
    FILE *archBin;
    archBin = fopen("archivoBinario.dat","wb+");
    if (archBin != NULL) {
        out("Ingrese un codigo de ciudad\n");
        in("%d",&cod);
        chequearSiEsta(archBin,delRead, cod, flag);
        while (cod != 0) {
            if (flag == 0) { // aca empiezo a ingresar datos
                cargar(cod, nombre, tMin, tMax, aux);
                 // aca hago un print para ver como guarda los datos en el registro
                out("este es el segundo(dentro de ingresar)\n%d\t%s\t%f\t%f\n", aux.cod_ciu,aux.nom_ciu,aux.t_min,aux.t_max);
                fseek(archBin,sizeof(registro),SEEK_CUR);
                fwrite(&aux,sizeof(registro),1,archBin);
                }
            out("Ingrese un codigo de ciudad\n");
            in("%d",&cod);
            chequearSiEsta(archBin,delRead, cod, flag);
        }
rewind(archBin);//
out("\n\n");
out("\nCodigo de ciudad\tNombre de la Ciudad\tTemp Minima\tTemp Maxima\tAmplitud termica\n");
while (!feof(archBin)){
  fread(&aux, sizeof(registro),1,archBin);

 out("%d\t%s\t%f\t%f\t%f\n", aux.cod_ciu,aux.nom_ciu,aux.t_max,aux.t_min,aux.t_max-aux.t_min);
}
fclose(archBin);
}
return 0;
}
