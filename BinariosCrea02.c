#include <stdio.h>  // Carga de un archivo de Texto separado los campos por comas
#include <stdlib.h> // Convierte e inserta en un Archivo binario
#include <conio.h>  // Probado con strtok
#include <string.h>
#include <ctype.h>
#define p printf
#define s scanf
typedef struct
{
    int cod_chof;
    char nom_chof[30];
    int kms;
    int rec;
} registro;

void cargar(FILE *);
void mostrar(FILE *);

int main()
{
    FILE  *binario;
    char *nombin = "F:\\UTN-INSPT\\Estructura y Base de Datos\\datos.dat";
    if ((binario = fopen(nombin, "rb+")) == NULL)
        binario = fopen(nombin, "wb+");
    cargar(binario);
    fseek(binario, 0L,SEEK_SET);
    mostrar(binario);
    getch();
    fclose(binario);
    system("cls");
    return 0;
}
void cargar(FILE *x)
{
    registro r;
    int pre = 200;
    int ban=1;
    // rewind(x);
    //fread(&r, sizeof(r), 1, x);
    while (ban)
    {
        p("\nIngrese Codigo de Chofer:");
        s("%d",&r.cod_chof);
        p("Ingrese cantidad de Kilometros:");
        s("%d",&r.kms);
        r.rec = pre * r.kms;
        fflush(stdin);
        p("Ingrese Nombre del Chofer:");
        s("%[^\n]",r.nom_chof);
        fseek(x, 0L, SEEK_END);
        fwrite(&r, sizeof(r), 1, x);
        p("\n\n Continua el ingreso:Si (1) / No (0)");
        s("%d",&ban);
    }
}
void mostrar(FILE*x)
{
   registro r;
    p("\n\t\t\t CONTENIDO DE LOS REGISTROS EN EL ARCHIVO\n\n");
    p("\n\n C%cDIGO\t\tCHOFER\t\t\t   KMS\t\t\t    RECAUDACI%cN\n\n",224,224);
    fseek(x, 0L,SEEK_SET);
    fread(&r,sizeof(r),1,x);
    while(!feof(x))
	{
		p("\n\n%3d\t\t%-20s\t%6d\t\t\t\t%6d",r.cod_chof,r.nom_chof,r.kms,r.rec);
		fread(&r,sizeof(r),1,x);
	}
}