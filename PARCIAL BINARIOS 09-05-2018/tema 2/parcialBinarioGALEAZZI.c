#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#define p printf
#define s scanf
#define HORA 250

typedef struct {
    int cod_prof;
    char nom_pro[30];
    int cant_insp;
    int horas;
} registro;


void clean_stdin(void){
    int c;
    do{
        c=getchar();
    }while(c!='\n' && c!=EOF);
}

void ingresarDatos(FILE*);
void mostrarArchivo(FILE*);
void mostrar(FILE*);
void pasarMayus(char[]);

int main() {

    FILE* archivo;
    char name[] = "registrosInspecciones.dat";

    if( archivo != NULL ){
        archivo = fopen(name, "rb+");
        p("\nEl archivo esta listo para seguir siendo cargado\n");
    } else {
        archivo = fopen(name, "wb+");
        p("\nEl archivo ha sido abierto por primera vez\n");
    }

    ingresarDatos(archivo);
    //mostrarArchivo(archivo);
    mostrar(archivo);

return 0;
}

void ingresarDatos(FILE* archivo) {
    registro nomina;
    int noInsp, noProf, ban, cantHoras, pos;


    p("Ingrese el numero de inspeccion o 0 para salir: ");
    s("%d", &noInsp);
    clean_stdin();
    while ( noInsp ){
        pos = 0;
        ban = 0;
        p("Ingrese el numero del profesional: ");
        s("%d", &noProf);
        clean_stdin();
        rewind(archivo);
        fread(&nomina, sizeof(nomina), 1, archivo);
        while ( !feof(archivo) && ban == 0){
            pos++;
            if (nomina.cod_prof == noProf){
                ban = 1;
            } else {
                ban = 0;
            }
            fread(&nomina, sizeof(nomina), 1, archivo);
        }
        p("Ingrese la cantidad de horas: ");
        s("%d", &cantHoras);
        clean_stdin();
        if ( !ban ){
            p("Debe ingresar el nombre del profesional: ");
            s("%s", &nomina.nom_pro);
            clean_stdin();
            pasarMayus(nomina.nom_pro);
            nomina.cod_prof = noProf;
            nomina.cant_insp = 1;
            nomina.horas = cantHoras;
            fseek(archivo, 0L, SEEK_END);
            fwrite(&nomina, sizeof(nomina), 1, archivo);
        } else {
            fseek(archivo, (pos-1)*sizeof(nomina), SEEK_SET);
            fread(&nomina, sizeof(nomina), 1, archivo);
            nomina.cant_insp += 1;
            nomina.horas += cantHoras;
            fseek(archivo, (pos-1)*sizeof(nomina), SEEK_SET);
            fwrite(&nomina, sizeof(nomina), 1, archivo);
        }
        p("Ingrese el numero de inspeccion o 0 para salir: ");
        s("%d", &noInsp);
        clean_stdin();
    }
}

void mostrarArchivo(FILE* archivo){
    registro nomina;
    rewind(archivo);
    p("\n********************************\n");
    fread(&nomina, sizeof(nomina), 1, archivo);
    while( !feof(archivo) ){
        p("cod: %d, nom: %s, cantInsp: %d, cantHoras: %d\n", nomina.cod_prof, nomina.nom_pro, nomina.cant_insp, nomina.horas);
        fread(&nomina, sizeof(nomina), 1, archivo);
    }
    p("\n********************************\n");
}

void mostrar(FILE* archivo){
    registro nomina;
    rewind(archivo);
    p("\n********************************\n");
    p("\nNo.Prof\tNombre y Apellido\tCant Insp Cant Horas Sueldo\n");
    fread(&nomina, sizeof(nomina), 1, archivo);
    while( !feof(archivo) ){
        p("%3d\t\t%-20s\t%d\t%d\t%d\n", nomina.cod_prof, nomina.nom_pro, nomina.cant_insp, nomina.horas, nomina.horas*HORA);
        fread(&nomina, sizeof(nomina), 1, archivo);
    }
    p("\n********************************\n");

}

void pasarMayus(char nom[]){
    int i=0;
    while(nom[i]!='\0'){
        nom[i]=(nom[i]>='a'&&nom[i]<='z')?(nom[i]-32):nom[i];
        i++;
    }
    nom[i]='\0';
}
