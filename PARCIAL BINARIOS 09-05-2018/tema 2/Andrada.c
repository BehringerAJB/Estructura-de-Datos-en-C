#include<stdio.h>
#include<conio.h>
#include<string.h>
#define p printf
#define s scanf
#define precio 250


//ESTRUCTURAS
typedef struct
{
    int cod_prof;
    char nom_prof[30];
    int cant_insp;
    int horas;
}registro;


//PROTOTIPOS

void mostrar(FILE *);
void tecla(void);
void ingresar(FILE *);
void mayus(char x[]);


//MAIN
int main()
{
	FILE *arch;
	char nomarch[]="grilla.dat";
	system("cls"); srand(time(NULL)); system("color 9f");
    if((arch=fopen(nomarch,"rb+"))==NULL) arch=fopen(nomarch,"wb");
	p("\nEl archivo %s ha sido cargado!!\n",nomarch);


	tecla();
	fflush(stdin);
	system("cls");
	ingresar(arch);
	system("cls");
	fclose(arch);
	return(0);

}

void ingresar(FILE *arch)
{
    int numinsp,horas,numpro,sueldo,ban=0;
    char nompro[30];
    registro a;
    p ("\nINGRESE N%cMERO DE INSPECCION O CERO PARA FINALIZAR: ",233);
    s ("%d",&numinsp);
    while(numinsp)
    {
        ban=0;
        p ("\nINGRESE N%cMERO DE PROFESIONAL: ",233);
        s("%d",&numpro);
        fflush(stdin);
        rewind(arch);
        p("\nINGRESE LA CANTIDAD DE HORAS: ");
        s("%d",&horas);
        fflush(stdin);
        fread(&a,sizeof(registro),1,arch);
        while(!feof(arch))
        {
            if(numpro==a.cod_prof)
            {
                ban=1;
                break;
            }
            else
                fread(&a,sizeof(registro),1,arch);
        }
        if(ban!=1)
        {
            p("\n*EL PROFESIONAL NO SE ENCUENTRA REGISTRADO\nINGRESE NOMBRE DEL PROFESIONAL:");
            gets(a.nom_prof);
            fflush(stdin);
            mayus(a.nom_prof);
            a.cod_prof=numpro;
            a.cant_insp=1;
            a.horas=horas;
            fseek(arch,0L,SEEK_END);
            fwrite(&a,sizeof(registro),1,arch);
        }
        else
        {
            a.cant_insp++;
            a.horas+=horas;
            fseek(arch,(-1L)*sizeof(registro),SEEK_CUR);
            fwrite(&a,sizeof(registro),1,arch);
        }
        p ("\nINGRESE N%cMERO DE INSPECCION O CERO PARA FINALIZAR: ",233);
        s ("%d",&numinsp);
    }
    mostrar(arch);
    tecla();

}


void mostrar(FILE *x)
{
    registro r;
	rewind(x);
	p("\n \t\t\tINFORME \n\n",144);
	p("\n N%c \t   Nombre y Apellido\t\t Cantidad de Inspecciones\t Cantidad de Horas Totales \tSueldo\n\n\n",167);
	fread(&r,sizeof(registro),1,x);
	while(!feof(x))
    {
        p("\n %-10d%-20s%16d\t\t %17d\t\t%18d\n\n",r.cod_prof,r.nom_prof,r.cant_insp,r.horas,(r.horas*precio));
        fread(&r,sizeof(registro),1,x);
    }
}

void mayus(char x[])
{
    int i=0;
    while(x[i])
    {
        x[i]=toupper(x[i]);
        i++;
    }
}


void tecla(void)
{
	p("\n\nPRESIONE CUALQUIER TECLA PARA CONTINUAR!!!");
	getch();
}
