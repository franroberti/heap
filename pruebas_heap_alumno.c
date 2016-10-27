#include "heap.h"
#include "testing.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>  // For ssize_t in Linux.


int comparar_cadenas(const void* a, const void*b){
    return strcmp((char*)a,(char*)b);
}

int comparar_enteros(const void* a, const void*b){
	if(*(int*)a > *(int*)b)
		return 1;
	if(*(int*)a < *(int*)b)
		return -1;

	return 0;
}

static void prueba_crear_heap_vacio()
{
    heap_t* heap = heap_crear(comparar_cadenas);

    print_test("Prueba crear heap vacio", heap);
    print_test("Prueba heap la cantidad de elementos es 0", heap_cantidad(heap) == 0);
    print_test("Prueba heap esta vacio", heap_esta_vacio(heap));
    print_test("Prueba heap ver maximo es NULL", !heap_ver_max(heap));
    print_test("Prueba heap desencolar es NULL", !heap_desencolar(heap));

    heap_destruir(heap,NULL);
}

static void prueba_heap_encolar_cadenas(){
    heap_t* heap = heap_crear(comparar_cadenas);

    char *clave4 = "cabra";
    char *clave2 = "gato";
    char* clave7 = "jirafa";
    char *clave5 = "mono";
    char *clave1 = "perro";
    char *clave3 = "vaca";
    char *clave6 = "zorro";
    
    print_test("Prueba heap encolar cadenas clave1", heap_encolar(heap, clave1));
    print_test("Prueba heap encolar cadenas clave2", heap_encolar(heap, clave2));
    print_test("Prueba heap ver max es clave2", heap_ver_max(heap)==clave1);
    print_test("Prueba heap encolar cadenas clave3", heap_encolar(heap, clave3));
    print_test("Prueba heap encolar cadenas clave4", heap_encolar(heap, clave4));
    print_test("Prueba heap la cantidad de elementos es 4", heap_cantidad(heap) == 4);
    print_test("Prueba heap ver max es clave3", heap_ver_max(heap)==clave3);
    print_test("Prueba heap encolar cadenas clave5", heap_encolar(heap, clave5));
    print_test("Prueba heap encolar cadenas clave6", heap_encolar(heap, clave6));
    print_test("Prueba heap encolar cadenas clave7", heap_encolar(heap, clave7));
    print_test("Prueba heap la cantidad de elementos es 7", heap_cantidad(heap) == 7);
    print_test("Prueba heap ver max es clave6", heap_ver_max(heap)==clave6);

    heap_destruir(heap,NULL);
}

static void prueba_heap_desencolar_cadenas(){
    heap_t* heap = heap_crear(comparar_cadenas);

    char *clave4 = "cabra";
    char *clave2 = "gato";
    char* clave7 = "jirafa";
    char *clave5 = "mono";
    char *clave1 = "perro";
    char *clave3 = "vaca";
    char *clave6 = "zorro";
    
    print_test("Prueba heap encolar cadenas clave1", heap_encolar(heap, clave1));
    print_test("Prueba heap encolar cadenas clave2", heap_encolar(heap, clave2));
    print_test("Prueba heap la cantidad de elementos es 2", heap_cantidad(heap) == 2);
    print_test("Prueba heap desencolar cadenas es clave1", heap_desencolar(heap)==clave1);
    print_test("Prueba heap desencolar cadenas es clave2", heap_desencolar(heap)==clave2);
    print_test("Prueba heap desencolar cadenas es NULL", heap_desencolar(heap)==NULL);
    print_test("Prueba heap la cantidad de elementos es 0", heap_cantidad(heap) == 0);
    print_test("Prueba heap encolar cadenas clave3", heap_encolar(heap, clave3));
    print_test("Prueba heap encolar cadenas clave4", heap_encolar(heap, clave4));
    print_test("Prueba heap ver max es es clave3", heap_ver_max(heap)==clave3);
    print_test("Prueba heap encolar cadenas clave5", heap_encolar(heap, clave5));
    print_test("Prueba heap encolar cadenas clave6", heap_encolar(heap, clave6));
    print_test("Prueba heap desencolar cadenas es clave6", heap_desencolar(heap)==clave6);
    print_test("Prueba heap encolar clave7", heap_encolar(heap, clave7));
    print_test("Prueba heap desencolar es clave6", heap_ver_max(heap)==clave3);

    heap_destruir(heap,NULL);
}

