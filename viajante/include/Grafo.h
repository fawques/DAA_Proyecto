/* 
 * File:   Grafo.h
 * Author: victor
 *
 * Created on 12 de diciembre de 2011, 15:39
 */

#ifndef GRAFO_H
#define	GRAFO_H

#include <list>
#include "Vertice.h"
#include "Arista.h"

using namespace std;

class Grafo {
public:
    Grafo();
    Grafo(const Grafo& orig);
    virtual ~Grafo();
    
    void anadirVertice(Vertice ver);
    void anadirArista(int origen, int destino, int peso);
    
    
private:
    list<Vertice> vertices;
    int nvertices;

};

#endif	/* GRAFO_H */

