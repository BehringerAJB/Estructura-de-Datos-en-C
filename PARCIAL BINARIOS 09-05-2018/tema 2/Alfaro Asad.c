#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <string.h>
#include <ctype.h>
#define p printf
#define s scanf

typedef struct
{
    int cod_prof;
    char nom_prof[30];
    int cant_insp;
    int horas;
    float sueldo;
}registro;

void ingresar(FILE*);
void tecla(void);
void mostrar(FILE*);
void linea(int);

int main()
{
    FILE *archivo;
    archivo = fopen("Archivo.dat","w+b");

    if(archivo == NULL)
    {
        p("El archivo no se pudo abrir");
        return(1);
    }
    else
    {
        p("BIENVENIDO AL SISTEMA DE ORGANIZACI%cN DE PROYECTOS", 224);
    }
    tecla();

    ingresar(archivo);
    rewind(archivo);
    mostrar(archivo);

    return 0;
}


void ingresar(FILE *archivo)
{
    char nomProfesional[40];
    int nroInsp, nroProf, cantHoras, bandera, contador;
    registro regEmpleado, regComparacion;

    system("cls");
    linea(80);
    p("\nIngrese Nro de inspeccion y para finalizar ingrese 0: ");
    s("%d", &nroInsp);

    while(nroInsp)
    {
        bandera = 0;
        contador = 0;

        p("\n\nIngrese el Nro del profesional: ");
        s("%d", &regEmpleado.cod_prof);


        fseek(archivo,sizeof(regComparacion),SEEK_SET);
        fread(&regComparacion,sizeof(regComparacion),1,archivo);
        while(!feof(archivo))
        {
            contador++;
            if(regEmpleado.cod_prof == regComparacion.cod_prof)
            {
                bandera = 1;
                break;
            }

            fread(&regComparacion,sizeof(regComparacion),1,archivo);
        }
        if(bandera == 0)
        {
            fflush(stdin);
            p("\n\nIngrese el nombre del profesional: ");
            gets(regEmpleado.nom_prof);

            p("\n\nIngrese la cantidad de horas: ");
            s("%d", &cantHoras);
            regEmpleado.horas = cantHoras;
            regEmpleado.sueldo = cantHoras * 250;
            regEmpleado.cant_insp = 1;
            fwrite(&regEmpleado,sizeof(regEmpleado),1,archivo);
        }

        if(bandera == 1)
        {

            p("\n\nIngrese la cantidad de horas del empleado Nro %d: ", regEmpleado.cod_prof);
            s("%d", &cantHoras);

            regEmpleado.horas = regEmpleado.horas + cantHoras;
            regEmpleado.cant_insp = regEmpleado.cant_insp + 1;
            regEmpleado.sueldo = regEmpleado.sueldo + (cantHoras * 250);
            fseek(archivo,sizeof(regEmpleado)*contador,SEEK_SET);
            fwrite(&regEmpleado,sizeof(regEmpleado),1,archivo);
        }

        system("cls");
        linea(80);
        p("\n\nIngrese Nro de inspeccion y para finalizar ingrese 0: ");
        s("%d", &nroInsp);


    }
}
void mostrar(FILE *archivo)
{

    registro regArchivo;
	system("cls");
	linea(80);
	 rewind(archivo);
	 p("\nNro de Prof. | Nombre Completo | Cant.Insp. | Cant.Hs | Sueldo\n");
	fread(&regArchivo,sizeof(regArchivo),1,archivo);
	while(!feof(archivo))
	{
		p("\n%d\t\t%s\t\t%d\t\t%d\t\t%.2f\n",regArchivo.cod_prof,regArchivo.nom_prof,regArchivo.cant_insp,regArchivo.horas,regArchivo.sueldo);
		fread(&regArchivo,sizeof(regArchivo),1,archivo);
	}
	p("\n");
}

void tecla(void)
{
	p("\n\nPresione cualquier tecla para comenzar");
	getch();
}

void linea(int x)
{
    int i;
	for(i=1;i<x;i++)
    p("*");
}
