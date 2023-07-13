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

void ingresar(FILE *);
void cargar(FILE *, registro);
void mostrar(FILE *);
void tecla(void);

int main() {
    FILE *archivo;
    char *nomarchivo = "ciudades.dat";
    system("color 9f");
    //VERIFICACION DE EXISTENCIA DE ARCHIVO
    if((archivo = fopen(nomarchivo,"rb+")) == NULL) {//CHECK APERTURA DE ARCHIVO
		archivo = fopen(nomarchivo,"wb+");
		p("\nEl archivo %s ha sido CARGADO!!\n",nomarchivo);
    }

    tecla();
    fflush(stdin);

    ingresar(archivo);
    tecla();
    fflush(stdin);
    system("cls");

    mostrar(archivo);
    tecla();
    fflush(stdin);

	fclose(archivo);
	return(0);
}

void ingresar(FILE *x) {
    //variables auxiliares
    int codigo;
    //int ampterm;
    char nombre[30];
    float tmax, tmin;
    registro dato;
    //Primer ingreso
    p("\nIngrese el codigo de la ciudad: ");
    s("%d",&codigo);
    //Ciclo hasta que codigo sea cero
    while (codigo) {
        //Ingreso datos por teclado
        dato.cod_ciu = codigo;
        p("\nIngrese el nombre de la ciudad: ");
        s("%s",nombre);
        strcpy(dato.nom_ciu,nombre);
        fflush(stdin);

        do {

        p("\nIngrese la temperatura minima: ");
        s("%f",&tmin);
        dato.t_min = tmin;

        p("\nIngrese la temperatura maxima: ");
        s("%f",&tmax);
        dato.t_max = tmax;

        }while(tmax - tmin < 0);

        //fin de ingreso de datos por teclado
        //Verificacion de existencia y carga en archivo
        cargar(x,dato);
        //Pido siguiente codigo para seguir el ciclo o salir del while
        p("\nIngrese el codigo de ciudad: ");
        s("%d",&codigo);
    }
}

void cargar(FILE *arch, registro dat){
    int flag = 0; //flag para determinar si el dato existe en el archivo o no
    registro aux; //auxiliar que voy a usar para actualizar o crear registro en archivo
    fseek(arch,0L,SEEK_SET);//Me ubico al prinicipio del archivo binario
    fread(&aux,sizeof(registro),1,arch);//leo en aux 1 dato de tipo registro del archivo arch
    while(!feof(arch) && flag == 0){ //mientras NO sea fin de archivo y el flag sea 0
        if(dat.cod_ciu == aux.cod_ciu){// si el dato existe en el binario...
            fflush(stdin);
            flag = 1; //cambio estado del flag
        }
        else { // si no existe en el binario...
            fread(&aux,sizeof(registro),1,arch);
        }
    }

    if (flag == 1) { //como el dato existe, aviso por pantalla
        p("\nLOS DATOS REFERIDOS AL CODIGO DE CIUDAD YA FUERON INGRESADOS!\n");
    }

    else{ //como el dato no existe, lo creo
        aux = dat;//paso los datos del dat ingresado por teclado al aux que va a escribir en el binario.
        fseek(arch,0L,SEEK_END); //me posiciono al final del archivo
        fwrite(&aux,sizeof(registro),1,arch); //escribo en el archivo binario los campos
   }
}

void mostrar(FILE *arch){
    registro aux;
    fseek(arch,0L,SEEK_SET);//Me posiciono al principio del archivo
	p("\nCod Ciudad\tNom Ciudad\tTemp Min\tTemp Max\tAmp Termica\n");
	fread(&aux,sizeof(aux),1,arch);
	while(!feof(arch)){
		p("\n%3d\t\t%-15s\t%6.2f\t\t%6.2f\t\t%6.2f\n",aux.cod_ciu,aux.nom_ciu,aux.t_min,aux.t_max,aux.t_max - aux.t_min);
		fread(&aux,sizeof(aux),1,arch);
	}
	p("\n");
}

void tecla(void)
{
	p("\n\nPRESIONE CUALQUIER TECLA PARA CONTINUAR!!!");
	getch();
}
