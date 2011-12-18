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
    // Constructor por defecto
    Arista();
    
    // Constructor sobrecargado. Llama a anadirArista del vértice origen
    Arista(Vertice*,Vertice*,int);
    
    // Constructor de copia. Copia los punteros, no el contenido
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

