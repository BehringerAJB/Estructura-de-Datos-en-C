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

int buscar(int*, FILE*);
void ingresar(FILE*);
void mostrar(FILE*);
int error(char*);

int main()
{
	FILE *temp;
	char nomarch[]="temp.dat";
		system("cls"); srand(time(NULL)); system("color 5f");
	if((temp=fopen(nomarch,"wb+"))==NULL)
		exit(error(nomarch));
	p("\nEl archivo %s ha sido cargado\n",nomarch);
	fflush(stdin);
	ingresar(temp);
	mostrar(temp);
	system("cls");
	fclose(temp);
	return(0);
}

int buscar(int*cod, FILE*x)
{
    int i=0;
    registro r;
    fread(&r,sizeof(r),1,x);
    while(!feof(x))
        {

            if(cod==r.cod_ciu)
            {
               i=1;
               break;
            }

            fread(&r,sizeof(r),1,x);
        }
    return i;
}

void ingresar(FILE* x)
{
    int cod;
    char nom[30];
    float temp_min, temp_max;
    registro r;

    p("\nIngrese el codigo de ciudad o cero para terminar\n");
    s("%d",&cod);
    while(cod)
    {
            if(buscar(cod,x)==1)
            {
//                fseek(x,(cod)*sizeof(r),SEEK_SET);
//                fread(&r,sizeof(r),1,x);
                p("Ciudad: %s, Temp. min: %f, Temp. max. %f", r.nom_ciu,r.t_min,r.t_max);
            }
            else
            {
                p("\nIngrese el nombre\n");
                fflush(stdin);
                gets(r.nom_ciu);
                p("\nIngrese la temperatura minima\n");
                s("%d",&r.t_min);
                p("\nIngrese la temperatura maxima\n");
                s("%d",&r.t_max);
                fseek(x,0L,SEEK_END);
                fwrite(&r,sizeof(r),1,x);
                system("cls");
            }
        p("\nIngrese el codigo de ciudad o cero para terminar\n");
        s("%d",&cod);
    }
}

void mostrar(FILE* x)
{
    registro r;
    float amp;
    rewind(x);
    system("cls");
    p("Listado de ciudades\n");
    p("\nCodigo\tNombre\tTemp. Min.\tTemp. Max.\tAmplitud\n");
    fread(&r,sizeof(r),1,x);
    while(!feof(x))
    {
        amp=r.t_max-r.t_min;
        p("\n%d\t%s\t%f\t%f\t%f\n",r.cod_ciu,r.nom_ciu,r.t_min,r.t_max,amp);
        fread(&r,sizeof(r),1,x);
    }
    getch();
}

int error(char *x)
{
	fprintf(stderr,"No se puede abrir el archivo %s",x);
	return(1);
}
