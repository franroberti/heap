#include "heap.h"
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#define TAM_INICIAL 20
//redim
#define FACTOR_DE_CARGA_MAX 0.7
#define FACTOR_DE_CARGA_MIN 0.15
#define INCREMENTO_CAPACIDAD 2
#define DECREMENTO_CAPACIDAD 2

bool heap_redimensionar(heap_t *heap);
void downheap(void *elementos[],size_t cant, size_t posicion, cmp_func_t cmp);
void upheap(void *elementos[], size_t posicion, cmp_func_t cmp);
void swap(void* elementos[], size_t pos1, size_t pos2);

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
	
	heap_t *heap = heap_crear(cmp);
	
	for(size_t i=0;i<n;i++){	
		heap_encolar(heap, arreglo[i]);
	}
		
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

	return (void*)heap->arreglo[0];
}

bool heap_redimensionar(heap_t *heap){
	double fc = (double)(heap->cantidad)/((double)heap->capacidad);

	if((fc>=FACTOR_DE_CARGA_MAX)||((fc<=FACTOR_DE_CARGA_MIN) && (heap->capacidad > TAM_INICIAL))){
		size_t tam;
		if(fc>=FACTOR_DE_CARGA_MAX) tam = heap->capacidad*INCREMENTO_CAPACIDAD;

		else tam = heap->capacidad/DECREMENTO_CAPACIDAD;

		void* aux_array = realloc(heap->arreglo,sizeof(void*)*tam);
		if(!aux_array) return false;
		heap->arreglo = aux_array;
		heap->capacidad = tam;
	}

	return true;
}

bool heap_encolar(heap_t *heap,void *elemento){
	
	if(!heap || !elemento)
		return false;
		
	heap->arreglo[heap->cantidad] = elemento;
	upheap(heap->arreglo, heap->cantidad, heap->cmp);
	heap->cantidad ++;

	if(!heap_redimensionar(heap)) return false;
	
	
	return true;
}

void heap_destruir(heap_t *heap, void destruir_elemento(void *e)){
	
	if(!heap)
		return;

	if(heap->cantidad){
		if(destruir_elemento){
			for(size_t i=0;i<heap->cantidad;i++){
				destruir_elemento(heap->arreglo[i]);
			}
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
	if(!heap_redimensionar(heap)) return false;
	return aux;
}

void heap_sort(void *elementos[], size_t cant, cmp_func_t cmp){
	for(int i = (int)(cant/2)-1;i>=0;i--){
		downheap(elementos,cant,i,cmp);
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
