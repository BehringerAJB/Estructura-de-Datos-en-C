#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <string.h>
#define p printf
#define s scanf
typedef struct
{
    int cod_alum;
    char nom_alum[30];
    float prom;
} registro;

void cargar(FILE *, registro, FILE *);
void tecla(void);
void sacar(char[], registro *);
void mostrar(FILE *, char[]);
int main()
{

    FILE *archivo, *binario, *aprobados;
    char *nombre = "F:\\UTN-INSPT\\Estructura y Base de Datos\\notas.txt"; // nombre físico del archivo
    char *nombin = "F:\\UTN-INSPT\\Estructura y Base de Datos\\datos.dat";
    char *apro = "F:\\UTN-INSPT\\Estructura y Base de Datos\\aproba.dat";
    char cadena[80];
    registro reg;
    system("color 9f");
    archivo = fopen(nombre, "r+");
    p("\n CONTENIDO DEL ARCHIVO DE TEXTO\n\n");
    getch();
    while (fgets(cadena, 81, archivo)) //!=NULL)  hasta \n n-1 o salto de linea
        p("%s", cadena);
    rewind(archivo);
    tecla();
    p("\n\n CONTENIDO DE LOS CAMPOS EN MEMORIA");
    p("\n\nC%CDIGO\t\tALUMNO\t\t\t PROMEDIO\n\n", 224);
 
    if ((fopen(nombin, "rb+")) == NULL)
    {
        while (fgets(cadena, 81, archivo)) // Recorro el Archivo de Texto
        {
            sacar(cadena, &reg);             
            // getch(); // Saco del Archivo de Texto y lo cargo en el registro
            cargar(binario, reg, aprobados); // Cargo el registro en el Archivo Binario
            p("\n\n");
        }
    }
    getch();
    binario = fopen(nombin, "rb+");
    rewind(binario);
    mostrar(binario, "DESAPROBADOS");
    getch();
    aprobados = fopen(apro, "rb+");
    rewind(aprobados);
    mostrar(aprobados, "APROBADOS");
    tecla();
    system("cls");
    fclose(binario);
    fclose(archivo);
    fclose(aprobados);
    getch();
    system("cls");
    return (0);
}

void sacar(char x[], registro *y) // Modifico el Registro por Dirección
{
    char *pri, *seg, *ter, *cuar;

    pri = strtok(x, ",");
    y->cod_alum = atoi(pri);
    p(" %3d", y->cod_alum); // getch();
    seg = strtok(NULL, ",");
    strcpy(y->nom_alum, seg);
    p("\t\t%-20s ", seg); // que será el nombre del alumno
    ter = strtok(NULL, ",");
    cuar = strtok(NULL, ",");
    y->prom = (atoi(ter) + atoi(cuar)) / 2.;
    p("\t%6.2f", y->prom);
}

void tecla(void)
{
    p("\n\nPRESIONE CUALQUIER TECLA PARA CONTINUAR!!!");
    getch();
}

void cargar(FILE *x, registro y, FILE *ap)
{
    registro r;
    char *nb = "datos.dat";
    char *bb = "aproba.dat";
    if ((x = fopen(nb, "rb+")) == NULL)
        x = fopen(nb, "wb+");
    if ((ap = fopen(bb, "rb+")) == NULL)
        ap = fopen(bb, "wb+");
    if (y.prom >= 6.)
    {
        fseek(ap, 0L, SEEK_END);
        fwrite(&y, sizeof(y), 1, ap);
    }
    else
    {
        fseek(x, 0L, SEEK_END);
        fwrite(&y, sizeof(y), 1, x);
    }
    fclose(x);
    fclose(ap);
}
//*/
void mostrar(FILE *x, char y[])
{
    registro r;
    p("\n\nCONTENIDO DE LOS REGISTROS EN EL ARCHIVO DE NOTAS DE %s\n\n", y);
    p("\n\n C%cDIGO\t\t ALUMNO\t\t\t   PROMEDIO", 224);
    rewind(x);
    fread(&r, sizeof(r), 1, x);
    while (!feof(x))
    {
        p("\n\n %3d\t\t%-20s\t  %6.2f", r.cod_alum, r.nom_alum, r.prom);
        fread(&r, sizeof(r), 1, x);
    }
}
