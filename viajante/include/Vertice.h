/* 
 * File:   Vertice.h
 * Author: victor
 *
 * Created on 10 de diciembre de 2011, 20:34
 */



#ifndef VERTICE_H
#define	VERTICE_H


#include <iostream>
#include <cstdlib>

#include "Arista.h"

using namespace std;

class Arista;

/* La clase Vertice modela un vértice del grafo. Posee un id y un vector de aristas
 *      que guarda las aristas que parten del vértice.
 */
class Vertice {
public:
    // Constructor por defecto. Crea un vértice con id -1 y vector NULL
    Vertice();

    // Constructor de copia. NO copia el vector de aristas, lo deja a NULL
    Vertice(const Vertice& orig);
    
    // Destructor
    virtual ~Vertice();
    
    int getGrado();
    int getID(){
        return id;
    }
    
    void setId(int nid)
    {
        id = nid;
    }
    
    // añade una arista al vector, gestionando los límites de tamaño
    void anadirArista(Arista ar);
    
    Arista* getAristas();
    
    
private:
    
    int id;
    int grado;
    Arista* aristas;

};

#endif	/* VERTICE_H */

