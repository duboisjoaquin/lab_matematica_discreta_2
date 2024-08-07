#ifndef EstructuraGrafo24_H
#define EstructuraGrafo24_H


typedef unsigned int u32;
typedef u32 color;

struct vert {
    u32 grado;       //numero de grado del vertice 
    color color;     //numero del color representado en el vertice 
    u32 *vecinos;      //arreglo de vecinos de vert  
};

struct GrafoSt {
    u32 total_vertices;     //cantidad total de vertices en el grafo
    u32 total_lados;        //cantidad total de lados en el grafo
    u32 deltaGraf;          //grado maximo del grafo 
    struct vert *vertices_array;      //arreglo que contiene struct vert 
};



#endif