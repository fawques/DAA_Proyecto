/* 
 * File:   Arista.cpp
 * Author: victor
 * 
 * Created on 10 de diciembre de 2011, 20:38
 */

#include "../include/Arista.h"
#include "../include/Vertice.h"

Arista::Arista()
{
    inicio = NULL;
    final = NULL;
    peso = 0;
    idfinal = 0;
    idinicio = 0;
}

Arista::Arista(Vertice* origen ,Vertice* destino ,int pes):inicio(origen), final(destino), peso(pes) {
    idinicio = inicio->getID();
    idfinal = final->getID();
    
    inicio->anadirArista(*this);
    final->anadirArista(*this);
    

}

Arista::Arista(const Arista& orig) {
    inicio = orig.inicio;
    final = orig.final;
    peso = orig.peso;
    idinicio = orig.idinicio;
    idfinal = orig.idfinal;
}

Arista::~Arista() {
    inicio = NULL;
    final = NULL;
    peso = 0;
    idinicio = 0;
    idfinal = 0;
}

