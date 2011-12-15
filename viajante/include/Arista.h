/* 
 * File:   Arista.h
 * Author: victor
 *
 * Created on 10 de diciembre de 2011, 20:38
 */

#ifndef ARISTA_H
#define	ARISTA_H

class Vertice;

class Arista {
public:
    Arista();
    Arista(Vertice*,Vertice*,int);
    Arista(const Arista& orig);
    virtual ~Arista();
    
    Vertice* getInicio(){
        return inicio;
    }
    Vertice* getFinal(){
        return final;
    }
    int getPeso(){
        return peso;
    }
    int getIdInicio(){
        return idinicio;
    }
    int getIdFinal(){
        return idfinal;
    }
    
private:
    Vertice* inicio;
    Vertice* final;
    int idinicio;
    int idfinal;
    int peso;
    
};

#endif	/* ARISTA_H */

