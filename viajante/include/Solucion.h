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

/* La clase Solucion es un envoltorio sobre el contenedor de STL vector.
 * Esto permite incluirlo en una priority queue sin problemas.
 * Esta clase guarda un vector de enteros con los vértices seleccionados. Se 
 *      inicializan a -1
 */
class Solucion {
public:
    // Constructor con un tamaño. Crea un vector con tamaño num+1 e 
//        inicializa todos los elementos a -1
    Solucion(int num);
    
    // Constructor de copia
    Solucion(const Solucion& orig);
    
    // Destructor
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
    
    // Función similar a pesoTotal en main. Calcula el peso de la solución.
    void setPeso(Vertice* vertices);
    
    /* Función utilizada para ordenar en la priority_queue. Devuelve el equivalente 
     * a lo que debería ser un operator>. Utiliza el peso para comparar.
     */
    bool operator<(const Solucion& sol) const;
    
    vector <int> solucion;
private:
    int peso;
    int n;
};

#endif	/* SOLUCION_H */

