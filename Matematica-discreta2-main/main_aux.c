#include <stdio.h>
#include <stdbool.h>

#include "EstructuraGrafo24.h"
#include "APIG24.h"

void mergeGrado(Grafo G, u32 arr[], u32 l, u32 m, u32 r) 
{ 
	u32 i, j, k; 
	u32 n1 = m - l + 1; 
	u32 n2 = r - m; 
	u32 L[n1], R[n2]; 

	for (i = 0; i < n1; i++) 
		L[i] = arr[l + i]; 
	for (j = 0; j < n2; j++) 
		R[j] = arr[m + 1 + j]; 

	i = 0; 
	j = 0; 
	k = l;
    
	while (i < n1 && j < n2) { 
		if (Grado(L[i],G) >= Grado(R[j],G)) { 
			arr[k] = L[i]; 
			i++; 
		} 
		else { 
			arr[k] = R[j]; 
			j++; 
		} 
		k++; 
	} 

	while (i < n1) { 
		arr[k] = L[i]; 
		i++; 
		k++; 
	} 

	while (j < n2) { 
		arr[k] = R[j]; 
		j++; 
		k++; 
	} 
} 

void mergeSortGrado(Grafo G, u32 arr[], u32 l, u32 r)
{ 
	if (l < r) { 
		u32 m = l + (r - l) / 2; 
		mergeSortGrado(G, arr, l, m); 
		mergeSortGrado(G, arr, m + 1, r); 
		mergeGrado(G, arr, l, m, r); 
	} 
}


color minc(color a, color b){
	if(a<=b){
		return a;
	}
	else{
		return b; 
	}
}

// Chequea que el coloreo dado por Greedy sea propio 
bool es_coloreo_propio(Grafo G, color* array_colores, u32* Orden){
  bool res=true;
  u32 vecino=0, i=0, j=0; 
  while(i< NumeroDeVertices(G) && res){
    j=0;
    while(j<Grado(Orden[i],G) && res){
      vecino=Vecino(j,Orden[i],G);
      res= res && array_colores[vecino]!=array_colores[Orden[i]];  
      j++;
    }
    i++; 
  }

  if(!res){
    printf("El vertice %d tiene el mismo color con su vecino %d\n", (i-1), (j-1));
  }

  return res; 
}