/* 
 * File:   Vertice.h
 * Author: victor
 *
 * Created on 10 de diciembre de 2011, 20:34
 */



#ifndef VERTICE_H
#define	VERTICE_H

//#include "Arista.h"
#include <iostream>
#include <cstdlib>
#include <cstdio>

using namespace std;

class Arista;

class Vertice {
public:
    Vertice();
    Vertice(int id);
    Vertice(const Vertice& orig);
    virtual ~Vertice();
    
    int getGrado();
    int getID(){
        return id;
    }
    
    void setId(int nid)
    {
        id = nid;
    }
//    bool esInicial();
//    bool esFinal();
    bool esVisitado();
    
    void marcarVisitado();
//    void marcarInicial();
//    void marcarFinal();
    
//     aumenta el grado en n
//    void aumentarGrado(int n);
//     aumenta el grado en 1
//    void aumentarGrado();
    
    void anadirArista(Arista ar);
    
    Arista* getAristas();
    
    
private:
    
    int id;
    bool visitado;
//    bool inicial;
//    bool final;
    int grado;
    Arista* aristas;

};

#endif	/* VERTICE_H */

