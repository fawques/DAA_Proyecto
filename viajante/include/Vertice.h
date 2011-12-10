/* 
 * File:   Vertice.h
 * Author: victor
 *
 * Created on 10 de diciembre de 2011, 20:34
 */

#ifndef VERTICE_H
#define	VERTICE_H

class Vertice {
public:
    Vertice(int);
    Vertice(const Vertice& orig);
    virtual ~Vertice();
    
    int getGrado();
    bool esInicial();
    bool esFinal();
    bool esVisitado();
    
    void marcarVisitado();
    void marcarInicial();
    void marcarFinal();
    
    // aumenta el grado en n
    void aumentarGrado(int n);
    // aumenta el grado en 1
    void aumentarGrado();
    
    
    
private:
    
    bool visitado;
    bool inicial;
    bool final;
    int grado;

};

#endif	/* VERTICE_H */