static void prueba_heap_encolar_enteros(){
    heap_t* heap = heap_crear(comparar_enteros);

    int clave4 = 6;
    int clave2 = 30;
    int clave7 = 555;
    int clave5 = 3244;
    int clave1 = 3245;
    int clave3 = 45213;
    int clave6 = 543254;
    
    print_test("Prueba heap encolar enteros clave1", heap_encolar(heap, &clave1));
    print_test("Prueba heap encolar enteros clave2", heap_encolar(heap, &clave2));
    print_test("Prueba heap ver max es clave2", heap_ver_max(heap)==&clave1);
    print_test("Prueba heap encolar enteros clave3", heap_encolar(heap, &clave3));
    print_test("Prueba heap encolar enteros clave4", heap_encolar(heap, &clave4));
    print_test("Prueba heap ver max es clave3", heap_ver_max(heap)==&clave3);
    print_test("Prueba heap encolar enteros clave5", heap_encolar(heap, &clave5));
    print_test("Prueba heap encolar enteros clave6", heap_encolar(heap, &clave6));
    print_test("Prueba heap encolar enteros clave7", heap_encolar(heap, &clave7));
    print_test("Prueba heap ver max es clave6", heap_ver_max(heap)==&clave6);

    heap_destruir(heap,NULL);
}

static void prueba_heap_desencolar_enteros(){
    heap_t* heap = heap_crear(comparar_enteros);
  
    int clave4 = 6;
    int clave2 = 30;
    int clave7 = 555;
    int clave5 = 3244;
    int clave1 = 3245;
    int clave3 = 45213;
    int clave6 = 543254;
    
    print_test("Prueba heap encolar enteros clave1", heap_encolar(heap, &clave1));
    print_test("Prueba heap encolar enteros clave2", heap_encolar(heap, &clave2));
    print_test("Prueba heap desencolar enteros es clave1", heap_desencolar(heap)==&clave1);
    print_test("Prueba heap desencolar enteros es clave2", heap_desencolar(heap)==&clave2);
    print_test("Prueba heap desencolar enteros es NULL", heap_desencolar(heap)==NULL);
    print_test("Prueba heap encolar enteros clave3", heap_encolar(heap, &clave3));
    print_test("Prueba heap encolar enteros clave4", heap_encolar(heap, &clave4));
    print_test("Prueba heap desencolar enteros es clave3", heap_ver_max(heap)==&clave3);
    print_test("Prueba heap encolar enteros clave5", heap_encolar(heap, &clave5));
    print_test("Prueba heap encolar enteros clave6", heap_encolar(heap, &clave6));
    print_test("Prueba heap desencolar enteros es clave6", heap_desencolar(heap)==&clave6);
    print_test("Prueba heap encolar enteros clave7", heap_encolar(heap, &clave7));
    print_test("Prueba heap desencolar enteros es clave6", heap_ver_max(heap)==&clave3);

    heap_destruir(heap,NULL);
}

static void prueba_heap_free_propio(){
    heap_t* heap = heap_crear(comparar_enteros);
  
	int *aux,i;

	for(i=0;i<100;i++){
		aux = malloc(sizeof(int));
		*aux = i;
    		heap_encolar(heap,aux);
	}

    print_test("Prueba heap free propio", *(int*)(heap_ver_max(heap))== 99);
    heap_destruir(heap,free);	
}
//Encola en volumen, 
static void prueba_heap_volumen(int tam){
    heap_t* heap = heap_crear(comparar_enteros);
  
	int i,*aux;

	for(i=0;i<tam;i++){
		aux = malloc(sizeof(int));
		*aux = i;
    		heap_encolar(heap,aux);
	}
	
    print_test("Prueba heap de volumen", *(int*)(heap_ver_max(heap))== tam-1);

    heap_destruir(heap,free);
}

