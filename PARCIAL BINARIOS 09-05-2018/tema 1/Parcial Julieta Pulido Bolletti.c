#include<stdlib.h>
#include<stdio.h>
#include<conio.h>
#include<time.h>
#include<string.h>
#define p printf
#define s scanf

typedef struct{
    int cod_ciu;
    char nom_ciu[30];
    float t_min;
    float t_max;
 } registro;

/********************************************************************************************/

 void mostrar(FILE *arch){

    registro reg;
    float amp;
    system("cls");
    p("\n Cod. Ciudad\t Nom. Ciudad\t Tem. minima\t Tem. maxima\t Am. Termica\n");//12
    //fread(reg,sizeof(reg),1,arch);
    //fread(reg,sizeof(registro),1,arch);
      rewind(arch);
      fread(&reg,sizeof(registro),1,arch);
    while(!feof(arch)){
        amp=((reg.t_max)-(reg.t_min));
        p("\n %d %s %f %f %f\n", reg.cod_ciu, reg.nom_ciu, reg.t_min, reg.t_max, amp);
        fread(&reg,sizeof(registro),1,arch);
    }
}

/********************************************************************************************/

void cargar(FILE *arch){
    registro reg;
    //registro aux;
    rewind(arch);
    int codCiudad, band;

    p("Ingrese Codigo de ciudad [0 para finalizar]: ");
    s("%d",&codCiudad);
    while(reg.cod_ciu!=0){
        fflush(stdin);
         /*if(aux.cod_ciu==reg.cod_ciu){
            reg.t_min=reg.t_min
            //fseek(reg,-sizeof(registro), SEEK_CUR);
            //fwrite(&reg,sizeof(registro),1,arch);*/

        bandera(arch, reg, codCiudad,band);
        if (bandera==0){
            p("Ingrese el nombre de la ciudad: ");
            gets(reg.nom_ciu);
            p("Ingrese temperatura minima: ");
            s("%f", reg.t_min);
            p("Ingrese temperatura maxima: ");
            s("%f", reg.t_max);
        }
        else p("Ya se ha ingresado la ciudad \n");

        p("Ingrese Codigo de ciudad [0 para finalizar]: ");
        s("%d",&codCiudad);
        if(reg.cod_ciu==0) break;
    }
}

/********************************************************************************************/

int bandera(FILE *arch, registro reg, int codigo, int band){
    while(!feof(arch)){
        fread(&reg,sizeof(registro),1,arch);
        if(reg.cod_ciu==codigo)
            band=1;
        else
            band=0;
    }
    return(band);
}

/********************************************************************************************/

int main(){
    FILE *arch;
    float tempMax;
    char *nombreArchivo="Temperatura.dat";
    if((arch=fopen(nombreArchivo,"rb+"))==NULL)
        arch=fopen(nombreArchivo,"wb+");
    //cargar(arch, registro);
    cargar(arch);
    mostrar(arch);
    fclose(arch);
    getch();
    return 0;
}
