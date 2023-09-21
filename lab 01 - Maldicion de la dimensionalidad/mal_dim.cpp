#include <iostream>
#include <vector>
#include <cmath>
#include <random>
#include <fstream>

using namespace std;

//funcion para generar puntos aleatorios en una dimension dada
vector<vector<double>> generarPuntos(int dim, int numPuntos) {
    random_device rd;   	//generador de números aleatorios
    mt19937 gen(rd());		// motor
    uniform_real_distribution<> dis(0.0, 1.0);  //rang

	// vector para almacenar ptos generados
    vector<vector<double>> puntos(numPuntos, vector<double>(dim));
	
	// generar num aleatorios en cada dimension
    for (int i = 0; i < numPuntos; i++) {
        for (int j = 0; j < dim; j++) {
            puntos[i][j] = dis(gen);  // generar un valor aleatorio en 
    }									// el rango

    return puntos;
}

//funcion para calcular distancias euclidianas
vector<vector<double>> calcularDistancias(const vector<vector<double>>& puntos) {
    int numPuntos = puntos.size();  // numero de ptos genreados
    int dim = puntos[0].size();		// dimension de cada pto

	// matriz para almacenar distancias entre los pares de ptos
    vector<vector<double>> distancias(numPuntos, vector<double>(numPuntos, 0.0));
	
	// calcular distancia euclediana
    for (int i = 0; i < numPuntos; i++) {
        for (int j = i + 1; j < numPuntos; j++) {
            double distancia = 0.0;
            for (int k = 0; k < dim; k++) {
                double diferencia = puntos[i][k] - puntos[j][k];
                distancia += diferencia * diferencia;
            }
            distancia = sqrt(distancia);
            distancias[i][j] = distancia;
            distancias[j][i] = distancia;
        }
    }

    return distancias;
}

int main() {
    vector<int> dimensiones = {10, 50, 100, 500, 1000, 2000, 5000};

	// para cada dimension en la lista
    for (int dim : dimensiones) {
        int numPuntos = 100; // num de ptos aleatorios a generar
        
        // generar ptos aleatorios
        vector<vector<double>> puntos = generarPuntos(dim, numPuntos);  
        // calcular distancias
		vector<vector<double>> distancias = calcularDistancias(puntos);

        //crear un archivo de texto para almacenar las distancias
        string nombreArchivo = "distancias_dim_" + to_string(dim) + ".txt";
        ofstream archivoSalida(nombreArchivo);
		
		
		// guardar distancias en el archivo txt
        for (int i = 0; i < numPuntos; i++) {
            for (int j = 0; j < numPuntos; j++) {
            	// escribir distancis
                archivoSalida << distancias[i][j] << " "; 
            }
            archivoSalida << endl; // salto de linea
        }

        archivoSalida.close();
    }

    return 0;
}


