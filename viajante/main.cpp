/* 
 * File:   main.cpp
 * Author: victor
 *
 * Created on 10 de diciembre de 2011, 20:23
 */

#include <fstream>
#include <queue>
#include <climits>

#include "include/Arista.h"
#include "include/Solucion.h"
#include "include/Vertice.h"


using namespace std;

/* Extrae los datos necesarios para la ejecución del programa desde un fichero de texto
 * Modifica los valores de opcion, numero_nodos y nodos
 * Comprueba que el grafo sea conexo. Si no lo es, muestra un error y devuelve falso
 * 
 * Recibe:
 * un entero en el que se guardará la opción de ejecución (0, 1 ó 2)
 * un entero en el que se guardará el número de vértices del grafo
 * un vector de objetos Vertice, que guardará todos los datos de los vértices
 * una cadena con el nombre del archivo de origen
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
                    // al crear la arista nueva, se asigna esta al vértice correspondiente
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

// Recorre las aristas de cada vértice, quedándose con el menor peso entre ellas
int* getMenorPeso(Vertice* vertices, int n)
{
    int* menores = new int[n];
    for(int i = 0; i < n; i++)
    {
        int aux = INT_MAX;
        Arista* aristas = vertices[i].getAristas();

        for(int j = 0; j < vertices[i].getGrado(); j++)
        {
            if(aristas[j].getPeso() < aux)
                aux = aristas[j].getPeso();
        }
        menores[i] = aux;
    }
    
    return menores;
}

// Devuelve la posición en el vector de vértices del elemento id
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

/* Calcula el peso total de una solución. Suma el peso de las aristas elegidas,
 * cuando encuentra un vértice sin seleccionar, termina y devuelve el valor hasta ahí
*/ 
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
    }
    
    return peso_total;
}

// Comprueba que existe una arista entre los vértices con id vert1 y vert2
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

    return false;
}

// Comprueba si ya se encuentra el elemento id en el vector de enteros hasta la posición k
bool repetido(vector<int> vertices, int k, int id)
{
    for (int i = 0; i < k; i++)
    {
        if(vertices[i] == id)
            return true;
    }
    return false;
}

/* Ejecuta un algoritmo voraz, que elige siempre la arista de menor peso, y devuelve su peso
 * Recibe un vector de vértices y un entero con el número de vértices
 */
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
    int peso_total = pesoTotal(solucion,vertices,n);
    cout<<"voraz devuelve: ";
    for(int i = 0; i < n+1; i++)
        cout<<solucion[i]<<" ";
    cout<<" con peso total: "<<peso_total<<endl;
    
    return peso_total;
}

/* Calcula el peso de una solución determinada, estimando el valor de los vértices
 * no seleccionados utilizando el menor peso de las aristas de cada vértice
 * 
 * Recibe:
 * un objeto Solucion, del que estimará el peso
 * un vector de objetos Vertice
 * un vector de enteros con los menores valores de cada vértice
 */
int estimarPesoTotal(Solucion sol, Vertice* vertices, int* menor)
{
    int peso_total = 0;
    

    for(int j = 0; j < sol.getN(); j++)
    {
        
        if(sol.solucion[j] == -1)
        {
            peso_total += menor[j];
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
        }
    }
    return peso_total;
}

/* Crea una representación gráfica del grafo de entrada, marcando en rojo el camino óptimo
 * Requiere del paquete graphviz (concretamente la aplicación dot), y del visualizador eog
 * Mediante dot creará una imagen PNG
 * 
 * Recibe:
 * un objeto solución, que utilizará para remarcarlo en el grafo
 * un vector de objetos Vertices
 * un entero con el número de vértices
 */
void dibujar(Solucion sol, Vertice* entrada, int n)
{
    // Creamos un archivo, que utilizaremos para crear el grafo y después borraremos.
    ofstream dibujo("grafo.dot");
    dibujo<<"digraph A {"<<endl;
    for(int i = 0; i < n; i++)
    {
        int pos = getVertice(sol.solucion[i],entrada,n);
        Arista* aristas = entrada[pos].getAristas();

        for(int j = 0; j < entrada[pos].getGrado(); j++)
        {
            dibujo<<aristas[j].getIdInicio()<<" -> "<<aristas[j].getIdFinal()<<" [label=\"";
            if(aristas[j].getIdInicio() == sol.solucion[i] && aristas[j].getIdFinal() == sol.solucion[i+1])
            {
                dibujo<<aristas[j].getPeso()<<"\",color=red];"<<endl;
            }
            else
                dibujo<<aristas[j].getPeso()<<"\"];"<<endl;
        }           
    }
    dibujo<<"}"<<endl;
    // Borramos grafo.png (por si había alguno generado anteriormente) y generamos el nuevo.
    system("rm grafo.png;dot grafo.dot -o grafo.png -Tpng -Grankdir=LR;rm grafo.dot;eog grafo.png");
    cout<<"======================="<<endl<<"la representación gráfica está guardada en 'grafo.png'"<<endl;

}

/* Ejecuta ramificación y poda, utilizando como función de poda la estimación de 
 *      los pesos. Se suma desde el primer vértice hasta el primero que tenga un -1
 *      y a partir de ahí se estima el resto de pesos con el peso mínimo de cada vértice
 * 
 * Recibe:
 * un objeto Solucion, inicializado a -1, que se modificará cuando encuentre una solución.
 * un array de objetos Vertice
 * un entero con la cantidad de nodos
 * un vector de enteros con los pesos mínimos de cada vértice
 * un entero con el valor obtenido por el algoritmo voraz. Si el voraz no ha 
 *      obtenido ningún resultado, se inicializa al máximo entero.
 *      Este valor se utiliza para comparar con los resultados de la función de poda.
 */
