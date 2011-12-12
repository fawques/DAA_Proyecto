/* 
 * File:   main.cpp
 * Author: victor
 *
 * Created on 10 de diciembre de 2011, 20:23
 */

#include <iostream>
#include <cstdlib>
#include <list>
#include <vector>

#include "include/Arista.h"
#include "include/Vertice.h"
//#include "include/Grafo.h"


using namespace std;

/*
 * TODO: PREGUNTAR: El grafo es no dirigido? 
 * TODO: Usar una priority queue en lugar de una lista
 * TODO: PREGUNTAR: El grafo puede tener varias aristas entre los mismos vértices & distinto peso?
 * TODO: Insertar código de decisión entre 0,1,2
 * TODO: Leer desde el fichero
 * TODO: Inventarse 2 funciones de poda (suma hasta el momento & ¿mediana?, ¿media? ...)
 */

int getVertice(int id, Vertice vertices[], int cantidad)
{
    bool encontrado = false;
    int i;
    for(i = 0; i < cantidad && !encontrado; i++)
    {
        if(vertices[i].getID() == id)
        {
            encontrado = true;
            break;
        }
    }
    
    if(!encontrado)
        i = -1;
    
    return i;
}

bool existeArista(int vert1, int vert2, Vertice vertices[], int n)
{
    int pos = getVertice(vert1,vertices,n);
    
    if(pos != -1)
    {
        Arista* aristas = vertices[pos].getAristas();

        for(int i = 0; i< vertices[pos].getGrado(); i++)
        {
            if(aristas[i].getIdFinal() == vert2 || aristas[i].getIdInicio() == vert2 )
                return true;
        }
    }
    else
        cout<<"ERROR!!!!"<<endl;
    return false;
}

bool repetido(vector<int> vertices, int k, int id)
{
    for (int i = 0; i < k; i++)
    {
        if(vertices[i] == id)
            return true;
    }
    return false;
}

void viajante(vector<int> solucion, Vertice vertices[], int n)
{
    // tomamos como primer vértice el vértice 1.
    solucion[0] = 0;
    solucion[n] = 0;
    int k = 1;
    
    list<vector<int> > lista_nodos_vivos;
    lista_nodos_vivos.push_back(solucion);
    list<vector<int> > lista_soluciones;
    
    // mientras tenemos nodos vivos
    while(!lista_nodos_vivos.empty())
    {
        vector<int> nodo_vivo = lista_nodos_vivos.front();
        k = -1;
        for(int i = 0; i < n; i++)
        {
            if(nodo_vivo[i] == -1)
            {
                k = i;
                break;
            }
        }
        
        if(k == -1)
        {
            lista_nodos_vivos.pop_front();
            vector<int> aux = nodo_vivo;
            if(existeArista(aux[n-1],aux[n],vertices,n))
                lista_soluciones.push_back(aux);
            k = 99; // TODO: poner algo más real
        }
            
        
        
        
        if(k < n)
        {
            
            lista_nodos_vivos.pop_front();
            vector<int> aux = nodo_vivo;
            for(int i = 0; i < n; i++)
            {
                if(!repetido(aux, k ,i) && existeArista(aux[k-1], i, vertices, n))
                {
                    aux[k] = i;
                    lista_nodos_vivos.push_back(aux);
                }
            }
        }
//        else
//        {
//            for(int i = 0; i < n; i++)
//            {
//                cout<<lista_nodos_vivos.front()[i]<<endl;
//            }
//            cout<<endl;
//            lista_nodos_vivos.pop_front();
//        }
    }
    
    // endbucle
    
    list<vector<int> >::iterator it = lista_soluciones.begin();
    while(it != lista_soluciones.end())
    {
        for(int i = 0; i < n+1; i++)
        {
            cout<<(*it)[i]<<" ";
        }
        cout<<endl;
        it++;
    }
    
    // BACKTRACKING
    //Si Cumple restricciones: se añade xi a la solución y se pasa a xi+1
    //Si no cumple restricciones: se prueba otra posibilidad para xi
    //Si No cumple restricciones y no hay más posibilidades con xi : se replantea la decisión anterior xi-1

    cout<<"aquí es donde hago el problema del viajante"<<endl;
}

int main(int argc, char** argv) 
{
//    list<Vertice> v_grafo;
//    list<Arista> a_grafo;
//    list<Vertice> solucion;
    
    
    // Creamos el grafo completo con 4 vértices y 6 aristas
    
//    ·___·
//    |\ /|
//    | X |
//    |/ \|
//    ·___·
    
//    Grafo g;
    int n = 5;
    
    Vertice entrada[n];
    for(int i = 0; i < n; i++)
    {
        entrada[i].setId(i);
    }
    
//    g.anadirVertice(v1);
//    g.anadirVertice(v2);
//    g.anadirVertice(v3);
//    g.anadirVertice(v4);
//    
//    g.anadirArista(1,2,1);
//    g.anadirArista(2,3,2);
//    g.anadirArista(3,4,3);
//    g.anadirArista(4,1,4);
//    g.anadirArista(2,4,5);
//    g.anadirArista(1,3,6);
    
    Arista a1(&entrada[0],&entrada[1],1);
    Arista a2(&entrada[1],&entrada[2],2);
    Arista a3(&entrada[2],&entrada[3],3);
    Arista a7(&entrada[3],&entrada[4],3);
    Arista a4(&entrada[3],&entrada[0],4);
    Arista a5(&entrada[1],&entrada[3],5);
    Arista a6(&entrada[0],&entrada[2],6);
    Arista a8(&entrada[0],&entrada[4],6);
    Arista a9(&entrada[1],&entrada[4],6);
    
    vector<int> solucion(n+1,-1);
    
    viajante(solucion, entrada, n);
    
    return 0;
}

