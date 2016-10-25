
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

};f

heap_t *heap_crear(cmp_func_t cmp){
	
	heap_t *heap = malloc(sizeof(heap_t));
	
	if(!heap)
		return NULL;

	heap->array = malloc(sizeof(char*)*CANTIDAD_INICIAL);	

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
			heap_redimensionar(heap,heap->capacidad*INCREMENTO_CAPACIDAD); //podria validar

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
	
	if(!heap || !heap->cantidad)
		return;

	for(size_t i=0;i<heap->cantidad;i++){
		if(destruir_elemento)
			destruir_elemento(heap->arreglo[i]);	

		free(heap->arreglo);
	}
	
	free(heap);
}

bool heap_redimensionar(heap_t *heap,size_t nueva_dim){
	void *aux_array;

	if(!heap_aux)
		return false;

	aux = realloc(heap->arreglo,sizeof(char*)*nueva_dim);

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
	
	heap->arreglo[cantidad] = elemento;

	heap_sort(heap);//reorganizar el arreglo

	heap->cantidad ++;
	
	return false;
}

void *heap_desencolar(heap){
	
	void *aux;

	if(!heap || !heap->cantidad)
		return NULL;

	aux = heap->arreglo[0];
	
	heap->arreglo[0] = heap->arreglo[cantidad-1];	
	
	heap_sort(heap);//reorganizar

	heap->cantidad --;


	return aux;
}

void heapify(heap_t *heap){
	for(size_t i = (cantidad/2)-1;i>=0;i--){
		downheap(heap,i);
	}
}

//podrian recivir el arreglo down y up heap, y heapify lo mismo
void downheap(heap_t *heap,size_t posicion){
	size_t pos_h_izq,posi_h_der,pos_mayor;
	
	if(posicion > heap->cantidad)
		return;

	pos_h_izq = posicion*2+1;
	pos_h_der = posicion*2+2;
	pos_mayor = i;

	if(pos_h_izq < heap->cantidad && heap->arreglo[posicion] < heap->arreglo[pos_h_izq])
		pos_mayor = pos_h_izq;

	if(pos_h_der < heap->cantidad && heap->arreglo[pos_mayor] < heap->arreglo[pos_h_der])
		pos_mayor - pos_h_der;

	if(pos_mayor != posicion)
		swap(heap->arreglo[posicion],heap->arreglo[pos_mayor])

	downheap(heap,pos_mayor);
}


void upheap(heap_t *heap,size_t posicion){
	size_t pos_padre;

	if(!posicion)
		return;

	pos_padre = (posicion-1)/2;

	if(heap->arreglo[posicion]>heap->arreglo[pos_padre])
		swap(heap->arreglo[posicion],heap->arreglo[pos_padre]);

	upheap(heap,pos_padre);
}