void viajanteRP2(Solucion& sol, Vertice* vertices, int n, int* menor_peso, int v_optimo = INT_MAX)
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
        // asignamos K al primer índice que no esté utilizado todavía (valor -1)
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
            
            if(existeArista(aux.solucion[n-1],aux.solucion[n],vertices,n) 
                    && estimarPesoTotal(aux,vertices,menor_peso) <= v_optimo )
            {
                aux.setPeso(vertices);
                v_optimo = aux.getPeso();
                lista_soluciones.push(aux);
                break;
            }
            
        }
        else // si k es < n
        {
            nodos_analizados++;
            lista_nodos_vivos.pop();
            Solucion aux = nodo_vivo;
            
            for(int i = 0; i < n; i++)
            {
                
                if(!repetido(aux.solucion, k ,i) && existeArista(aux.solucion[k-1], i, vertices, n))
                {
                    aux.solucion[k] = i;
                    if(estimarPesoTotal(aux,vertices,menor_peso) <= v_optimo )
                    {
                        aux.setPeso(vertices);   
                        lista_nodos_vivos.push(aux);
                        nodos_generados++;
                    }
                    else
                        nodos_podados++;
                }
            }    
        }
    }
    
    if(!lista_soluciones.empty())
    {
        sol = lista_soluciones.top();
        cout<<"Nodos generados: "<<nodos_generados<<endl;
        cout<<"Nodos analizados: "<<nodos_analizados<<endl;
        cout<<"Nodos podados: "<<nodos_podados<<endl;
    }

}

/* Ejecuta ramificación y poda, utilizando como función de poda la suma de 
 *      los pesos desde el primer vértice hasta el primero que tenga un -1
 * 
 * Recibe:
 * un objeto Solucion, inicializado a -1, que se modificará cuando encuentre una solución.
 * un array de objetos Vertice
 * un entero con la cantidad de nodos
 * un entero con el valor obtenido por el algoritmo voraz. Si el voraz no ha 
 *      obtenido ningún resultado, se inicializa al máximo entero.
 *      Este valor se utiliza para comparar con los resultados de la función de poda.
 */
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
        // asignamos K al primer índice que no esté utilizado todavía (valor -1)
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
                break;
            }
        }
        else // si k es < n
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
                        nodos_generados++;
                    }
                    else
                        nodos_podados++;
                }
            }
        }
    }
    
    if(!lista_soluciones.empty())
    {
        sol = lista_soluciones.top();
        cout<<"Nodos generados: "<<nodos_generados<<endl;
        cout<<"Nodos analizados: "<<nodos_analizados<<endl;
        cout<<"Nodos podados: "<<nodos_podados<<endl;
    }
    
}

/* Ejecuta Backtracking sin función de cota.
 * 
 * Recibe:
 * un objeto Solucion, inicializado a -1, que modificará cuando encuentre una solución.
 * un array de objetos Vertice
 * un entero con la cantidad de nodos
 */
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
        // asignamos K al primer índice que no esté utilizado todavía (valor -1)
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
        else // si k es < n
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
    
    if(!lista_soluciones.empty())
    {
        sol = lista_soluciones.top();
        cout<<"Nodos generados: "<<nodos_generados<<endl;
        cout<<"Nodos analizados: "<<nodos_analizados<<endl;
    }
    
}

int main(int argc, char** argv) 
{
    if(argc == 2)
    {
        int opcion = -1;
        int n = 0;
        Vertice* entrada = NULL;
        
        // leerFichero rellenará los valores de opcion, n y entrada con lo que extraiga del fichero argv[1]
        if(leerFichero(opcion,n,entrada, argv[1]))
        {

            Solucion sol(n);
            int v_optimo;
            cout<<"Modo de ejecución "<<opcion<<endl;
            switch (opcion)
            {
                case 0: // Ejecutamos backtracking sin función de poda
                        viajanteBT(sol, entrada, n);
                        break;
                case 1: // Ejecutamos ramificación y poda con la primera función de poda (suma del peso acumulado)
                        v_optimo = voraz(entrada,n);
                        if(v_optimo != -1)
                            viajanteRP1(sol,entrada,n, v_optimo);
                        else
                            viajanteRP1(sol,entrada,n);
                        break;
                case 2: { // Ejecutamos ramificación y poda con la segunda función de poda (estimación con el menor peso de cada vértice)
                            int* menor = getMenorPeso(entrada,n);
                            v_optimo = voraz(entrada,n);
                            if(v_optimo != -1)
                                viajanteRP2(sol,entrada,n, menor, v_optimo);
                            else
                                viajanteRP2(sol,entrada,n, menor);
                            delete [] menor;
                            break;
                        }
                default:
                        cerr<<"Opción introducida incorrecta, puede ser 0, 1 o 2"<<endl;
                        return -1;
            }

            if(sol.solucion[1] != -1)
            {
                cout<<"La solución óptima es: ";
                for(int i = 0; i < n+1; i++)
                    cout<<sol.solucion[i]<<" ";
                cout<<" con peso total: "<<pesoTotal(sol.solucion,entrada,n)<<endl;
            }
            else
            {
                cerr<<"No se ha encontrado solución"<<endl;
                return -1;
            }
            
//            dibujar(sol,entrada,n);
            
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

