#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <stdbool.h>
#include "APIG24.h"
#include "EstructuraGrafo24.h"

u32 max(u32 a, u32 b){
    u32 max;
    if(a>b){
        max=a;
    } else {
        max=b;
    }
    return max; 
}

//------------------------Parser--------------------------------------------------------------
Grafo parser(Grafo g){
    char char_actual;
    bool graph_yet=false;
    u32 lados=0, vertices=0, delta=1;
    u32 a=0, b=0, i=0;
    int scanf_check=0;


    char_actual=getchar();
    while(!graph_yet && char_actual!=EOF){
        if(char_actual=='c'){
            while (char_actual!='\n') {
                    char_actual=getchar();
                    if (char_actual==EOF) {
                        return NULL;
                    }
                }
        }
        else if(char_actual=='p'){
            scanf_check=scanf(" edge %u %u", &vertices, &lados);
                if(scanf_check!=2){
                    return NULL;
                }
                graph_yet=true;

        }
        char_actual=getchar();
    }
    g->total_vertices=vertices;
    g->total_lados=lados; 
    
    g->vertices_array=calloc(vertices,sizeof(struct vert));

    char_actual=getchar();
    while(char_actual!=EOF && i<lados){
        if(char_actual=='e'){
            scanf_check=scanf(" %u %u ", &a, &b);  
            if (scanf_check!=2) {
                for (unsigned int j = 0; j < i; j++){
                    free(g->vertices_array[j].vecinos); 
                }   
                 
                free(g->vertices_array);
                return NULL; 
            }

            if(g->vertices_array[a].grado==0){
                g->vertices_array[a].color=0;
                g->vertices_array[a].grado=1;
                g->vertices_array[a].vecinos=calloc(1,sizeof(u32));
                g->vertices_array[a].vecinos[0]=b;
                
            } else if(0!=g->vertices_array[a].grado){
                g->vertices_array[a].grado+=1;
                g->vertices_array[a].vecinos=realloc(g->vertices_array[a].vecinos,(g->vertices_array[a].grado)*sizeof(u32));
                g->vertices_array[a].vecinos[(g->vertices_array[a].grado-1)]=b;
                delta=max(g->vertices_array[a].grado,delta);
            }

            if(0==g->vertices_array[b].grado){
                g->vertices_array[b].color=0;
                g->vertices_array[b].grado=1;
                g->vertices_array[b].vecinos=calloc(1,sizeof(u32));
                g->vertices_array[b].vecinos[0]=a;
            } else if(0!=g->vertices_array[b].grado){
                g->vertices_array[b].grado+=1;
                g->vertices_array[b].vecinos=realloc(g->vertices_array[b].vecinos,(g->vertices_array[b].grado)*sizeof(u32));
                g->vertices_array[b].vecinos[(g->vertices_array[b].grado-1)]=a;
                delta=max(g->vertices_array[b].grado,delta);
            }

            
            i++;
        } else {  
            for (unsigned int j = 0; j < i; j++){
                    free(g->vertices_array[j].vecinos); 
            }   
            free(g->vertices_array);
            return NULL;
        }
    char_actual=getchar();
    }
    g->deltaGraf=delta;
    
    return g;
}



 

//------------------------Operaciones para Crear y Destruir un Grafo---------------------------

Grafo ConstruirGrafo(){
    //asumo que parser me va a devolver [{l1,l2},{l2,l3},...]
    
    Grafo G=malloc(sizeof(struct GrafoSt));            //alocar memoria
    assert(G!=NULL);

    G = parser(G);
    assert(G!=NULL); 

    return G;

}

void DestruirGrafo(Grafo G){
    for (unsigned int i = 0; i < G->total_vertices; i++){
        free(G->vertices_array[i].vecinos);
    }
    free(G->vertices_array);
    G->vertices_array=NULL;
    free(G);
    G=NULL;

}




//------------------------Operaciones para Extraer datos de un Grafo---------------------------

u32 NumeroDeVertices(Grafo G){
    return G->total_vertices;
}

u32 NumeroDeLados(Grafo G){
    return G->total_lados;
}

u32 Delta(Grafo G){
    return G->deltaGraf;
}


//------------------------Operaciones para Extraer informacion sobre vertices------------------

u32 Grado(u32 i,Grafo G){
    assert(G!=NULL);
    if(G->total_vertices<=i){
        return 0;
    }

    return G->vertices_array[i].grado;
} 

color Color(u32 i,Grafo G){
    assert(G!=NULL);
    if(G->total_vertices<=i){
        return (4294967296-1);     //(2 a la 32) - 1 
    }

    return G->vertices_array[i].color; 
}

u32 Vecino(u32 j,u32 i,Grafo G){
    assert(G!=NULL);
    if(i>=G->total_vertices ||  G->vertices_array[i].grado<=j){
        return (4294967296-1);     //(2 a la 32) - 1 
    }

    return G->vertices_array[i].vecinos[j];
}

//------------------------Operaciones sobre coloreo de Grafos---------------------------------


void AsignarColor(color x,u32 i,Grafo  G){
    assert(G!=NULL);
    if(i<G->total_vertices){
        G->vertices_array[i].color=x;
    }

}

void ExtraerColores(Grafo G,color* Color){
    u32 i=0;
    while(i<G->total_vertices){
        Color[i]=G->vertices_array[i].color;        
        i++;
    }

}

void ImportarColores(color* Color,Grafo  G){
    u32 i=0;
    while(i<G->total_vertices){
        G->vertices_array[i].color=Color[i];        
        i++;
    }

}










