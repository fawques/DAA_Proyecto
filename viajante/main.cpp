/* 
 * File:   main.cpp
 * Author: victor
 *
 * Created on 10 de diciembre de 2011, 20:23
 */

#include <iostream>
#include <fstream>
#include <cstdlib>
#include <list>
#include <queue>
#include <vector>
#include <time.h>
#include <climits>
#include <algorithm>

//#include "lib/auxiliar.cpp"
#include "include/Arista.h"
#include "include/Solucion.h"
#include "include/Vertice.h"


//#include "include/Grafo.h"


using namespace std;

/*
 * TODO: Trazar RP1 & RP2 a ver xq son más lentos
 * TODO: Añadir generación gráfica del grafo, con una llamada a system("dot ...")
 */

bool leerFichero(int& opcion, int& numero_nodos, Vertice*& nodos, char* nombre)
{
    bool tiene_aristas = true;
    ifstream fichero(nombre);
    
    if(fichero)
    {
        fichero>>opcion;
        fichero>>numero_nodos;
        
        nodos = new Vertice[numero_nodos];
        
        for(int i = 0; i < numero_nodos; i++)
        {
            nodos[i].setId(i);
        }
        
        for(int i = 0; i < numero_nodos && tiene_aristas; i++)
        {   
            tiene_aristas = false;
            for(int j = 0; j < numero_nodos; j++)
            {   
                int aux;
                fichero>>aux;
                if(i != j && aux != -1){
                    Arista arista_aux(&nodos[i], &nodos[j],aux);
                    tiene_aristas = true;
                }
            }
            if(!tiene_aristas)
                cerr<<"Hay un nodo desconectado. No hay camino posible"<<endl;
        }
        fichero.close();
    }
    return tiene_aristas;
}

int getMediaPesos(Vertice* vertices, int n)
{
    int* media = new int[n];
    for(int i = 0; i < n; i++)
    {
        int aux = 0;
            Arista* aristas = vertices[i].getAristas();

            for(int j = 0; j < vertices[i].getGrado(); j++)
            {
                    aux += aristas[j].getPeso();
            }
            media[i] = aux / vertices[i].getGrado();
    }
    
    int devolver = 0;
    for(int i = 0; i < n; i++)
        devolver += media[i];
    devolver /= n;
    
    return devolver;
}

int getVertice(int id, Vertice* vertices, int cantidad)
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

int pesoTotal(vector<int> solucion, Vertice* vertices, int n)
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

