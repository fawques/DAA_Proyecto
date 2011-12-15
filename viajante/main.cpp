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
#include <climits>
#include <algorithm>

//#include "lib/auxiliar.cpp"
#include "include/Arista.h"
#include "include/Solucion.h"
#include "include/Vertice.h"


//#include "include/Grafo.h"


using namespace std;

/*
 * TODO: Arreglar las comprobaciones para que sea dirigido (comprobar)
 * TODO: Usar una priority queue en lugar de una lista
 * TODO: PREGUNTAR: El grafo puede tener varias aristas entre los mismos vértices & distinto peso?
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

int pesoTotal(vector<int> solucion, Vertice vertices[], int n)
{
    int peso_total = 0;
    // sacamos el elemento 0 de la solución.
    

    for(int j = 0; j < n; j++)
    {
        if(solucion[j] == -1 || solucion[j+1] == -1)
            break;
        
        int pos = getVertice(solucion[j],vertices,n);
        if(pos != -1)
        {
            Arista* aristas = vertices[pos].getAristas();

            for(int i = 0; i < vertices[pos].getGrado(); i++)
            {
                // si hay una arista entre los nodos de la solucion
                if(aristas[i].getIdFinal() == solucion[j+1] && aristas[i].getIdInicio() == solucion[j])
                {
                    peso_total += aristas[i].getPeso();
                }
            }
        }
        else
            cerr<<"ERROR!!!!!!"<<endl;
    }
    
    return peso_total;
}

bool existeArista(int vert1, int vert2, Vertice vertices[], int n)
{
    int pos = getVertice(vert1,vertices,n);
    
    if(pos != -1)
    {
        Arista* aristas = vertices[pos].getAristas();

        for(int i = 0; i< vertices[pos].getGrado(); i++)
        {
            if(aristas[i].getIdFinal() == vert2)
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

// elige siempre la arista de menor peso
int voraz(Vertice vertices[], int n)
{
    vector<int> solucion(n+1, -1);
    
    solucion[0] = solucion [n] = 0;
    
    for(int j = 0; j < n; j++)
    {
        if(solucion[j] != -1)
        {
            int pos = getVertice(solucion[j],vertices,n);
            if(pos != -1)
            {
                int mejor_peso= INT_MAX;
                int mejor_arista = -1;
                Arista* aristas = vertices[pos].getAristas();

                for(int i = 0; i < vertices[pos].getGrado(); i++)
                {
                    if(aristas[i].getIdInicio() == solucion[j] && aristas[i].getPeso() < mejor_peso && !repetido(solucion,j+1,aristas[i].getIdFinal()))
                    {
                        mejor_arista = i;
                        mejor_peso = aristas[i].getPeso();
                    }
                }

                if(mejor_arista != -1)
                    solucion[j+1] = aristas[mejor_arista].getIdFinal();
            }
        }
        else
        {
            cerr<<"El algoritmo voraz no ha encontrado solución"<<endl;
            return -1;
        }
    }
    
    cout<<"voraz devuelve: ";
    for(int i = 0; i < n+1; i++)
        cout<<solucion[i]<<" ";
    cout<<" con peso total: "<<pesoTotal(solucion,vertices,n)<<endl;
    
    return pesoTotal(solucion,vertices,n);
}

Solucion seleccionar(list<Solucion > lista_sols, Vertice vertices[], int n)
{
    
    Solucion optima(n+1);
    int v_optimo = INT_MAX;
    
    cout<<"Posibles soluciones: "<<endl;
    list<Solucion >::iterator it = lista_sols.begin();
    while(it != lista_sols.end())
    {
        if(pesoTotal(it->solucion,vertices,n) < v_optimo)
        {
            optima = *it;
            v_optimo = pesoTotal(it->solucion,vertices,n);
        }
        
        for(int i = 0; i < n+1; i++)
            cout<<it->solucion[i]<<" ";
        cout<<" con peso total: "<<pesoTotal(it->solucion,vertices,n)<<endl;
        
        it++;
    }
    
    return optima;
}

// Función de poda: suma de los pesos desde el primer vértice hasta el primero que tenga un -1
void viajanteRP1(Solucion& sol, Vertice vertices[], int n, int v_optimo = INT_MAX)
{
    // tomamos como primer vértice el vértice 0.
    sol.solucion[0] = 0;
    sol.solucion[n] = 0;
    int k = 1;
    
    list<Solucion > lista_nodos_vivos;
    lista_nodos_vivos.push_back(sol);
    list<Solucion > lista_soluciones;
    
    // mientras tenemos nodos vivos
    while(!lista_nodos_vivos.empty())
    {
        Solucion nodo_vivo = lista_nodos_vivos.front();
        k = n;
        for(int i = 0; i < n; i++)
        {
            if(nodo_vivo.solucion[i] == -1)
            {
                k = i;
                break;
            }
        }
        
        // si el nodo que hemos extraído es un nodo solución
        if(k == n)
        {
            lista_nodos_vivos.pop_front();
            Solucion aux = nodo_vivo;
            if(existeArista(aux.solucion[n-1],aux.solucion[n],vertices,n))
                lista_soluciones.push_back(aux);
        }
        else if(k < n)
        {
            
            lista_nodos_vivos.pop_front();
            Solucion aux = nodo_vivo;
            for(int i = 0; i < n; i++)
            {
                if(!repetido(aux.solucion, k ,i) && existeArista(aux.solucion[k-1], i, vertices, n))
                {
                    aux.solucion[k] = i;
                    if(pesoTotal(aux.solucion,vertices,n) <= v_optimo )
                        lista_nodos_vivos.push_back(aux);
                }
            }
        }
    }
    
    sol = seleccionar(lista_soluciones, vertices, n);

}

void viajanteBT(Solucion& sol, Vertice vertices[], int n)
{
    // tomamos como primer vértice el vértice 0.
    sol.solucion[0] = 0;
    sol.solucion[n] = 0;
    int k = 1;
    
    list<Solucion> lista_nodos_vivos;
    lista_nodos_vivos.push_back(sol);
    list<Solucion> lista_soluciones;
    
    // mientras tenemos nodos vivos
    while(!lista_nodos_vivos.empty())
    {
        Solucion nodo_vivo = lista_nodos_vivos.front();
        k = n;
        for(int i = 0; i < n; i++)
        {
            if(nodo_vivo.solucion[i] == -1)
            {
                k = i;
                break;
            }
        }
        
        // si el nodo que hemos extraído es un nodo solución
        if(k == n)
        {
            lista_nodos_vivos.pop_front();
            Solucion aux = nodo_vivo;
            if(existeArista(aux.solucion[n-1],aux.solucion[n],vertices,n))
            {
                lista_soluciones.push_back(aux);
            }
        }
        else if(k < n)
        {
            
            lista_nodos_vivos.pop_front();
            Solucion aux = nodo_vivo;
            for(int i = 0; i < n; i++)
            {
                if(!repetido(aux.solucion, k ,i) && existeArista(aux.solucion[k-1], i, vertices, n))
                {
                    aux.solucion[k] = i;
                    lista_nodos_vivos.push_back(aux);
                }
            }
        }
    }
    
    sol = seleccionar(lista_soluciones, vertices, n);
    
}

int main(int argc, char** argv) 
{
    int opcion = 1;
    
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
    
    Arista a1i(&entrada[0],&entrada[1],1);
    Arista a1v(&entrada[1],&entrada[0],2);
//    Arista a2i(&entrada[1],&entrada[2],1);
//    Arista a2v(&entrada[2],&entrada[1],2);
    Arista a3v(&entrada[3],&entrada[2],2);
    Arista a3i(&entrada[2],&entrada[3],1);
//    Arista a4i(&entrada[3],&entrada[4],1);
//    Arista a4v(&entrada[4],&entrada[3],2);
//    Arista a5v(&entrada[0],&entrada[4],2);
    Arista a5i(&entrada[4],&entrada[0],1);
    Arista a6i(&entrada[0],&entrada[2],1);
    Arista a6v(&entrada[2],&entrada[0],2);
    Arista a7v(&entrada[0],&entrada[3],2);
    Arista a7i(&entrada[3],&entrada[0],2);
//    Arista a8i(&entrada[4],&entrada[2],2);
    Arista a8v(&entrada[2],&entrada[4],2);
    Arista a9v(&entrada[4],&entrada[1],2);
    Arista a9i(&entrada[1],&entrada[4],2);
    Arista a10i(&entrada[1],&entrada[3],2);
//    Arista a10v(&entrada[3],&entrada[1],2);
    
    
    
    Solucion sol(n);
    int v_optimo;
    switch (opcion)
    {
        case 0: viajanteBT(sol, entrada, n);
                break;
        case 1: v_optimo = voraz(entrada,n);
                if(v_optimo != -1)
                    viajanteRP1(sol,entrada,n, v_optimo);
                else
                    viajanteRP1(sol,entrada,n);
                break;
        case 2: v_optimo = voraz(entrada,n);
//                if(v_optimo != -1)
//                    viajanteRP2(solucion,entrada,n, v_optimo);
//                else
//                    viajanteRP2(solucion,entrada,n);
                break;
        default:
            cerr<<"Opción introducida incorrecta, puede ser 0, 1 o 2"<<endl;
    }
    
    cout<<"La solución óptima es: ";
    for(int i = 0; i < n+1; i++)
        cout<<sol.solucion[i]<<" ";
    cout<<" con peso total: "<<pesoTotal(sol.solucion,entrada,n)<<endl;
    
    
    return 0;
}

