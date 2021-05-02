#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

typedef struct Tarea{
    int tareaID;
    char *descripcion;
    int duracion;
}Tarea;

typedef struct TNodo{
    Tarea tarea;
    struct TNodo *siguiente;
} TNodo;

TNodo * crearListaVacia();
TNodo * crearNodo();
void cargarTareasNodo(TNodo *nodo, int tareaID, char *descripcion, int duracion);
void cargarTareas(TNodo **lista, int tamanio);
void insertarNodoALista(TNodo **lista, TNodo *nodo);
void mostrarTares(TNodo *lista);
void ToDo(TNodo **lista, TNodo **lista2);
void busquedaPorID(TNodo **lista, int tamanio);
void busquedaPorPalabra(TNodo **lista);

int main(){
    srand(time(NULL));

    TNodo *start, *ready, *indice;
    int cantidadAct;

    start = crearListaVacia();
    ready = crearListaVacia();

    printf("Ingrese la cantidad de tareas a cargar: ");
    scanf("%d", &cantidadAct);

    printf("\n CARGAR TAREAS \n");
    cargarTareas(&start, cantidadAct);

    indice = start;
    /*while(indice != NULL){
        mostrarTares(indice);
        indice = indice->siguiente;        
    }

    printf("\n BUSCAR TAREAS POR ID \n");
    busquedaPorID(&start, cantidadAct);

    printf("\n BUSCAR TAREAS POR PALABRA CLAVE \n");
    fflush(stdin);
    busquedaPorPalabra(&start);*/

    printf("\n ANALIZAR SI SE REALIZARON TAREAS \n");
    ToDo(&start, &ready);

    indice = ready;
    printf("\n TAREAS REALIZADAS \n");
    while(indice != NULL){
        mostrarTares(indice);
        indice = indice->siguiente;
    }

    indice = start;
    printf("\n TAREAS PENDIENTES \n");
    while(indice != NULL){
        mostrarTares(indice);
        indice = indice->siguiente;
    }

    indice = start;
    while (indice != NULL)
    {
        TNodo * aux = indice;
        indice = indice->siguiente;
        free(aux);
    }

    indice = ready;
    while (indice != NULL)
    {
        TNodo * aux = indice;
        indice = indice->siguiente;
        free(aux);
    }

    return 0;
}

TNodo * crearListaVacia()
{
    return NULL;
}

TNodo * crearNodo()
{
    TNodo *nuevoNodo = (TNodo*)malloc(sizeof(TNodo));
    nuevoNodo->siguiente = NULL;
    return nuevoNodo;
}

void cargarTareas(TNodo **lista, int tamanio)
{
    TNodo *NuevoNodo;
    for(int i = 0; i < tamanio; i++){
        NuevoNodo = crearNodo();
        printf("-------- TAREA %d-------- \n", i+1);
        fflush(stdin);
        char *descripcion = (char*)malloc(sizeof(char)*100);
        printf("Descripcion de la tarea: ");
        gets(descripcion);

        cargarTareasNodo(NuevoNodo, i + 1, descripcion, rand()% 10 + 1);
        insertarNodoALista(lista, NuevoNodo);
    }
}

void cargarTareasNodo(TNodo *nodo, int tareaID, char *descripcion, int duracion)
{
    nodo->tarea.tareaID = tareaID;
    nodo->tarea.descripcion = descripcion;
    nodo->tarea.duracion = duracion;
}

void insertarNodoALista(TNodo **lista, TNodo *nodo)
{
    TNodo * aux = *lista;

    if(aux != NULL){
        while(aux->siguiente != NULL){
            aux = aux->siguiente;
        }
        aux->siguiente = nodo;
    }else{
        *lista = nodo;
    }
}

void mostrarTares(TNodo *lista)
{
    printf("-------- TAREA %d -------- \n", lista->tarea.tareaID);
    printf("ID: %d \n", lista->tarea.tareaID);
    printf("Duracion: %d hs\n", lista->tarea.duracion);
    printf("Descripcion: %s \n", lista->tarea.descripcion);
}

void ToDo(TNodo **lista, TNodo **lista2)
{
    char respuesta[30]; 
    TNodo * indice = *lista;
    TNodo * indice2 = *lista2;
    TNodo * anterior = indice;
    while((indice) != NULL){
        mostrarTares(indice);
        fflush(stdin);
        printf("La tarea fue realizada? (Responda S/N) ");
        gets(respuesta);
        
        if(respuesta[0] == 'S' || respuesta[0] == 's'){           
            indice2 = indice;
            indice = indice2->siguiente;

            if(anterior->siguiente == indice){
                *lista = indice;
                anterior = indice;
            }else{
                anterior->siguiente = indice;
            }

            indice2->siguiente = *lista2;   
            *lista2 = indice2;    
          
        }else{
            anterior = indice;
            indice = indice->siguiente;
        }    
    }
}

void busquedaPorID(TNodo **lista, int tamanio)
{
    TNodo *indice;
    int id;

    indice = *lista;
    printf("Ingrese el ID de la tarea que desea buscar (ID > 0): ");
    scanf("%d", &id);

    if(id > tamanio){
        printf("El ID ingresado no pertenece a ninguna tarea");
        busquedaPorID(lista, tamanio);
    } else{
        printf("\n TAREA BUSCADA POR ID \n");
        while(indice->tarea.tareaID != id){
            indice = indice->siguiente;
        }
        mostrarTares(indice);
    }
}

void busquedaPorPalabra(TNodo **lista)
{
    char palabraClave[30];
    char *palabraEncont;
    int coincidencia = 0;
    TNodo *indice;

    indice = *lista;
    printf("Ingrese una palabra clave para buscar una tarea: ");
    gets(palabraClave);

    printf("\n TAREA BUSCADA POR PALABRA CLAVE \n");
    while(indice != NULL){
       
        palabraEncont = strstr(indice->tarea.descripcion, palabraClave);

        if(palabraEncont != NULL){
            mostrarTares(indice);
            coincidencia++;
        }
        indice = indice->siguiente;
    }
    
    if(coincidencia == 0){
        printf("No se encontraron resultados \n");
    }
}