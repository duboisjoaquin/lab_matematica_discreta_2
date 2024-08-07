#include <stdio.h>
#include <stdbool.h>

#include "EstructuraGrafo24.h"
#include "APIG24.h"

// Funcion para detectar comparacion entre 2 vertices de un grafo para el algoritmo GulDukat
bool less_gk(Grafo G, u32 a, u32 b, u32 M[], u32 m[]){
    if(Color(a,G)%4==0 && Color(b,G)%4==0){
        if(M[Color(a,G)] == M[Color(b,G)]){
            if(Color(a,G) >= Color(b,G)){
                return true;
            }
            else{
                return false;
            }
        }
        else if(M[Color(a,G)] > M[Color(b,G)]){
            return true;
        }
        else{
            return false;
        }
    }
    else if(Color(a,G)%4==0){
        return true;
    }
    else if(Color(b,G)%4==0){
        return false;
    }
    else if(Color(a,G)%2==0 && Color(b,G)%2==0){
        if((M[Color(a,G)] + m[Color(a,G)]) == (M[Color(b,G)] + m[Color(b,G)])){
            if(Color(a,G) >= Color(b,G)){
                return true;
            }
            else{
                return false;
            }
        }
        else if((M[Color(a,G)] + m[Color(a,G)]) > (M[Color(b,G)] + m[Color(b,G)])){
            return true;
        }
        else{
            return false;
        }
    }
    else if(Color(a,G)%2==0){
        return true;
    }
    else if(Color(b,G)%2==0){
        return false;
    }
    else{
        if(m[Color(a,G)] == m[Color(b,G)]){
            if(Color(a,G) >= Color(b,G)){
                return true;
            }
            else{
                return false;
            }
        }
        else if(m[Color(a,G)] > m[Color(b,G)]){
            return true;
        }
        else{
            return false;
        }
    }   
}

void mergeGK(Grafo G, u32 arr[], u32 l, u32 mid, u32 r, u32 M[], u32 m[]) 
{ 
	u32 i, j, k; 
	u32 n1 = mid - l + 1; 
	u32 n2 = r - mid; 
	u32 L[n1], R[n2]; 

	for (i = 0; i < n1; i++) 
		L[i] = arr[l + i]; 
	for (j = 0; j < n2; j++) 
		R[j] = arr[mid + 1 + j]; 

	i = 0; 
	j = 0; 
	k = l;

	while (i < n1 && j < n2) { 
		if (less_gk(G, L[i], R[j], M, m)) { 
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

void mergeSortGK(Grafo G, u32 arr[], u32 l, u32 r, u32 M[], u32 m[])
{ 
	if (l < r) { 
		u32 mid = l + (r - l) / 2; 
		mergeSortGK(G, arr, l, mid, M, m); 
		mergeSortGK(G, arr, mid + 1, r, M, m); 
		mergeGK(G, arr, l, mid, r, M, m); 
	} 
}

bool order_check_GK(u32 Orden[], Grafo G, u32 M[], u32 m[]){
    bool res = true;
    for(u32 i = 0; i < NumeroDeVertices(G)-1 && res; i++){
        u32 p1,p2;
        p1 = Orden[i];
        p2 = Orden[i+1];
        if(!(less_gk(G, p1, p2, M, m))){
            res = false;
        }
    }
    return res;
}

// Funcion para detectar comparacion entre 2 vertices de un grafo para el algoritmo ElimGarak
bool less_eg(Grafo G, u32 a, u32 b, u32 colores[]){
    if(Color(a,G) == Color(b,G)){
        if(Grado(a, G) >= Grado(b, G)){
            return true;
        }
        else{
            return false;
        }
    }
    else if(Color(a,G)==1){
        return false;
    }
    else if(Color(b,G)==1){
        return true;
    }
    else if(Color(a,G)==2){
        return false;
    }
    else if(Color(b,G)==2){
        return true;
    }
    else{
        if(colores[Color(a,G)] == colores[Color(b,G)]){
            if(Color(a,G) >= Color(b,G)){
                return true;
            }
            else{
                return false;
            }
        }
        else if(colores[Color(a,G)] < colores[Color(b,G)]){
            return true;
        }
        else{
            return false;
        }
    }

}

void mergeEG(Grafo G, u32 arr[], u32 l, u32 m, u32 r, u32 colores[]) 
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
		if (less_eg(G, L[i], R[j], colores)) { 
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

void mergeSortEG(Grafo G, u32 arr[], u32 l, u32 r, u32 colores[])
{ 
	if (l < r) { 
		u32 m = l + (r - l) / 2; 
		mergeSortEG(G, arr, l, m, colores); 
		mergeSortEG(G, arr, m + 1, r, colores); 
		mergeEG(G, arr, l, m, r, colores); 
	} 
}

bool order_check_EG(u32 Orden[], Grafo G, u32 colores[]){
    bool res = true;
    for(u32 i = 0; i < NumeroDeVertices(G)-1 && res; i++){
        u32 p1,p2;
        p1 = Orden[i];
        p2 = Orden[i+1];
        if(!(less_eg(G, p1, p2, colores))){
            res = false;
        }
    }
    return res;
}