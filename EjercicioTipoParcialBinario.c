#include<stdio.h>
#include<stdlib.h>
#include<conio.h>
#include<time.h>
#define p printf
#define s scanf
typedef struct
{
 int cod_ciu;
 char nom_ciu[30];
 float t_min;
 float t_max;
 float dif_t;
 } registro;

float mostrar(FILE *);
void tecla(void);
void cargar(FILE *);
void filtrar(FILE*,FILE*);
void maxamp(FILE*,float);
int error(char *);

int main()
{
 FILE *arch;
 float max;
 // poner un directorio valido
 char *nomarch="D:\\alejandro\\temp.dat";
 system("cls");
 system("color 9f");
  if((arch=fopen(nomarch,"ab+"))==NULL) exit(error(nomarch));
  p("\nEl archivo %s ha sido abierto para escritura!!!",nomarch);
  tecla();
  cargar(arch);
   tecla();
	p("\n Presione una tecla para mostrar la Estadística de Temperaturas !!!\n\n");
	tecla();
	max=mostrar(arch);
	p("\n La amplitud maxima  es %.2f corresponde a:\n\n ",max);
	maxamp(arch,max);
	tecla();
	fclose(arch);	getch(); 	return(0);
}
int error(char *x)
{
	fprintf(stderr,"No se pudo abrir el archivo %s",x);
	return(1);
}
void tecla(void)
{
 p("\nPresione cualquier tecla para continuar !!!!");
 getch();
  system("cls") ;
}

	void cargar(FILE *x)
{
	int codc,horas,ni,c;
    registro r;
	p("\n Ingrese Codigo de Ciudad:"); s("%d",&codc);
	while(codc)
	{
	   rewind(x); c=0;
       fread(&r,sizeof(registro),1,x);
	   while(!feof(x))
            {
                if(r.cod_ciu==codc)
                {
                    c=1; break;
                } else  fread(&r,sizeof( registro),1,x);
		     }
		   if(c==1)
			 {
				  p("\n El  Registro de la Ciudad Ya Fue Ingresado!!");
				 tecla(); //break;
			 }
		 else
		 {
					p("\nLa Ciudad No tiene registros");
					fseek(x,0L,SEEK_END);
					r.cod_ciu=codc;
					fflush(stdin);
					p("\n Ingrese Nombre de la Ciudad:");
					s("%[^\n]",r.nom_ciu);
					p("\n Ingrese Temperatura Minima de la Ciudad:");
					s("%f",&r.t_min);
					p("\n Ingrese Temperatura Maxima de la Ciudad:");
					s("%f",&r.t_max);
					r.dif_t= r.t_max-r.t_min;
					fwrite(&r,sizeof(registro),1,x);
					//break;
			}
	  system("cls") ;
		p("\n Ingrese Codigo de Ciudad:"); s("%d",&codc);
	}


}
float mostrar(FILE *x)
{
	registro r;
	float maxi=0;
	rewind(x);
	p("\n \t\t\tESTADISTICA DE TEMPERATURA DE CIUDADES \n\n");
	p("\n Cod \t CIUDAD\t\t\t MINIMA   MAXIMA\t\tAMPLITUD\n\n\n");
	fread(&r,sizeof(registro),1,x);
	while(!feof(x))
		{
		 if(r.dif_t>maxi) maxi=r.dif_t;
		 p("\n %-10d%-20s %6.2f\t  %6.2f\t\t%6.2f\n\n",r.cod_ciu,r.nom_ciu,r.t_min,r.t_max,r.dif_t);
		 fread(&r,sizeof( registro),1,x);
		}
	return(maxi);
}
	void maxamp(FILE*x,float y)
	{
	    registro r;
	    rewind(x);
		fread(&r,sizeof(registro),1,x);
	    while(!feof(x))
		{
		 if(r.dif_t==y)  p("\n %-20s \n",r.nom_ciu);
		 fread(&r,sizeof( registro),1,x);
		}
	}
