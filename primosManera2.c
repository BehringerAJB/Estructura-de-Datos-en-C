#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <math.h>

void mostrar(FILE *);
void tecla(void);

int generar(int, FILE*);
int esPrimo(int);

int main(){
    int n, cant;

    FILE * archivo;
    system("color 9f");

    do{
        printf("\n Ingrese cantidad de primos a generar:");
        fflush(stdin);
        scanf("%d", &n);
    }while(n < 1);

    archivo = fopen("prueba.dat", "wb+");
    system("cls");

    cant = generar(n, archivo);
    fclose(archivo);

    archivo = fopen("prueba.dat", "rb+");
    printf("\n Archivo de primos abierto\n");

    mostrar(archivo);
    printf("\nCantidad de iteraciones %d", cant);
    getch();

    return 0;
}

int generar(int x, FILE * y){
    int cant = 0, r, it = 0, i = 1, res;

    while(cant < x){
        res = i * i;

        res = (res - 1) % 12;
        r = (!res)?1:0;

        if(r == 1 || i < 7)
            if(esPrimo(i)){
                fwrite(&i, sizeof(int), 1, y);
                cant++; it++;
            }
            i++;
        }
        fclose(y);

        //Cantidad de iteraciones
        return i;

}

int esPrimo(int x){
    int mitad, res = 0, divs = 2;

    if(x > 2){
        mitad = (int) (sqrt(x));
        do{
            res = (x % divs != 0);
            divs++;
        }while(res != 0 && divs <= mitad);
    }
    else if(x == 2)
        res = 1;


    return (res);
}

void mostrar(FILE * x){
    int c = 0, i;
    rewind(x);

    fread(&i, sizeof(int), 1, x);

    while(!feof(x)){
        if(c % 15 == 0){
            printf("\n");
        }
        printf("%5d", i);
        c++;
        fread(&i, sizeof(int), 1, x);
    }
}
