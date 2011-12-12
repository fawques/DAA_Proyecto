/* 
 * File:   Grafo.cpp
 * Author: victor
 * 
 * Created on 12 de diciembre de 2011, 15:39
 */

#include "../include/Grafo.h"

Grafo::Grafo() {
    nvertices = 0;
}

Grafo::Grafo(const Grafo& orig) {
}

Grafo::~Grafo() {
    nvertices = 0;
    vertices.clear();
}

void Grafo::anadirVertice(Vertice ver)
{
    nvertices++;
    vertices.push_back(ver);
}

void Grafo::anadirArista(int origen, int destino, int peso)
{
    bool encontrado1 = false;
    bool encontrado2 = false;
    
    list<Vertice>::iterator it = vertices.begin();
    list<Vertice>::iterator v1;
    list<Vertice>::iterator v2;
    
    while((!encontrado1 || !encontrado2) && it != vertices.end())
    {
        if(origen == it->getID())
        {
            v1 = it;
            encontrado1 = true;
        }
        else if(destino == it->getID())
        {
            v2 = it;
            encontrado2 = true;
        }
        it++;
    }
    
    if(it != vertices.end() && encontrado1 && encontrado2)
    {

        Arista aux(&(*(v1)),&(*(v2)),peso);

        v1->anadirArista(aux);
        v2->anadirArista(aux);
    }
    else
        cout<<"ALGO HA PETADO!"<<endl;
    
}
