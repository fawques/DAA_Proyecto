/* 
 * File:   Vertice.cpp
 * Author: victor
 * 
 * Created on 10 de diciembre de 2011, 20:34
 */

#include "../include/Vertice.h"
#include "../include/Arista.h"

Vertice::Vertice() {
    visitado = false;
    grado = 0;
    aristas = NULL;
    id = -1;
}

Vertice::Vertice(int nid) {
    visitado = false;
    grado = 0;
    aristas = NULL;
    id = nid;
}

Vertice::Vertice(const Vertice& orig) {
    visitado = orig.visitado;
    grado = orig.grado;
    id = orig.id;
    aristas = NULL;
        
    // TODO: Decidir si la copia debe copiar punteros a aristas o hacer copias de aristas
}

Vertice::~Vertice() {
    visitado = false;
    grado = 0;
    id = 0;
    delete [] aristas;
    aristas = NULL;
}

//void Vertice::aumentarGrado()
//{
//    grado++;
//}
//
//void Vertice::aumentarGrado(int n)
//{
//    grado += n;
//}

void Vertice::marcarVisitado()
{
    visitado = true;
}

bool Vertice::esVisitado()
{
    return visitado;
}

int Vertice::getGrado()
{
    return grado;
}

void Vertice::anadirArista(Arista ar)
{
    grado++;
    if(aristas == NULL)
    {
        aristas = new Arista[1];
        aristas[0] = ar;
    }
    else
    {
        Arista* aux = new Arista[grado];
        for(int i = 0; i < grado-1; i++)
        {
            aux[i] = aristas[i];
        }
        aux[grado-1] = ar;
        delete [] aristas;
        aristas = aux;
        aux = NULL;
    }
}

Arista* Vertice::getAristas()
{
    return aristas;
}

