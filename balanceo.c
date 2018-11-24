#include <stdio.h>
#include <stdlib.h>

typedef struct arbolavl
{
    int info;
    int bal; /* Factor de balance -1,0,1 */
    struct arbolavl *izq, *der;
} nodo, *pnodo;

#  define p printf
# define s scanf

int ban; /* Marca para registrar cambios de altura. En rebalance ascendente */
//ban = 1 indica que debe seguir el ascenso rebalanceando.
int key; /* Variable global, para disminuir argumentos */
int alto_avl = 0; /* Altura árbol avl.Número de nodos desde la raíz a las hojas.  */    //global  ver

/* Rotación Izquierda *
*  A           B
* / \         / \
* a  B ==>   A   c
*   / \     / \
*   b  c    a  b
* Sólo cambian los factores de balance de los nodos A y B
* Los factores de balance de los sub-árboles no cambian. */
//static
pnodo rotaizq(pnodo t)
{
    pnodo temp;
    int x,y;
    temp = t;
    t = t->der;
    temp->der = t->izq;
    t->izq = temp;
    //Recalcula factores de balance de los dos nodos
    x = temp->bal; // oldbal(A)
    y = t->bal; // oldbal(B)
    temp->bal = x-1-max(y, 0); // nA
    t->bal = min(x-2+min(y, 0), y-1); // nB
    return t;
}

/* Rotación derecha
*
*   A         B
*  / \       / \
*  B  c ==> a   A
* / \          / \
* a  b        b   c
*
*/
//static
pnodo rotader(pnodo t)
{
    pnodo temp = t;
    int x,y;
    t = t->izq;
    temp->izq = t->der;
    t->der = temp;
    x = temp->bal; // oldbal(A)
    y = t->bal;    // oldbal(B)
    temp->bal = x+1-min(y, 0);  // nA
    t->bal = max(x+2+max(y, 0), y+1); //nB
    return t;
}

static void Error(int tipo)
{
    if (tipo) p("\nError en inserción\n");
    else p("\nError en descarte\n");
}

int Altura(void)
{
    return alto_avl;
}

pnodo CreaNodo(int key)
{
    pnodo t;
    t = (pnodo) malloc(sizeof(nodo));
    t->info=key;
    t->izq=0;
    t->der=0;
    return t;
}

pnodo insertar(pnodo t)
{
    if (t == NULL)  /* Llegó a un punto de inserción */
    {
        t = CreaNodo(key);
        t->bal = 0; /* Los dos hijos son nulos */
        ban = 1; /* Marca necesidad de revisar balances */
        return t; /* retorna puntero al insertado */
    }
    else if (t->info < key)
    {
        //desciende por la derecha
        t->der = insertar(t->der);
        //se pasa por la siguiente línea en la revisión ascendente
        t->bal += ban; /* Incrementa factor de balance */
    }
    else if (t->info > key)
    {
        //desciende por la izquierda
        t->izq = insertar(t->izq);
        //se corrige en el ascenso
        t->bal -= ban; /* Decrementa balance */
    }
    else   /* (t->k == key) Ya estaba en el árbol */  //cuando se ingresa un valor igual a un nodo del arbol
    {
        Error(1);
        ban = 0;
    }

    if (ban == 0) /* No hay que rebalancear. Sigue el ascenso */
        return t;

    /*El código a continuación es el costo adicional para mantener propiedad AVL */
    /* Mantiene árbol balanceado avl. Sólo una o dos rotaciones por inserción */
    if (t->bal < -1)
    {
        /* Quedó desbalanceado por la izquierda. Espejos Casos c y d.*/
        if (t->izq->bal > 0)
            /* Si hijo izquierdo está cargado a la derecha */
            t->izq = rotaizq(t->izq);
        t = rotader(t);
        ban = 0; /* El subárbol no aumenta su altura */
    }
    else if (t->bal > 1)
    {
        /* Si quedó desbalanceado por la derecha: Casos c y d.*/
        if (t->der->bal < 0)
            /* Si hijo derecho está cargado a la izquierda Caso d.*/
            t->der = rotader(t->der);
        t = rotaizq(t); /* Caso c.*/
        ban = 0; /* El subárbol no aumenta su altura */
    }
    else if (t->bal == 0)/* La inserción lo balanceo */
        ban = 0; /* El subárbol no aumenta su altura. Caso a*/
    else /* Quedó desbalanceado con -1 ó +1 Caso b */
        ban = 1; /* Propaga ascendentemente la necesidad de rebalancear */
    return t;
}

/* Mantiene variable global con el alto del árbol. */
pnodo InsertarAVL(int info, pnodo t)
{
    key = info; //pasa argumento a global.
    t = insertar(t);
    if (ban == 1)
        alto_avl++;
    //si la propagación llega hasta la raíz, aumenta la altura.
    return t;
}

int min(int x,int y)
{
    return((x)>(y)?(y):(x));
 }

int max(int x,int y)
{
    return((x)>(y)?(x):(y));
 }


