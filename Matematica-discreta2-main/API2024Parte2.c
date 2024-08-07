#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "APIG24.h"
#include "sort.c"

u32 _max(u32 a, u32 b){
    u32 max;
    if(a>b){
        max=a;
    } else {
        max=b;
    }
    return max; 
}

u32 _min(u32 a, u32 b){
    u32 min;
    if(a>b){
        min=b;
    } else {
        min=a;
    }
    return min; 
}


bool biyeccion_orden(Grafo G, u32* Orden){
    bool* bool_array = calloc(NumeroDeVertices(G), sizeof(bool));
    bool res=true;

    for (u32 i = 0; i < NumeroDeVertices(G) ; i++){
        res = bool_array[Orden[i]]==false && res;
        bool_array[Orden[i]]=true;
    }

    free(bool_array);
    return res;
}

color Greedy(Grafo G, u32* Orden){
  color max_color = 1;
  u32 i = 1;

  if (!biyeccion_orden(G, Orden)) {
    return -1;
  }

  for(u32 v = 0; v<NumeroDeVertices(G); v++){
    AsignarColor(0,v,G); 
  }

  AsignarColor(1, Orden[0], G);

  while (i < NumeroDeVertices(G)) {
    u32 v = Orden[i]; // Vertice actual
    bool* colores_disponibles = calloc(Delta(G)+1, sizeof(bool));

    // Inicializar colores disponibles
    for (u32 j = 1; j <= max_color; j++) {
      colores_disponibles[j] = true;
    }

    // Marcar colores no disponibles
    for (u32 j = 0; j < Grado(v, G); j++) {
      u32 w = Vecino(j, v, G); // Vecino actual
      color color_w = Color(w, G); // Color del vecino
      colores_disponibles[color_w] = false;
    }

    // Buscar color disponible
    color color_v = 1;
    while (color_v <= max_color) {
      if (colores_disponibles[color_v]) {
        break;
      }

      color_v++;
    }

    // Asignar color
    AsignarColor(color_v, v, G);

    // Actualizar color máximo si es necesario
    if (color_v > max_color) {
      max_color = color_v;
    }

    i++;

    free(colores_disponibles); 
  }

  return max_color;
}





char GulDukat(Grafo G, u32 *Orden){
    char res=0;
    // Creamos e inicializamos el arreglo de colores(O(Delta +1) < N)
    u32* M = calloc(Delta(G)+2, sizeof(u32));
    u32* m = calloc(Delta(G)+2, sizeof(u32));

    for(u32 i = 0;i < Delta(G) + 2; i++){
      M[i] = 0;
      m[i]= 0;
    }

    for(u32 i = 0; i < NumeroDeVertices(G); i++){
      if(M[Color(i,G)] == 0){
        M[Color(i,G)] = Grado(i,G);
        m[Color(i,G)] = Grado(i,G);
      }
      else{
        M[Color(i,G)] = _max(M[Color(i,G)],Grado(i,G));
        m[Color(i,G)] = _min(m[Color(i,G)],Grado(i,G));
      }
    }

    // sort gk
    mergeSortGK(G, Orden, 0, NumeroDeVertices(G)-1,M,m);

    if(!(order_check_GK(Orden, G, M, m))){
      res = 1;
    }

    free(M);
    free(m);
    return res;
}


char ElimGarak(Grafo G, u32 *Orden){
    char res=0; 

    // Creamos e inicializamos el arreglo de colores(O(Delta +1) < N)
    u32* colores = calloc(Delta(G)+2, sizeof(u32));
    for(u32 i = 0;i < Delta(G) + 2; i++){
      colores[i] = 0;
    }
    // Cargamos la cantidad de colores
    for(u32 i = 0; i < NumeroDeVertices(G); i++){
      colores[Color(i,G)] += 1;
    }

    //sort eg
    mergeSortEG(G, Orden, 0 , NumeroDeVertices(G)-1, colores);

    if(!(order_check_EG(Orden, G, colores))){
      res = 1;
    }
    free(colores);

    return res;
}