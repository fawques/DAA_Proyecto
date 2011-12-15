# build
build: Arista.o Vertice.o Solucion.o main.cpp
	g++ -g -Wall Arista.o Vertice.o Solucion.o main.cpp -o viajante

# clases
Arista.o: lib/Arista.cpp include/Arista.h
	g++ -g -Wall -Iinclude -c lib/Arista.cpp
Vertice.o: lib/Vertice.cpp include/Vertice.h
	g++ -g -Wall -Iinclude -c lib/Vertice.cpp
Grafo.o: lib/Grafo.cpp include/Grafo.h
	g++ -g -Wall -Iinclude -c lib/Grafo.cpp
Solucion.o: lib/Solucion.cpp include/Solucion.h
	g++ -g -Wall -Iinclude -c lib/Solucion.cpp





# clean
clean: 
	rm -f Grafo.o Arista.o Vertice.o Solucion.o viajante


# all
all: 
