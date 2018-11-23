#include<stdlib.h>
#include<stdio.h>
#include<conio.h>
#include<time.h>

#define p printf
#define s scanf

void cargar(FILE*);
void mostrar(FILE*);
void tecla(void);

int main()
{
    FILE* archi;
    srand(time(NULL));
    char nomarch[] = "numeros.dat";
    system("color 9f");

    archi = fopen(nomarch,"wb+");
    p("\nEl archivo ");

    cargar(archi);
    p("\nPresiona una tecla para ver el contenido del archivo!!\n\n");
    getch();
    mostrar(archi);
    fclose(archi);
    getch();
    return 0;
}

void cargar(FILE* x){
    int i, cant, n;
    do{
        p("\nIngrese cantidad de numeros: ");
        s("%d", &cant);
    }while(cant<1);
    for(i=0; i<cant; i++){
        n=rand()%(81)+10; //num aleatorio entre 10 y 90 (por teorema de la aritmetica)
        fwrite(&n, sizeof(int), 1, x);
    }
}

void mostrar(FILE* x){
    int c=0,i;
    rewind(x);
    fread(&i, sizeof(int), 1, x);//leo 1er registro
    while(!feof(x)){//me aseguro qno sea fin de archivo
        if(c%15==0) p("\n");
        p("%5d", i);
        c++;
        fread(&i, sizeof(int), 1, x);
    }
}

void tecla(void){
    p("\nPresione una tecla para continuar\n\n");
    getch();
}



/*
Con numeros.dat hay q:
-levantar archivo y mostrarlo (prog solo de lectura) (con rb+)
-levantar archivo y generar archivo pares y archivo impares
-numeros primos


*/
