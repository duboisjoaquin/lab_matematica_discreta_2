
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "API2024Parte2.h"
#include "main_aux.c"

/*
COMANDOS CON LOS QUE COMPILAMOS:
gcc -Wall -Wextra -O3 -std=c99 -c APIG24.c API2024Parte2.c main.c 
gcc APIG24.o API2024Parte2.o main.o -o out 
./out < "Grafo a eleccion"
*/


int main(void){
	Grafo graf = NULL;      
	char res; 
  int random=0; 
	graf=ConstruirGrafo();
  if(graf==NULL){
    printf("Error al crear el grafo\n");
    return 0;
  }

	u32 cant_vertices = NumeroDeVertices(graf);

	printf("Grafo creado\n");
	printf("Hay %d vertices \n", graf->total_vertices);
	printf("Su delta es: %d  \n", Delta(graf));

  color c_natural=0, c_descendente=0, c_pares_impares=0, c_x_grado=0, c_eleccion=0, c_menor=0;

	//creacion de arreglos con los diferentes ordenes

  u32 *orden_natural=calloc(cant_vertices,sizeof(u32));         //arreglo de vertices ordenados de 0 a n-1
  u32 *orden_descendente=calloc(cant_vertices,sizeof(u32));     //arreglo de vertices ordenados de n-1 a 0
  u32 *orden_pares_impares=calloc(cant_vertices,sizeof(u32));   //arreglo de vertices ordenados de pares decrecientes e impares crecientes
  u32 *orden_x_grado=calloc(cant_vertices,sizeof(u32));         //arreglo de vertices ordenados por grado
  u32 *orden_eleccion=calloc(cant_vertices,sizeof(u32));        //arreglo de vertices ordenados a eleccion
  u32 *orden_minimo=calloc(cant_vertices,sizeof(u32));          //arreglo que guarda el color del orden inicial que tuvo mejor coloreo
  
  //creacion de arreglos para albergar los colores de los distintos ordenes

  color *c_array_natural=calloc(cant_vertices,sizeof(color));       //arreglo de vertices ordenados de 0 a n-1
  color *c_array_descendente=calloc(cant_vertices,sizeof(color));   //arreglo de vertices ordenados de n-1 a 0
  color *c_array_pares_impares=calloc(cant_vertices,sizeof(color)); //arreglo de vertices ordenados de pares decrecientes e impares crecientes
  color *c_array_x_grado=calloc(cant_vertices,sizeof(color));       //arreglo de vertices ordenados por grado
  color *c_array_eleccion=calloc(cant_vertices,sizeof(color));      //arreglo de vertices ordenados a eleccion
  
 
  //printf("pancho\n"); //SegFault checer :)

	//inicializacion
	for(u32 i=0, j=cant_vertices-1;i<cant_vertices;i++,j--){
		orden_natural[i]=i;             //Orden natural
		orden_descendente[i]= j;        //Orden descendente
		orden_x_grado[i]=i;           //Orden por grado
		orden_eleccion[i]=i;          //Orden a eleccion
	}


	//Orden pares decrecientes e impares crecientes
  
	u32 indice_impar;
	u32 indice_par;

	if (cant_vertices%2==0){
		indice_impar = (cant_vertices/2);
	}else{
		indice_impar = ((cant_vertices+1)/2);
		}

	indice_par = indice_impar-1;


	for(u32 i=0, j=indice_impar, k=indice_par; i<graf->total_vertices; i++){
		if(i%2==0){
			orden_pares_impares[k]=i;
			k--;
		}else{
			orden_pares_impares[j]=i;
			j++;
		}
	}

	//orden por grado

	mergeSortGrado(graf, orden_x_grado, 0, cant_vertices-1);

	//orden a eleccion
	//intercambia indice i con j donde i es par y j impar (en caso de tener una cantidad impar de elementos, el ultimo no cambia)

	u32 aux, aux2;

	//inicializacion

	if (cant_vertices%2==0){
		for(u32 i=0; i<cant_vertices-1; i+=2){        
			aux = orden_eleccion[i];
			aux2 = orden_eleccion[i+1];
			orden_eleccion[i] = aux2;
			orden_eleccion[i+1] = aux;
		}
	}else
		for(u32 i=0; i<cant_vertices-2; i+=2){
			aux = orden_eleccion[i];
			aux2 = orden_eleccion[i+1];
			orden_eleccion[i] = aux2;
			orden_eleccion[i+1] = aux;
	}

	printf("Ordenes creados\n");

  c_natural=Greedy(graf,orden_natural);
  printf("Chi Orden Natural = %d\n", c_natural);
  for(u32 i=0; i<50; i++){

    res=GulDukat(graf,orden_natural);
    c_natural=Greedy(graf,orden_natural);
    printf("GK (%d) -> %d       ", res,c_natural);
    
    res=ElimGarak(graf,orden_natural);
    c_natural=Greedy(graf,orden_natural);
    printf("EG (%d)-> %d\n", res, c_natural);

  }

  printf("\n");
  ExtraerColores(graf,c_array_natural);


  c_descendente=Greedy(graf,orden_descendente);
  printf("Chi Orden Descendente = %d\n", c_descendente);
  for(u32 i=0; i<50; i++){

    res=GulDukat(graf,orden_descendente);
    c_descendente=Greedy(graf,orden_descendente);
    printf("GK (%d) -> %d       ", res,c_descendente);
    
    res=ElimGarak(graf,orden_descendente);
    c_descendente=Greedy(graf,orden_descendente);
    printf("EG (%d)-> %d\n", res, c_descendente);

  }
  
  printf("\n");
  ExtraerColores(graf,c_array_descendente);


  c_pares_impares=Greedy(graf,orden_pares_impares);
  printf("Chi Orden pares_impares = %d\n", c_pares_impares);
  for(u32 i=0; i<50; i++){

    res=GulDukat(graf,orden_pares_impares);
    c_pares_impares=Greedy(graf,orden_pares_impares);
    printf("GK (%d) -> %d       ", res,c_pares_impares);
    
    res=ElimGarak(graf,orden_pares_impares);
    c_pares_impares=Greedy(graf,orden_pares_impares);
    printf("EG (%d)-> %d\n", res, c_pares_impares);

  }

  printf("\n");
  ExtraerColores(graf,c_array_pares_impares);


  c_x_grado=Greedy(graf,orden_x_grado);
  printf("Chi Orden x_grado = %d\n", c_x_grado);
  for(u32 i=0; i<50; i++){

    res=GulDukat(graf,orden_x_grado);
    c_x_grado=Greedy(graf,orden_x_grado);
    printf("GK (%d) -> %d       ", res,c_x_grado);
    
    res=ElimGarak(graf,orden_x_grado);
    c_x_grado=Greedy(graf,orden_x_grado);
    printf("EG (%d)-> %d\n", res, c_x_grado);

  }

  printf("\n");
  ExtraerColores(graf,c_array_x_grado);

  

  c_eleccion=Greedy(graf,orden_eleccion);
  printf("Chi Orden eleccion = %d\n", c_eleccion);
  for(u32 i=0; i<50; i++){

    res=GulDukat(graf,orden_eleccion);
    c_eleccion=Greedy(graf,orden_eleccion);
    printf("GK (%d) -> %d       ", res,c_eleccion);
    
    res=ElimGarak(graf,orden_eleccion);
    c_eleccion=Greedy(graf,orden_eleccion);
    printf("EG (%d)-> %d\n", res, c_eleccion);

  }

  printf("\n");
  ExtraerColores(graf,c_array_eleccion);


  c_menor=minc(c_natural,minc(c_descendente,minc(c_pares_impares,minc(c_x_grado,c_eleccion))));

  if(c_menor==c_natural){
    ImportarColores(c_array_natural,graf);
    for(u32 i=0; i<cant_vertices;i++){
      orden_minimo[i]=orden_natural[i];
    }
  } 
  else if(c_menor==c_descendente){
    ImportarColores(c_array_descendente,graf);
    for(u32 i=0; i<cant_vertices;i++){
      orden_minimo[i]=orden_descendente[i];
    }
  } 
  else if(c_menor==c_pares_impares){
    ImportarColores(c_array_pares_impares,graf);
    for(u32 i=0; i<cant_vertices;i++){
      orden_minimo[i]=orden_pares_impares[i];
    }
  } 
  else if(c_menor==c_x_grado){
    ImportarColores(c_array_x_grado,graf);
    for(u32 i=0; i<cant_vertices;i++){
      orden_minimo[i]=orden_x_grado[i];
    }
  } 
  else if(c_menor==c_eleccion){
    ImportarColores(c_array_eleccion,graf);
    for(u32 i=0; i<cant_vertices;i++){
      orden_minimo[i]=orden_eleccion[i];
    }
  }

  printf("\nel color mas chico es %d\n",c_menor);
  c_menor=Greedy(graf,orden_minimo);

  for(int i=0; i<500; i++){
    random = rand() % 2;
    if(random==1){
      printf("GK (%d) -> %d\n", res,c_menor);
      c_menor=Greedy(graf,orden_minimo);
      res=GulDukat(graf,orden_minimo);
    }
    else{
      printf("EG (%d) -> %d\n", res,c_menor);
      c_menor=Greedy(graf,orden_minimo);
      res=ElimGarak(graf,orden_minimo);
    }
  }

  ExtraerColores(graf,c_array_natural);
  if(es_coloreo_propio(graf,c_array_natural,orden_minimo)){
    printf("El coloreo es propio\n");
  }
  else{
    printf("El coloreo no es propio\n");
  }

	//printf("Termino\n");

  //liberacion de memoria
  free(orden_natural);
  free(orden_descendente);
  free(orden_pares_impares);
  free(orden_x_grado);
  free(orden_eleccion);
  free(orden_minimo);

  free(c_array_natural);
  free(c_array_descendente);
  free(c_array_pares_impares);
  free(c_array_x_grado);
  free(c_array_eleccion);
  
  DestruirGrafo(graf);


    return 0;
  }