bool existeArista(int vert1, int vert2, Vertice* vertices, int n)
{
    int pos = getVertice(vert1,vertices,n);
    
    if(pos != -1)
    {
        Arista* aristas = vertices[pos].getAristas();

        for(int i = 0; i< vertices[pos].getGrado(); i++)
        {
            if(aristas[i].getIdFinal() == vert2 && aristas[i].getPeso() != -1)
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
int voraz(Vertice* vertices, int n)
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
                    if(aristas[i].getPeso() < mejor_peso && !repetido(solucion,j+1,aristas[i].getIdFinal()))
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

//Solucion seleccionar(priority_queue<Solucion > lista_sols, Vertice* vertices, int n)
//{
//    
//    Solucion optima(n+1);
//    int v_optimo = INT_MAX;
//    
//    list<Solucion >::iterator it = lista_sols.begin();
//    while(it != lista_sols.end())
//    {
//        if(pesoTotal(it->solucion,vertices,n) < v_optimo)
//        {
//            optima = *it;
//            v_optimo = pesoTotal(it->solucion,vertices,n);
//        }
//        
//        it++;
//    }
//    
//    return optima;
//}

int estimarPesoTotal(Solucion sol, Vertice* vertices, int menor)
{
    int peso_total = 0;
    

    for(int j = 0; j < sol.getN(); j++)
    {
        
        if(sol.solucion[j] == -1 /*|| sol.solucion[j+1] == -1*/)
        {
            if(sol.solucion[j] == -1)
                peso_total += menor;
        }
        else
        {
            int pos = getVertice(sol.solucion[j],vertices,sol.getN());
            if(pos != -1)
            {
                Arista* aristas = vertices[pos].getAristas();

                for(int i = 0; i < vertices[pos].getGrado(); i++)
                {
                    // si hay una arista entre los nodos de la solucion
                    if(aristas[i].getIdFinal() == sol.solucion[j+1] && aristas[i].getIdInicio() == sol.solucion[j])
                    {
                        peso_total += aristas[i].getPeso();
                    }
                }
            }
            else
                cerr<<"ERROR!!!!!!"<<endl;
        }
    }
    return peso_total;
}

// Función de poda: suma de los pesos desde el primer vértice hasta el primero que tenga un -1
void viajanteRP2(Solucion& sol, Vertice* vertices, int n, int menor_peso, int v_optimo = INT_MAX)
{
    int nodos_generados = 1;
    int nodos_analizados = 0;
    int nodos_podados = 0;
    
    
    // tomamos como primer vértice el vértice 0.
    sol.solucion[0] = 0;
    sol.solucion[n] = 0;
    int k = 1;
    
    priority_queue<Solucion > lista_nodos_vivos;
    lista_nodos_vivos.push(sol);
    priority_queue<Solucion > lista_soluciones;
    
    // mientras tenemos nodos vivos
    while(!lista_nodos_vivos.empty())
    {
        Solucion nodo_vivo = lista_nodos_vivos.top();
        k = n;
        for(int i = 0; i < n; i++)
            vertices[i].desmarcarVisitado();
        
        for(int i = 0; i < n; i++)
        {
            if(nodo_vivo.solucion[i] == -1)
            {
                k = i;
                break;
            }
            else
            {
                int pos = getVertice(nodo_vivo.solucion[i], vertices, n);
                vertices[pos].marcarVisitado();
            }
        }
       
        
        // si el nodo que hemos extraído es un nodo solución
        if(k == n)
        {
            lista_nodos_vivos.pop();
            Solucion aux = nodo_vivo;
            
            if(existeArista(aux.solucion[n-1],aux.solucion[n],vertices,n) 
                    && estimarPesoTotal(aux,vertices,menor_peso) <= v_optimo )
            {
                aux.setPeso(vertices);
                v_optimo = aux.getPeso();
                lista_soluciones.push(aux);
            }
            
        }
        else if(k < n)
        {
            nodos_analizados++;
            lista_nodos_vivos.pop();
            Solucion aux = nodo_vivo;
            
            for(int i = 0; i < n; i++)
            {
                
                if(!repetido(aux.solucion, k ,i) && existeArista(aux.solucion[k-1], i, vertices, n))
                {
                    aux.solucion[k] = i;
//                    clock_t t1 = clock();
                    
                    if(estimarPesoTotal(aux,vertices,menor_peso) <= v_optimo )
                    {
                        
                        aux.setPeso(vertices);   
                        lista_nodos_vivos.push(aux);

                        nodos_generados++;
//                        lista_nodos_vivos.sort();
                    }
                    else
                        nodos_podados++;
                    
//                    clock_t t2 = clock();
//                    cout<<"Ha tardado: "<<t2-t1<<endl;
                }
                    
                
            }
            
                 
        }
    }
    
    if(!lista_soluciones.empty())
        sol = lista_soluciones.top();
    else
        cerr<<"No hay solución válida"<<endl;
    
    cout<<"Nodos generados: "<<nodos_generados<<endl;
    cout<<"Nodos analizados: "<<nodos_analizados<<endl;
    cout<<"Nodos podados: "<<nodos_podados<<endl;

}

// Función de poda: suma de los pesos desde el primer vértice hasta el primero que tenga un -1
void viajanteRP1(Solucion& sol, Vertice* vertices, int n, int v_optimo = INT_MAX)
{
    int nodos_generados = 1;
    int nodos_analizados = 0;
    int nodos_podados = 0;
    
    // tomamos como primer vértice el vértice 0.
    sol.solucion[0] = 0;
    sol.solucion[n] = 0;
    int k = 1;
    
    priority_queue<Solucion > lista_nodos_vivos;
    lista_nodos_vivos.push(sol);
    priority_queue<Solucion > lista_soluciones;
    
    // mientras tenemos nodos vivos
    while(!lista_nodos_vivos.empty())
    {
        Solucion nodo_vivo = lista_nodos_vivos.top();
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
            lista_nodos_vivos.pop();
            Solucion aux = nodo_vivo;
            if(existeArista(aux.solucion[n-1],aux.solucion[n],vertices,n) && pesoTotal(aux.solucion,vertices,n) <= v_optimo )
            {
                aux.setPeso(vertices);
                v_optimo = aux.getPeso();
                lista_soluciones.push(aux);
            }
        }
        else if(k < n)
        {
            nodos_analizados++;
            lista_nodos_vivos.pop();
            Solucion aux = nodo_vivo;
            for(int i = 0; i < n; i++)
            {
                if(!repetido(aux.solucion, k ,i) && existeArista(aux.solucion[k-1], i, vertices, n))
                {
                    aux.solucion[k] = i;
                    if(pesoTotal(aux.solucion,vertices,n) <= v_optimo )
                    {
                        aux.setPeso(vertices);   
                        lista_nodos_vivos.push(aux);
//                        lista_nodos_vivos.sort();
                        nodos_generados++;
                    }
                    else
                        nodos_podados++;
                }
            }
        }
    }
    
    sol = lista_soluciones.top();
    
    cout<<"Nodos generados: "<<nodos_generados<<endl;
    cout<<"Nodos analizados: "<<nodos_analizados<<endl;
    cout<<"Nodos podados: "<<nodos_podados<<endl;
    
}

void viajanteBT(Solucion& sol, Vertice* vertices, int n)
{
    int nodos_generados = 1;
    int nodos_analizados = 0;
    
    // tomamos como primer vértice el vértice 0.
    sol.solucion[0] = 0;
    sol.solucion[n] = 0;
    int k = 1;
    
    priority_queue<Solucion> lista_nodos_vivos;
    lista_nodos_vivos.push(sol);
    priority_queue<Solucion> lista_soluciones;
    
    // mientras tenemos nodos vivos
    while(!lista_nodos_vivos.empty())
    {
        Solucion nodo_vivo = lista_nodos_vivos.top();
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
            lista_nodos_vivos.pop();
            Solucion aux = nodo_vivo;
            if(existeArista(aux.solucion[n-1],aux.solucion[n],vertices,n))
            {
                lista_soluciones.push(aux);
            }
        }
        else if(k < n)
        {
            nodos_analizados++;
            lista_nodos_vivos.pop();
            Solucion aux = nodo_vivo;
            for(int i = 0; i < n; i++)
            {
                if(!repetido(aux.solucion, k ,i) && existeArista(aux.solucion[k-1], i, vertices, n))
                {
                    aux.solucion[k] = i;
                    aux.setPeso(vertices);  
                    lista_nodos_vivos.push(aux);
                    nodos_generados++;
                }
            }
        }
    }
    
//    sol = seleccionar(lista_soluciones, vertices, n);
    sol = lista_soluciones.top();
    
    cout<<"Nodos generados: "<<nodos_generados<<endl;
    cout<<"Nodos analizados: "<<nodos_analizados<<endl;
    
}

int main(int argc, char** argv) 
{
    if(argc == 2)
    {
        int opcion = -1;
        int n = 0;
        Vertice* entrada = NULL;
        if(leerFichero(opcion,n,entrada, argv[1]))
        {

            Solucion sol(n);
            int v_optimo;
            cout<<"Modo de ejecución "<<opcion<<endl;
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
                case 2: {
                            int menor = getMediaPesos(entrada,n);
                            v_optimo = voraz(entrada,n);
                            if(v_optimo != -1)
                                viajanteRP2(sol,entrada,n, menor, v_optimo);
                            else
                                viajanteRP2(sol,entrada,n, menor);
                            break;
                        }
                default:
                    cerr<<"Opción introducida incorrecta, puede ser 0, 1 o 2"<<endl;
                    return -1;
            }

            if(sol.solucion[0] != -1)
            {
                cout<<"La solución óptima es: ";
                for(int i = 0; i < n+1; i++)
                    cout<<sol.solucion[i]<<" ";
                cout<<" con peso total: "<<pesoTotal(sol.solucion,entrada,n)<<endl;
            }
            else
            {
                cerr<<"No hay solución posible"<<endl;
                return -1;
            }
            
            
//            ofstream dibujar("grafo.dot");
//            dibujar<<
////                system("dot ")
////            crear el grafo en un temporal, llamar a dot y borrar el temporal
            

            delete [] entrada;
        }
        else
            return -1;
    }
    else
    {
        cerr<<"Error de argumentos."<<endl<<"La llamada debe ser ./viajante [fichero de datos]"<<endl;
        return -1;
    }
    
    return 0;
}

