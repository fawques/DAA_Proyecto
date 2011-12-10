/* 
 * File:   Arista.h
 * Author: victor
 *
 * Created on 10 de diciembre de 2011, 20:38
 */

#ifndef ARISTA_H
#define	ARISTA_H

#include "Vertice.h"

class Arista {
public:
    Arista(Vertice,Vertice,int);
    Arista(const Arista& orig);
    virtual ~Arista();
    
    Vertice getInicio();
    Vertice getFinal();
    int getPeso();
    bool esSeleccionada();
private:
    Vertice inicio;
    Vertice final;
    int peso;
    bool seleccionada;
    
};

#endif	/* ARISTA_H */