pnodo borrader(pnodo t)
{
    pnodo p;
    if (t == NULL)  /* No encontró nodo a descartar */
    {
        Error(0);
        ban = 0;
    }
    else if (t->info < key)
    {
        //Comienza el descenso por la derecha
        t->der = borrader(t->der);
        //aquí se llega en el retorno ascendente.
        t->bal -= ban; /* Se descartó por la derecha. Disminuye factor */
        //Se retorna después de la revisión de los factores
    }
    else if (t->info > key)
    {
        //Desciende por la izquierda
        t->izq = borrader(t->izq);
        //o se llega por esta vía si se descartó por la izquierda.
        t->bal += ban; /* se descartó por la izq. Aumenta factor de balance */
    }
    else   /* (t->info == key) */
    {
        /* Encontró el nodo a descartar */
        if (t->izq == NULL)   /*Si hay hijo derecho debe ser hoja, por ser AVL */
        {
            p = t;
            t = t->der;
            free(p);
            ban = 1; /* Debe seguir revisando factores de balance */
            return t; /* ascendentemente */
        }
        else if (t->der == NULL)   /*Si hay hijo izquierdo debe ser hoja */
        {
            p = t;
            t = t->izq;
            free(p);
            ban = 1; /* Asciende revisando factores de balance */
            return t; /* Corrigiendo */
        }
        else   /* Tiene dos hijos */
        {
            if (t->bal<0)
            {
                /* Si cargado a la izquierda, elimina mayor descendiente hijo izq */
                p = t->izq;
                while (p->der != NULL) p = p->der;
                t->info = p->info;
                key = p->info; //busca hoja a eliminar
                t->izq = borrader(t->izq);
                t->bal += ban; /* incrementa factor de balance */
            }
            else   /* Si cargado a la derecha, elimina menor descendiente hijo der */
            {
                p = t->der;
                while (p->izq != NULL)
                    p = p->izq;
                t->info = p->info;
                key = p->info;
                t->der = borrader(t->der);
                t->bal -= ban; /* decrementa balance */
            }
        }
    }

    /* Mantiene árbol balanceado avl. Sólo una o dos rotaciones por descarte */
    if (ban == 0 ) /* No hay que rebalancear. Sigue el ascenso, sin rebalancear */
        return t;

    /* Hay que revisar factores de balance en el ascenso*/
    if (t->bal < -1)  /* Si quedó desbalanceado por la izquierda y dejó de ser AVL */
    {
        if (t->izq->bal > 0)  /*espejos casos c, d y e */
        {
            /* Si el hijo izquierdo está cargado a la derecha */
            t->izq = rotaizq(t->izq);
            ban = 1; /*Continuar revisando factores */
        }
        else if (t->izq->bal == 0)
            ban = 0; /*No debe seguir el rebalance */
        else
            ban = 1;/* Debe seguir revisando factores de balance */
        t = rotader(t);
    }
    else if (t->bal > 1)  /* Si quedó desbalaceado por la derecha */
    {
        if (t->der->bal < 0)
        {
            /* Si hijo derecho está cargado a la izquierda */
            t->der = rotader(t->der);
            ban = 1; //debe seguir revisando. Caso d.
        }
        else if (t->der->bal == 0)
            ban = 0; /* No debe seguir el rebalance. Caso c. */
        else //positivo
            ban = 1;/* Debe seguir revisando factores de balance. Caso e. */
        t = rotaizq(t);
    }
    else if (t->bal == 0) /* Si estaba en +1 ó -1 y queda en cero */
        ban = 1; /* Debe seguir corrigiendo. Caso b.*/
    else /* Si estaba en cero y queda en -1 ó +1 */
        ban = 0; /* No debe seguir rebalanceando. Caso a.*/
    return t;
}

pnodo DescartarAVL(int info, pnodo t)
{
    key = info;
    t = borrader(t);
    if (ban == 1) alto_avl--;
    return t;
}

pnodo borranodo(pnodo t)
{
    if (t != NULL)
    {
       	p("\nNodo a eliminar:%3d",(t)->info);getch();

        t->izq = borranodo(t->izq);
        t->der = borranodo(t->der);
        free(t); //borra la raíz subárbol
    }
    return NULL;
}

void mostrar(pnodo x,int y) // como arbol en orden
{
	int i;
	if(x!=NULL)
	{
		mostrar(x->der,y+1);
			for(i=1;i<=y;i++)
			p("        ");
		p("%2d(%d)\n\n",x->info,x->bal);
		mostrar(x->izq,y+1);
	 }
}

pnodo deltree(pnodo t)
{
    alto_avl = 0;
    return borranodo(t);
}


int menu(void)
{
	int op;

	 do
	 {
		system("cls");
		p("\n\t\t MENU DE OPCIONES DEL BALANCEO DE UN ARBOL AVL\n");
		p("\n\t\t\t ADDELSON-VELSKII Y LANDIS\n");
		p("\n\n\t\t\t - Ingresar Datos           <1>\n");
		p("\n\n\t\t\t - Mostrar en Arbolescencia <2>\n");
		p("\n\n\t\t\t - Borrar Arbol             <3>\n");
		p("\n\n\t\t\t - Salir                    <4>\n");
		p("\n\n\t\t\t   Ingrese Opcion [1-4]  :  ");
		scanf("%d",&op);
	 }while(op<1||op>4);
	 return op;
 }

void vaciopausa()
{
  p("\n Arbol Vacio\n\n"); getch();
}


int main()
{
    pnodo t=NULL;
    int num;

    int op;
 do
   {
    op=menu();
    system("cls");
    switch(op)
	{
	case 1:
			p("\n Ingrese Elemento al Arbol:");
            s("%d",&num);
            t=InsertarAVL(num,t);
 	     	break;

	case 2:
			 if(t)
			 {
			 p("\n\n Arbolescencia en Orden\n\n");
             mostrar(t,0); getch();
			 }
			 else vaciopausa();
     		break;

	case 3:
		      if(t)
			 {
		     p("\n\n Borrar el Arbol \n\n");
             p("\n Presione una tecla y comenzar  a borrar nodos!!");getch();
             deltree(t);
             t=NULL;
             p("\n\n Arbol borrado !!\n\n");getch();
			 }
			 else vaciopausa();

	  }
	}while(op<4);

   getch();

 return 0;
}
