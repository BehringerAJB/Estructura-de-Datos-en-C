#include<stdlib.h>
#include<stdio.h>
#include<conio.h>
#include<time.h>

#define p printf
#define s scanf


void mostrar(FILE*);


int main()
{
    FILE* archi;
    srand(time(NULL));
    char nomarch[] = "numeros.dat";
    system("color 9f");

    archi = fopen(nomarch,"rb+");
    p("\nEl archivo ");

    p("\nPresiona una tecla para ver el contenido del archivo!!\n\n");
    getch();
    mostrar(archi);
    fclose(archi);
    getch();
    return 0;
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

