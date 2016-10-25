
#define CANTIDAD_INICIAL 20

//redim
#define FACTOR_DE_CARGA 0.7
#define INCREMENTO_CAPACIDAD 2
#define DECREMENTO_CAPACIDAD 2

struct heap{

	char *array[];
	size_t cantidad;
	size_t capacidad;
	cmp_func_t cmp;

};

heap_t *heap_crear(cmp_func_t cmp){
	
	heap_t *heap = malloc(sizeof(heap_t));
	
	if(!heap)
		return NULL;

	heap->array = malloc(sizeof(*char)*CANTIDAD_INICIAL);	

	if(!heap->array){
		free(heap);
		return NULL;
	}

	heap->cantidad = 0;
	heap->capacidad = CANTIDAD_INICIAL;
	heap->cmp = cmp;

	return heap;
}

heap_t *heap_crear_arr(void *arreglo[], size_t n, cmp_func_t cmp){
	
	heap_t *heap = heap_crear(cmp);
	
	for(size_t i=0;<n;i++){	

		if(heap->cantidad >= (heap->capacidad*FACTOR_DE_CARGA))
			heap_redimensionar(heap,heap->capacidad*2);

		heap->arreglo[i] = arreglo[i];

		heap->cantidad ++;	
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
	
	for(i=0;i<heap->cantidad;i++){
		if(destruir_elemento)
			destruir_elemento(heap->arreglo[i]);	

		free(heap->arreglo);
	}
	
	free(heap);
}
