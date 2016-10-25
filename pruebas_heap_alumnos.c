
static void prueba_crear_heap_vacio()
{
    heap* heap = heap_crear(strcmp);

    print_test("Prueba crear heap vacio", heap);
    print_test("Prueba heap la cantidad de elementos es 0", heap_cantidad(heap) == 0);
    print_test("Prueba heap esta vacio", heap_esta_vacio(heap));
    print_test("Prueba heap ver maximo es NULL", !heap_ver_max(heap));
    print_test("Prueba heap desencolar es NULL", !heap_desencolar(heap));

    heap_destruir(heap);
}

static void prueba_heap_encolar(){
    heap_t* heap = heap_crear(strcmp);

    char *clave4 = "cabra";
    char *clave2 = "gato";
    char* clave7 = "jirafa";
    char *clave5 = "mono";
    char *clave1 = "perro";
    char *clave3 = "vaca";
    char *clave6 = "zorro";
    
    print_test("Prueba heap encolar clave1", heap_encolar(heap, clave1));
    print_test("Prueba heap encolar clave2", heap_encolar(heap, clave2));
    print_test("Prueba heap ver max es clave2", heap_ver_max(heap)==clave1);
    print_test("Prueba heap encolar clave3", heap_encolar(heap, clave3));
    print_test("Prueba heap encolar clave4", heap_encolar(heap, clave4));
    print_test("Prueba heap ver max es clave3", heap_ver_max(heap)==clave3);
    print_test("Prueba heap encolar clave5", heap_encolar(heap, clave5));
    print_test("Prueba heap encolar clave6", heap_encolar(heap, clave6));
    print_test("Prueba heap encolar clave7", heap_encolar(heap, clave7));
    print_test("Prueba heap ver max es clave6", heap_ver_max(heap)==clave6);

    heap_destruir(heap);
}

static void prueba_heap_desencolar(){
    heap_t* heap = heap_crear(strcmp);

    char *clave4 = "cabra";
    char *clave2 = "gato";
    char* clave7 = "jirafa";
    char *clave5 = "mono";
    char *clave1 = "perro";
    char *clave3 = "vaca";
    char *clave6 = "zorro";
    
    print_test("Prueba heap encolar clave1", heap_encolar(heap, clave1));
    print_test("Prueba heap encolar clave2", heap_encolar(heap, clave2));
    print_test("Prueba heap desencolar es clave1", heap_desencolar(heap)==clave1);
    print_test("Prueba heap desencolar es clave2", heap_desencolar(heap)==clave2);
    print_test("Prueba heap desencolar es NULL", heap_desencolar(heap)==NULL);
    print_test("Prueba heap encolar clave3", heap_encolar(heap, clave3));
    print_test("Prueba heap encolar clave4", heap_encolar(heap, clave4));
    print_test("Prueba heap desencolar es clave3", heap_ver_max(heap)==clave3);
    print_test("Prueba heap encolar clave5", heap_encolar(heap, clave5));
    print_test("Prueba heap encolar clave6", heap_encolar(heap, clave6));
    print_test("Prueba heap desencolar es clave", heap_desencolar(heap)==clave6);
    print_test("Prueba heap encolar clave7", heap_encolar(heap, clave7));
    print_test("Prueba heap desencolar es clave6", heap_ver_max(heap)==clave3);

    heap_destruir(heap);
}

void pruebas_heap_alumno()
{
    /* Ejecuta todas las pruebas unitarias. */
    prueba_crear_heap_vacio();
    prueba_heap_guardar();
    prueba_heap_encolar();
    prueba_heap_desencolar();

    if(!failure_count())
        printf("Se finalizaron todas las pruebas sin errores\n");
}
