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

void inicio(FILE*,FILE*);
void ingresar(FILE*);
//void mostrar(FILE*,FILE*,FILE*);
int buscaCiudad(FILE *, int x);
//void sumarFacturacion(FILE *, FILE *, int x, float totfact);
//void sumarFacturacionCliente(FILE *, char nomcli[], float totfact);
int error(char*);
void tecla(void);
void linea(int);

int main()
{
	FILE *ciu;
	char nomarchciu[] = "ciudades.dat";
	system("cls");
	srand(time(NULL));
	system("color 9f");

	if((ciu = fopen(nomarchciu,"rb+")) == NULL)//CHECK APERTURA DE ARCHIVO
		ciu = fopen(nomarchciu, "wb");

	p("\nEl archivo %s ha sido cargado!!\n",nomarchciu);

    ingresar(ciu);
    mostrar(ciu);

	linea(110);
	tecla();
	system("cls");
	fclose(ciu);
	return(0);

}
void linea(int x)
{
 int i;
	//p("");
	for(i=1;i<x;i++)
	 p("*");
// p("\n");
}

/*void inicio(FILE *x,FILE*y)//DATOS DE LA TABLAS PASADAS A LOS ARCHIVOS x=clientes, y=articulos
{
    registro c;
    articulo a;
    char nomcli[][30] = {"ECUMENICO LOPEZ","MARCELINO RIOS","ROQUE CARPIO","NICANOR PAREDES","ALFINGER MALDONADO"};
    char nomart[][30] = {"COCA COLA","FANTA TONICA","FANTA NARANJA","SPRITE","AGUA KIN","MANDARINA"};
    float pre[] = {12.70,13.75,13.66,12.80,12.89,13.01};
    int sto[] = {73,120,76,34,77,98};
    int i;


    for (i = 0; i < 5; i++) {//OK
        fseek(x,0L,SEEK_END);
        c.cod = i + 1;
        strcpy(c.nom,nomcli[i]);
        c.fac = 0;
        fwrite(&c,sizeof(c),1,x);
    }

    for (i = 0; i < 6; i++) {//OK
        fseek(y,0L,SEEK_END);
        a.datos.cod = i + 1;
        strcpy(a.datos.nom,nomart[i]);
        a.datos.fac = 0;
        a.pre = pre[i];
        a.sto = sto[i];
        fwrite(&a,sizeof(a),1,y);
    }


}*/


void mostrar(FILE *ciu)
{
  registro c;
    rewind(ciu);
	system("cls");
	p("\n\n\t\t\tLISTADO DE CIUDADES\n\n");
	linea(80);
	p("\nC%cDIGO\t\tCIUDAD\t\t\tTEMP MIN\tTEMP MAX\tAMP. TERM.\n",224);
	fread(&c,sizeof(c),1,ciu);
	while(!feof(ciu))
	{
		p("\n%3d\t\t%-20s %1.2f\t\t%1.2f\t\t%1.2f\n",c.cod_ciu,c.nom_ciu,c.t_min,c.t_max,(float)c.t_max-c.t_min);
		fread(&c,sizeof(c),1,ciu);
	}
	p("\n");
}

void ingresar(FILE *ciu)
{
    int codCiu = 0;
    char nomCiu[30];
    float tempMin, tempMax, ampTermica;
    registro c;
    do{
        fflush(stdin);
        p ("\nINGRESE CODIGO DE CIUDAD O CERO PARA FINALIZAR: ");
        s ("%d",&codCiu);
        c.cod_ciu = codCiu;

        // PREGUNTA SI INGRESÓ CERO PARA SALTAR LAS FUNCIONES Y FINALIZAR
        if(codCiu != 0){
            // BUSCA CIUDAD Y CONSULTA SI EXISTE (0 NO EXISTE, 1 EXISTE)
            if(buscaCiudad(ciu, codCiu) == 1){
                p("\n****LOS DATOS DE LA CIUDAD SOLICITADA YA FUERON INGRESADOS****\n");
                continue;
            }

            // SI LOS DATOS DE LA CIUDAD NO FUERON INGRESADOS
            else{
                //ampTermica = 0;
                tempMin = 0;
                tempMax = 0;
                ampTermica = 0;
                fflush(stdin);
                p ("\nINGRESE EL NOMBRE DE LA CIUDAD: ");
                gets(c.nom_ciu);
                fflush(stdin);
                p ("\nINGRESE TEMPERATURA MINIMA: ");
                s ("%f",&c.t_min);

                do{
                fflush(stdin);
                p ("\nINGRESE TEMPERATURA MAXIMA: ");
                s ("%f",&c.t_max);
                } while(c.t_max < c.t_min);

                //ampTermica = (float)tempMax-tempMin;
                /*p("\n\nNombre ciudad: %s", c.nom_ciu);
                p("\nTemp min: %2.f", c.t_min);
                p("\nTemp max: %2.f", c.t_max);
                p("\nAmp term: %2.f", ampTermica);
                //p("\nAmplitud termica: %2.f", &ampTermica);*/
                fseek(ciu,0L,SEEK_END);
                fwrite(&c,sizeof(c),1,ciu);
                //system("cls");
            //CIERRO FACTURA
            }
        }
    }while(codCiu != 0);
}

int buscaCiudad(FILE *ciu, int c)
{
    int bandera=0;
    registro f;
    rewind(ciu);
        fread(&f,sizeof(registro),1,ciu);
        while(!feof(ciu)) // while infinito
        {

            if(f.cod_ciu==c)
            //if(strcmpi(r.chofer,y.chofer)==0)
            {
                bandera=1;
                break;
            }
            else
            {
                fread(&f,sizeof(registro),1,ciu);
            }
        }
        return bandera;

}

/*void sumarFacturacion(FILE *fc, FILE *cl, int x, float totfact)
{
    registro f;
    rewind(fc);
        fread(&f,sizeof(registro),1,fc);
        while(!feof(fc)) // while infinito
        {
            if(f.cod==x)
            //if(strcmpi(r.chofer,y.chofer)==0)
            {
                f.fac += totfact;
                fseek(fc,(-1L)*sizeof(f),SEEK_CUR);
                fwrite(&f,sizeof(f),1,fc);
                sumarFacturacionCliente(cl, f.nom, totfact);
                break;
            }
            else
            {
                fread(&f,sizeof(registro),1,fc);
            }
        }

}

void sumarFacturacionCliente(FILE *cl, char nomcli[], float totfact)
{
    registro f;
    rewind(cl);
        fread(&f,sizeof(registro),1,cl);
        while(!feof(cl)) // while infinito
        {
            if(strcmp(f.nom, nomcli) == 0)
            //if(strcmpi(r.chofer,y.chofer)==0)
            {
                f.fac += totfact;
                fseek(cl,(-1L)*sizeof(f),SEEK_CUR);
                fwrite(&f,sizeof(f),1,cl);
                break;
            }
            else
            {
                fread(&f,sizeof(registro),1,cl);
            }
        }

}*/


int error(char *x)
{
	fprintf(stderr,"no se puede abrir el archivo %s",x);
	return(1);
}
void tecla(void)
{
	p("\n\nPRESIONE CUALQUIER TECLA PARA CONTINUAR!!!");
	getch();
}