//Se pasa un arreglo con claves ordenadas de menor a mayor, y se espera que 
//las encole a un heap, para luego ir obteniendo de mayor a menor.
static void prueba_heapify(size_t tam){
	void** arreglo = malloc(sizeof(int*)*tam);

	for(int i=0;i<(int)tam;i++){
		int* aux = malloc(sizeof(int));
		*aux = i;
		arreglo[i]=aux;
	} 	

	heap_t* heap = heap_crear_arr(arreglo,tam,comparar_enteros); 
	print_test("Prueba heap_crear_arr devuelve heap ", heap);
	print_test("Prueba heap_crear_arr, el heap no esta vacio",!heap_esta_vacio(heap));
	print_test("Prueba heap_crear_arr, ver_max",*(int*)heap_ver_max(heap)==*(int*)arreglo[tam-1]);

	bool ok;
	for(int i =(int)tam-1;i>=0;i--){
		ok = (heap_desencolar(heap) == arreglo[i]);
	
	}
	print_test("Prueba orden de desencolado en heapify",ok);

	

	for(int i = 0;i<(int)tam;i++){
		free(arreglo[i]);
	}
	free(arreglo);

	heap_destruir(heap,free);
	
}


//Se pasa un arreglo con claves ordenadas de menor a mayor, y se espera que 
//las encole a un heap, para luego ir obteniendo de mayor a menor.
static void prueba_heap_sort(size_t tam){
	void** arreglo = malloc(sizeof(int*)*tam);

	for(int i=0;i<(int)tam;i++){
		int* aux = malloc(sizeof(int));
		*aux = i;
		arreglo[i]=aux;
	} 	
	
	heap_sort(arreglo,tam,comparar_enteros);
	
	bool ok=true;
	for(int i = 0;i<=(int)tam-2;i++){
		if(comparar_enteros(arreglo[i],arreglo[i+1])>0){
			ok = false;
			break;
		}
	}

	print_test("Prueba orden de arreglo prueba_heap_sort",ok);
	

	for(int i = 0;i<(int)tam;i++){
		free(arreglo[i]);
	}
	free(arreglo);

	
}



void prueba_heap_sort_2(){
	size_t tam = 3;
	void** arreglo = malloc(sizeof(int*)*tam);

	int* a = malloc(sizeof(int));
	int* b = malloc(sizeof(int));
	int* c = malloc(sizeof(int));

	*a = 20;
	*b = 300;
	*c = 4000;

	arreglo[1]=a;
	arreglo[2]=b;
	arreglo[0]=c;

	heap_sort(arreglo,tam,comparar_enteros);

	print_test("Prueba heap_sort, ver pos 0 es a", arreglo[0]==a);
	print_test("Prueba heap_sort, ver pos 1 es b", arreglo[1]==b);
	print_test("Prueba heap_sort, ver pos 2 es c", arreglo[2]==c);

	heap_sort(arreglo,tam,comparar_enteros);

	bool ok=true;
	if(arreglo[0]!=a || arreglo[1] != b || arreglo[2]!=c) ok = false;
	print_test("Prueba heap_sort en un arreglo ordenado",ok);
	

	for(int i = 0;i<(int)tam;i++){
		free(arreglo[i]);
	}
	free(arreglo);


}
void prueba_heap_encolar_memoria_dinamica(){
	heap_t* heap = heap_crear(comparar_enteros);

	
	int* a = malloc(sizeof(int));
	int* b = malloc(sizeof(int));
	int* c = malloc(sizeof(int));

	*a = 1;
	*b = 2;
	*c = 3;
	
	print_test("Prueba heap encolar elemento a",heap_encolar(heap,a));
	print_test("Prueba heap encolar elemento b",heap_encolar(heap,b));
	print_test("Prueba heap encolar elemento c",heap_encolar(heap,c));
	print_test("Ver maximo es c",heap_ver_max(heap)==c);

	heap_destruir(heap,free);

}
void pruebas_heap_alumno()
{
    /* Ejecuta todas las pruebas unitarias. */
    prueba_crear_heap_vacio();
    prueba_heap_encolar_cadenas();
    prueba_heap_desencolar_cadenas();
    prueba_heap_encolar_enteros();
    prueba_heap_desencolar_enteros();
    prueba_heap_free_propio();
    prueba_heap_volumen(5000);
    prueba_heapify(5000);
    prueba_heap_sort(100);
    prueba_heap_sort_2(1000);
   	prueba_heap_encolar_memoria_dinamica();

    if(!failure_count())
        printf("Se finalizaron todas las pruebas sin errores\n");
}
