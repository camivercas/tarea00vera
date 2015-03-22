/*
Autores: Nelson Cariqueo 
		 Diego Higuera
		 Camila Vera

Versión: 1.1

Fecha: 17 de marzo de 2015

*/

#include <iostream>
#include <cstdlib>
#include <fstream>
#include <string.h>
#include <time.h>
using namespace std;

void ordenar(int q[]){ //Método de ordenamiento BubleSort
	int i;
	int j;
	int aux;
	for(i=1; i<14; i++){
		for(j=0;j<(14-i);j++){
			if(q[j] > q[j+1]){
				aux = q[j];
				q[j] = q[j+1];
				q[j+1] = aux;
			}
		}
	}
}

int esta(int numero, int q[]){ //Función que sirve para verificar si un número en específico
	int i;					   //se encuentra en el arreglo.
	for(i = 0; i<14; i++){
		if(q[i] == numero)
			return 1;
	}
	return 0;
}

void llenarVector(int qno[]){ //Función que llena el vector "qno" con número aleatorios
	srand(time(NULL)*123456789);
	int i;
	int numero;
	int isIn;
	for(i=0;i<14;i++){
		do{
			numero = rand()%25+1;
			isIn = esta(numero, qno);
			if(isIn != 1)
				qno[i] = numero;
		}while(isIn == 1);
	}
}

string tiempo(){ //Funcion para obtener el tiempo en formato ISO YY:MM:DD HH:MM:SS
	time_t tiempo;
	struct tm *ts;
	char formatoISO[80];

	tiempo = time(0);

	ts = localtime(&tiempo);
	strftime(formatoISO, sizeof(formatoISO), "%Y-%m-%d %H:%M:%S", ts);
	return formatoISO;
}

void Qno(){ //Procedimiento que crea el archivo con extensión .csv que almacena los números guardados en el arreglo lotería.
	int i;
	int loteria[14];

	string formatoISO = tiempo();

	llenarVector(loteria);
	ordenar(loteria);

	ofstream archivo_salida;

	string nombre_archivo = "Qno.csv";

	archivo_salida.open(nombre_archivo.c_str(),ios::app);

	if(archivo_salida.fail())
		cout << "El archivo no se creo correctamente" << endl;
	else{
		cout << formatoISO;
		archivo_salida << formatoISO << ";";
	
		for(i=0;i<14;i++){
			archivo_salida << loteria[i] << ";";
			cout << " ;" << loteria[i];
		}
	
		cout << endl;
		archivo_salida << endl;

		archivo_salida.close();
	}
}

void Info(){ 
	string ptr = __DATE__; //Macro que muestra la fecha de compilación.
	string ptr2 = __TIME__; //Macro que muestra la hora de compilación (añadido para mostrar el momento exacto de compilación).
	cout << "Integrantes " << endl
		 << "\n\tNelson Cariqueo Rojas" << endl
		 << "\tDiego Higuera Fernandez" << endl
		 << "\tCamila Vera Castañeda" << endl
		 << "\nFecha de compilacion " << ptr << " " << ptr2 << endl
		 << " " << endl;
}

int main(int argc, char *argv[]){
	char opcion;
	int j = 0;

	for (j=0;j<argc;j++)
	{
   		if(strcmp(argv[j],"-v")==0) 
   			opcion = 'v';
   		else{
   			if(strcmp(argv[j],"-g")==0) 
   				opcion = 'g';
   		}
	}

	switch (opcion)
	{
		case 'g': 
				Qno();
				break;

		case 'v': 
				Info();
				break;

		default: 
				cout << "No ingreso una opcion valida. Por favor ingrese nuevamente." << endl;
	}
	
}
