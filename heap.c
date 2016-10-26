#include "heap.h"
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#define TAM_INICIAL 20
//redim
#define FACTOR_DE_CARGA 0.7
#define INCREMENTO_CAPACIDAD 2
#define DECREMENTO_CAPACIDAD 2

struct heap{
	//char *array[];
	void* arreglo[];
	size_t cantidad;
	size_t capacidad;
	cmp_func_t cmp;

};

heap_t *heap_crear(cmp_func_t cmp){
	
	heap_t *heap = malloc(sizeof(heap_t));
	
	if(!heap)
		return NULL;

	//heap->array = malloc(sizeof(char*)*CANTIDAD_INICIAL);
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
	
	for(size_t i=0;<n;i++){	

		if(heap->cantidad >= (heap->capacidad*FACTOR_DE_CARGA))//Podemos meter esto en la funcion redimensionar,
			//llamarla siempre para no repetir codigo y que ella decida si agrandar, achicar o no hacer nada
			//(Correcion de Martin)
			heap_redimensionar(heap,heap->capacidad*INCREMENTO_CAPACIDAD); //podria validar

		//heap->arreglo[i] = arreglo[i];// Si hacemos esto el heap queda con el mismo orden que el arreglo
		//heap->cantidad ++;	
		heap_encolar(heap, arreglo[i]);
	}
		
	return heap;

}

bool heap_esta_vacio(const heap_t *heap){
	return heap->cantidad == 0;
}

void *heap_ver_max(const heap_t *heap){
	if(!heap->cantidad || !heap)
		return NULL;

	return heap->arreglo[0];
}

void heap_destruir(heap_t *heap, void destruir_elemento(void *e)){
	
	if(!heap || !heap->cantidad)
		return;

	for(size_t i=0;i<heap->cantidad;i++){
		if(destruir_elemento)
			destruir_elemento(heap->arreglo[i]);	
	}
	free(heap->arreglo);
	free(heap);
}

bool heap_redimensionar(heap_t *heap,size_t nueva_dim){
	void *aux_array[];
	//Falta definir un heap_aux
	if(!heap_aux)
		return false;


	aux = realloc(heap->arreglo,sizeof(void*)*nueva_dim);

	if(!aux){
		heap_destruir(heap_aux);
		return false;
	}

	heap->capacidad = nueva_dim;

	return true;
}

bool heap_encolar(heap_t *heap,void *elemento){
	
	if(!heap || !elemento)
		return false;
	
	if(heap->cantidad >= (heap->capacidad*FACTOR_DE_CARGA))
		heap_redimensionar(heap,heap->capacidad*INCREMENTO_CAPACIDAD); //podria validar
	
	heap->arreglo[heap->cantidad] = elemento;

	//heap_sort(heap);//reorganizar el arreglo
	//Hacer upheap porque el unico elemento que puede estar desordenado es el del final
	upheap(heap,heap->cantidad);
	heap->cantidad ++;
	
	return false;
}

void heap_destruir(heap_t *heap, void destruir_elemento(void *e)){
	
	if(!heap || heap->cantidad){
		if(destruir_elemento){
			for(int i=0;i<heap->cantidad;i++){
				destruir_elemento(heap->arreglo);
			}
		}
	}
	free(heap->arreglo);
	free(heap);

}

void *heap_desencolar(heap){
	
	void *aux;

	if(!heap || !heap->cantidad)
		return NULL;

	aux = heap->arreglo[0];
	heap->arreglo[0] = heap->arreglo[cantidad-1];	
	//heap_sort(heap);//reorganizar
	//Hacer downheap desde la raiz(heap_sort no porque se supone que hay 
	//un solo elemento desordenado, y es el primero)
	downheap(heap,0);
	
	heap->cantidad --;

	return aux;
}

void heapsort(void *elementos[], size_t cant, cmp_func_t cmp){
	for(size_t i = (cant-1)/2-1;i>=0;i--){
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

	if(pos_h_izq < heap -> cantidad && cmp(elementos[posicion],elementos[pos_h_izq]) <0)
		pos_mayor = pos_h_izq;

	if(pos_h_der < heap -> cantidad && cmp(elementos[pos_mayor],elementos[pos_h_der]) <0)
		pos_mayor = pos_h_der;

	if(pos_mayor != posicion){
		swap(elementos, posicion, pos_mayor);
		downheap(elementos,cant,pos_mayor,cmp);
	}

}


/*//podrian recibir el arreglo down y up heap, y heapify lo mismo
void downheap(heap_t *heap,size_t posicion){
	size_t pos_h_izq,pos_h_der,pos_mayor;
	
	if(posicion >= heap->cantidad)
		return;

	pos_h_izq = posicion*2+1;
	pos_h_der = posicion*2+2;
	//pos_mayor = i; //i no se inicializa nunca 
	pos_mayor = posicion;

	if(pos_h_izq < heap->cantidad && heap->arreglo[posicion] < heap->arreglo[pos_h_izq])
		pos_mayor = pos_h_izq;

	if(pos_h_der < heap->cantidad && heap->arreglo[pos_mayor] < heap->arreglo[pos_h_der])
		pos_mayor = pos_h_der;

	if(pos_mayor != posicion){
		swap(heap->arreglo[posicion],heap->arreglo[pos_mayor]);
		downheap(heap,pos_mayor);
	}
}*/

void upheap(void *elementos[], size_t posicion, cmp_func_t cmp){
	size_t pos_padre;

	if(!posicion)
		return;

	pos_padre = (posicion-1)/2;

	if(cmp(elementos[posicion]elementos[pos_padre]))>0{
		swap(elementos,posicion,pos_padre);
		upheap(elementos,pos_padre,cmp);
	}
}
