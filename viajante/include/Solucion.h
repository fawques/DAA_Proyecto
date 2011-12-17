/* 
 * File:   Solucion.h
 * Author: victor
 *
 * Created on 15 de diciembre de 2011, 15:43
 */

#ifndef SOLUCION_H
#define	SOLUCION_H

#include <vector>
#include "Vertice.h"
#include "Arista.h"

using namespace std;

class Solucion {
public:
    Solucion(int num);
    Solucion(const Solucion& orig);
    
    virtual ~Solucion();
    
    int getN(){
        return n;
    }
    void setN(int num){
        n = num;
    }
    
    int getPeso(){
        return peso;
    }
    
    void setPeso(Vertice* vertices);
    
    bool operator<(const Solucion& sol) const;
    
    vector <int> solucion;
private:
    int peso;
    int n;
};

#endif	/* SOLUCION_H */

