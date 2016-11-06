#include "heap.h"
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <stdio.h>

#define TAM_INICIAL 20
#define INCREMENTO_TAM 2
#define DECREMENTO_TAM 4

bool heap_redimensionar(heap_t *heap,size_t tam);
void downheap(void *elementos[],size_t cant, size_t posicion, cmp_func_t cmp);
void upheap(void *elementos[], size_t posicion, cmp_func_t cmp);
void swap(void* elementos[], size_t pos1, size_t pos2);
void _heap_sort(void* elementos[],size_t cant,cmp_func_t cmp);
void heapify(void* elementos[], size_t cant, cmp_func_t cmp);

struct heap{
	void** arreglo;
	size_t cantidad;
	size_t capacidad;
	cmp_func_t cmp;

};

heap_t *heap_crear(cmp_func_t cmp){
	
	heap_t *heap = malloc(sizeof(heap_t));
	
	if(!heap)
		return NULL;
	heap -> arreglo = malloc(sizeof(void*)*TAM_INICIAL);

	if(!heap->arreglo){
		free(heap);
		return NULL;
	}

	heap->cantidad = 0;
	heap->capacidad = TAM_INICIAL;
	heap->cmp = cmp;

	return heap;
}

heap_t *heap_crear_arr(void *arreglo[], size_t n, cmp_func_t cmp){
	
	heapify(arreglo,n,cmp);

	heap_t* heap = heap_crear(cmp);
	free(heap->arreglo);

	heap -> arreglo = arreglo;
	heap->cantidad = n;
	heap->capacidad = n;

	return heap;

}

size_t heap_cantidad(const heap_t *heap){
	return heap->cantidad;
}

bool heap_esta_vacio(const heap_t *heap){
	return heap->cantidad == 0;
}

void *heap_ver_max(const heap_t *heap){
	if(!heap->cantidad || !heap)
		return NULL;

	return heap->arreglo[0];
}

bool heap_redimensionar(heap_t *heap,size_t tam){

	void* aux_array = realloc(heap->arreglo,sizeof(void*)*tam);
	if(!aux_array) return false;
	heap->arreglo = aux_array;
	heap->capacidad = tam;

	return true;
}

bool heap_encolar(heap_t *heap,void *elemento){
	
	if(!heap || !elemento)
		return false;
	

	heap->arreglo[heap->cantidad] = elemento;
	upheap(heap->arreglo, heap->cantidad, heap->cmp);
	heap->cantidad ++;

	if(heap->cantidad == heap->capacidad){
		return heap_redimensionar(heap, heap->capacidad * INCREMENTO_TAM);
	}
	
	return true;
}

void heap_destruir(heap_t *heap, void destruir_elemento(void *e)){
	
	if(!heap)
		return;

	
	if(destruir_elemento){
		for(size_t i=0;i<heap->cantidad;i++){
			destruir_elemento(heap->arreglo[i]);
		}
	}
	
	free(heap->arreglo);
	free(heap);

}

void *heap_desencolar(heap_t* heap){
	
	void *aux;

	if(!heap || !heap->cantidad)
		return NULL;

	aux = heap->arreglo[0];
	heap->arreglo[0] = heap->arreglo[heap->cantidad-1];	

	downheap(heap->arreglo,heap->cantidad,0,heap->cmp);
	
	heap->cantidad --;
	
	size_t carga_min = heap->capacidad/4;

	if(heap -> cantidad < carga_min && heap -> cantidad > TAM_INICIAL){
		heap_redimensionar(heap,heap -> capacidad /DECREMENTO_TAM);
	}

	return aux;
}


void heapify(void* elementos[], size_t cant, cmp_func_t cmp){
	for(int i = (int)(cant-1)/2;i>=0;i--){
		downheap(elementos,cant,i,cmp);
	}
	
}

void heap_sort(void *elementos[], size_t cant, cmp_func_t cmp){
	heapify(elementos,cant,cmp);

	for(int i = (int)cant-1;i>0;i--){
		swap(elementos,0,i);
		downheap(elementos,i,0,cmp);
	}

}



void downheap(void *elementos[],size_t cant, size_t posicion, cmp_func_t cmp){
	size_t pos_h_izq, pos_h_der, pos_mayor;

	if(posicion >= cant){
		return;
	}

	pos_h_izq = posicion*2 + 1;
	pos_h_der = posicion*2 + 2;
	pos_mayor = posicion;

	if(pos_h_izq < cant && cmp(elementos[posicion],elementos[pos_h_izq]) <0)
		pos_mayor = pos_h_izq;

	if(pos_h_der < cant && cmp(elementos[pos_mayor],elementos[pos_h_der]) <0)
		pos_mayor = pos_h_der;

	if(pos_mayor != posicion){
		swap(elementos, posicion, pos_mayor);
		downheap(elementos,cant,pos_mayor,cmp);
	}

}


void upheap(void *elementos[], size_t posicion, cmp_func_t cmp){
	size_t pos_padre;

	if(!posicion)
		return;

	pos_padre = (posicion-1)/2;

	if(cmp(elementos[posicion],elementos[pos_padre])>0){
		swap(elementos,posicion,pos_padre);
		upheap(elementos,pos_padre,cmp);
	}
}

void swap(void* elementos[], size_t pos1, size_t pos2){
	void* aux = elementos[pos1];
	elementos[pos1] = elementos[pos2];
	elementos[pos2] = aux;
}
