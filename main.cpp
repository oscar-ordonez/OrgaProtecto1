#include <iostream>
#include <fstream>
#include <sstream>
#include <cstdlib>
#include <ctime>
#include <string>
#include <string.h>
#include <fstream>
#include <vector>
#include <cstring>




using namespace std;

void convertirPersonas();
void indexarPersonas();
void mostrarPersonas();
int posicionIndice(vector <string>, unsigned long);
void indexarCiudad();
int posicionIndicePrimario(vector<string>, int);
void convertirCiudad();
void mostrarCiudad();
void convertirNumero();
void mostrarNumero();
void indexarNumero();
void agregarPersona();
void agregarNumero();
void agregarCiudad();
void eliminarCiudad( int );
void eliminarPersona(long);
void eliminarNumero(int);

vector<string> llaveCliente;
vector<string> rrnCliente;
vector<string> llaveCiudad;
vector<string> rrnCiudad;
vector<string> llaveNumero;
vector<string> rrnNumero;
const int HeaderSize = sizeof(int) + sizeof(int) + sizeof(bool);


int main(int argc, char* argv[]){
	
	int respuestaContinuar;
	do{
		cout << "Menu" << endl << "1. Pasar Archivos a binario e indexarlos"
			 << endl << "2. Visualizar" << endl << "3. Agregar " << endl 
			 << "4. Eliminar" << endl <<"5. Salir" << endl;
		cin >> respuestaContinuar;

		//Pasar Archivo a binario
		if(respuestaContinuar == 1){
			convertirPersonas();
			cout << "convertirPersonas";
			indexarPersonas();
			cout << endl << "personas indexadas exitosamente" << endl;
			convertirCiudad();
			cout << "convertirCiudad";
			indexarCiudad();
			cout << endl << "ciudades indexadas exitosamente" << endl;
			convertirNumero();
			cout << "convertirNumero";
			indexarNumero();
			cout << endl << "Numero indexadas exitosamente" << endl;
		}
		if(respuestaContinuar == 2){				

			int op = 0;
			cout << endl << "Visualizar \n1. Personas\n2. Ciudades\n3. Numeros" << endl;
			cin >> 	op;
			if(op == 1){
				 mostrarPersonas();
			}
			if(op==2){
				mostrarCiudad();
			}	
			if(op==3){
				mostrarNumero();
			}	
					}

		if(respuestaContinuar == 3){
			int op = 0;
			cout << endl << "Agregar \n1. Personas\n2. Ciudades\n3. Numeros" << endl;
			cin >> 	op;
			if(op == 1){
				 agregarPersona();
			}
			if(op==2){
				agregarCiudad();
			}	
			if(op==3){
				agregarNumero();
			}	

		}

		if(respuestaContinuar == 4){
			int op = 0;
			cout << endl << "Eliminar \n1. Personas\n2. Ciudades\n3. Numeros" << endl;
			cin >> 	op;
			if(op == 1){
				long identidad;
				cout << "Ingrese la identidad de la persona que desea borrar" << endl;
				cin >> identidad;
				 eliminarPersona(identidad);

			if(op==2){
				int id = 0;
				cout << "Ingrese el Id de la ciudad que desea borrar" << endl;
				cin >> id;
				eliminarCiudad(id);
			}	
			if(op==3){
				int num = 0;
				cout << "Ingrese el numero que desea borrar" << endl;
				cin >> num;
				eliminarNumero(num);
			}	

		}

	}
	}while(respuestaContinuar != 5);
	return 0;

}

void convertirPersonas(){
	//archivo texto
	ifstream archivo("personas.txt");
	//archivo binario
	ofstream archivoBinario("personas.bin");
	int rrn = -1;
	bool bandera = 0;
	int recorriendo = 0;
	char terminado;

	archivoBinario.write(reinterpret_cast <char*> (&rrn), sizeof(int));
	archivoBinario.write(reinterpret_cast <char*> (&recorriendo), sizeof(int));
	archivoBinario.write(reinterpret_cast <char*> (&bandera), sizeof(bool));
	cout << "entra" << endl;
	while(true){
		if(archivo.eof()){
			break;
		}
		char id[15];
		char nombre[40];
		char genero[2];
		char idCiudad[6];

		string idString = "";
		string nombreString = "";
		string generoString = "";
		string idCiudadString = "";

		getline(archivo, idString, '@');
		getline(archivo, nombreString, '@');
		getline(archivo, generoString, '@');
		getline(archivo, idCiudadString, '@');

		//identidad
		for (int i = 0; i < 15; ++i) {
			id[i] = idString[i];
		}

		//nombre
		for (int i = 0; i < 40; ++i) {
			nombre[i] = nombreString[i];
		}

		//genero
		for (int i = 0; i < 2; ++i) {
			genero[i] = generoString[i];
		}

		//codigo de la ciudad
		for (int i = 0; i < 6; ++i) {
			idCiudad[i] = idCiudadString[i];
		}

		archivoBinario.write((char*)id,sizeof(id));
		archivoBinario.write((char*)nombre,sizeof(nombre));
		archivoBinario.write((char*)genero,sizeof(genero));
		archivoBinario.write((char*)idCiudad,sizeof(idCiudad));
		
		recorriendo ++;
		archivoBinario.seekp (sizeof(rrn));
  		archivoBinario.write(reinterpret_cast<char*>(&recorriendo), sizeof(recorriendo));
  		archivoBinario.seekp(sizeof(int)*2 + 1 + (recorriendo*63));
	}
	cout << "sale" << endl;
	// Visualizar el contenido
	archivo.close();
	archivoBinario.close();
}

void indexarPersonas(){
	llaveCliente.clear();
	llaveCliente.clear();
	int contador = 0;
	ifstream leerArchivo("personas.bin",ios::binary);
	leerArchivo.seekg(sizeof(int) + sizeof(int) + sizeof(bool));
	cout << "antes del while" << endl;
	while(true){
		stringstream rrn;
		if(leerArchivo.eof()){
			break;
		}

		char id[15];
		char nombre[40];
		char genero[2];
		char IdCiudad[6];
		
		leerArchivo.read((char*)id, sizeof(id));
		leerArchivo.read((char*)nombre, sizeof(nombre));
		leerArchivo.read((char*)genero, sizeof(genero));
		leerArchivo.read((char*)IdCiudad, sizeof(IdCiudad));
		
		bool comparar = false;
		
		for(int i = 0; i < sizeof(id)-1; i++){
			if(id[i] == '*'){
				comparar = true;
				break;
			}
		}

		if(!comparar){
			stringstream cadena;
			for (int i = 0; i < sizeof(id); ++i){
				cadena << id[i];
			}

			rrn << contador;

			unsigned long llave = atol(cadena.str().c_str());
			int posicion = posicionIndice(llaveCliente,llave);
			if (posicion == -1){
				llaveCliente.push_back(cadena.str());
				rrnCliente.push_back( rrn.str());
			}else{
				llaveCliente.insert(llaveCliente.begin() + posicion, cadena.str());
				rrnCliente.insert(rrnCliente.begin() + posicion, rrn.str());
			}
		}
	}
	contador++;
	cout << "despues" << endl;
}

void mostrarPersonas(){
	int rrn=-1;
	int recorriendo = 0;
	int final = 0;
	bool bandera = 0;
	char id[15];
	char nombre[40];
	char genero[2];
	char ciudad[6];
	ifstream readFile("personas.bin",ios::binary);
	readFile.read( reinterpret_cast<char*>(&rrn), sizeof(int) );
	readFile.read( reinterpret_cast<char*>(&recorriendo), sizeof(int) );
	readFile.read( reinterpret_cast<char*>(&bandera), sizeof(bool)  );
	readFile.seekg(sizeof(int)+sizeof(int)+sizeof(bool));
	while(final < recorriendo){
		/*if(readFile.eof())
			break;*/
		readFile.read((char*)id, sizeof(id));
		readFile.read((char*)nombre, sizeof(nombre));
		readFile.read((char*)genero, sizeof(genero));
		readFile.read((char*)ciudad, sizeof(ciudad));
		if( id[0] != '*'){
			cout <<"----------------------------------------------------------------------------"<<endl;
			cout << "Id: " << id << endl;
			cout << "Nombre: " << nombre <<endl; 
			cout << "Genero: " << genero << endl;
			cout << "Id Ciudad: " << ciudad <<endl;
		}
		final++;

	}
	readFile.close();
}

int posicionIndice(vector <string> llaveIndice, unsigned long llave){
	int primero = 0;
	int ultimo = llaveIndice.size()-1;
	int medio;
	bool bandera = false;

	while(true){
		if(primero > ultimo)
			break;
		medio = (primero + ultimo)/2;
		
		if(llave == atol((llaveIndice.at(medio)).c_str())){
			return medio;
		}

		if(llave > atol((llaveIndice.at(medio)).c_str())){
    		if(medio != llaveIndice.size() - 1){
    			if(llave < atol((llaveIndice.at(medio+1)).c_str())){
    				return medio+1;
    			}else{
    				if(bandera && medio == llaveIndice.size()-2)
    					return -1;
    				primero = medio;
    				bandera = true;
    			}
    		}else{
    			if(llave < atol((llaveIndice.at(medio)).c_str())){
    				return medio;
    			}else{
    				return -1;
    			}

    		}
    	}else{
    		if(medio != 0){
    			if(llave > atol((llaveIndice.at(medio-1)).c_str())){
    				return medio;
    			}else{
    				ultimo = medio;
    			}
    		}else{
    			if(llave < atol((llaveIndice.at(medio)).c_str())){
    				return medio;
    			}else{
    				return medio+1;
    			}
    		}
    	}			
	}
	return -1;
}

void indexarCiudad(){
	llaveCiudad.clear();
	rrnCiudad.clear();
	ifstream leer("ciudades.bin",ios::binary);
	leer.seekg(HeaderSize);
	int cont = 0;

 	while(true){
		stringstream rrn ;
		if(leer.eof()){
			break;
		}
		char IdCiudad[4];
		char NameCiudad[40];
		leer.read(reinterpret_cast<char*>(&IdCiudad), sizeof(IdCiudad));
		leer.read(reinterpret_cast<char*>(&NameCiudad), sizeof(NameCiudad));
		bool iguales = false;
		for (int i = 0; i < sizeof(IdCiudad)-1; i++){
			if(IdCiudad[i] == '*'){
				iguales = true;	
				break;			
			}
		}
		if(!iguales){
			stringstream ss;
			for (int i = 0; i < sizeof(IdCiudad); i++){							
				ss<< IdCiudad[i];	
			}
			rrn<< cont;
			int key = atoi(ss.str().c_str());
			int position = posicionIndicePrimario(llaveCiudad
		, key);
			if (position == -1){
				llaveCiudad
		.push_back(ss.str());
				rrnCiudad.push_back(rrn.str());
			}else{
				llaveCiudad
		.insert(llaveCiudad
			.begin() + position, ss.str());
				rrnCiudad.insert(rrnCiudad.begin() + position, rrn.str());
			}

		}
		cont++;

	}
	/*for (int i = 0; i < llaveCiudad.size(); i++)
	{
		cout << "Key: " << llaveCiudad
.at(i) << " RRN: " << rrnCiudad.at(i)<< endl;
	}*/
	leer.close();
	//writeIndexCity();
	//ListIndex("IndexCity.bin");
}
int posicionIndicePrimario(vector<string> indexKey  , int key){
    int minimo = 0;
    int mayor = indexKey.size() - 1;
    int medio;
    bool bandera = false;
    
    while(true){
    	if(minimo > mayor)
    		break;    	
    	medio = (minimo + mayor)/2;
    	if(key == atoi((indexKey.at(medio)).c_str()) )
    		return medio;
    	if(key > atoi((indexKey.at(medio)).c_str())){
    		if(medio != indexKey.size() - 1){
    			if(key < atoi((indexKey.at(medio+1)).c_str())){
    				return medio+1;
    			}else{
    				if(bandera && medio == indexKey.size()-2)
    					return -1;
    				minimo = medio;
    				bandera = true;
    			}
    		}else{
    			if(key < atoi((indexKey.at(medio)).c_str())){
    				return medio;
    			}else{
    				return -1;
    			}

    		}
    	}else{
    		if(medio != 0){
    			if(key > atoi((indexKey.at(medio-1)).c_str())){

    				return medio;
    			}else{
    				mayor = medio;
    			}
    		}else{
    			if(key < atoi((indexKey.at(medio)).c_str())){
    				return medio;
    			}else{
    				return medio+1;
    			}

    		}
    	}
    }
    return -1;
}

void convertirCiudad(){
	ifstream archivo("ciudades.txt");
	ofstream binario("ciudades.bin");
	int rrn=-1, recorrido = 0;
	bool bandera = 0;
	binario.write( reinterpret_cast<char*>(&rrn), sizeof(int) );
	binario.write( reinterpret_cast<char*>(&recorrido), sizeof(int) );
	binario.write( reinterpret_cast<char*>(&bandera), sizeof(bool)  );
	char ultimo;
	while(archivo>>ultimo){
		/*if(archivo.eof())
			break;*/
		char IdCiudad[5];
		char NameCiudad[40];
		string temp = "", temp1 = "";
		getline(archivo, temp, '@');
		getline(archivo, temp1, '@');
		for (int i = 0; i < 5; i++){
			IdCiudad[i] = temp[i];
		}		
		for (int i = 0; i < 40; i++){
			NameCiudad[i] = temp1[i];
		}
		bool CadenaVacia = true;
		for (int i = 0; i < sizeof(IdCiudad); i++)
		{
			if(IdCiudad[i] != '\0' && IdCiudad[i] != ' ')
				CadenaVacia = false;
		}
		if(!CadenaVacia){			
			binario.write((char*)IdCiudad, sizeof(IdCiudad));
			binario.write((char*)NameCiudad, sizeof(NameCiudad));
			recorrido++;
	  		binario.seekp (sizeof(rrn));
	  		binario.write(reinterpret_cast<char*>(&recorrido), sizeof(recorrido));
	  		binario.seekp(sizeof(int)*2 +1 +(recorrido*45));
		}
	}	
	archivo.close();
	binario.close();
	//ListCity();
}

void mostrarCiudad(){
	int rrn=-1, recorrido = 0, final = 0;
	bool bandera = 0;
	char IdCiudad[5];
	char NameCiudad[40];
	ifstream readFile("ciudades.bin",ios::binary);
	readFile.read( reinterpret_cast<char*>(&rrn), sizeof(int) );
	readFile.read( reinterpret_cast<char*>(&recorrido), sizeof(int) );
	readFile.read( reinterpret_cast<char*>(&bandera), sizeof(bool)  );
	readFile.seekg(sizeof(int)+sizeof(int)+sizeof(bool));
	//cout << rrn <<"||"<< recorrido<<"||" << bandera <<endl;
 	while(final < recorrido){

		/*if(readFile.eof())
			break;*/
		char IdCiudad[5];
		char NameCiudad[40];
		readFile.read((char*)IdCiudad, sizeof(IdCiudad));
		readFile.read((char*)NameCiudad, sizeof(NameCiudad));
		if( IdCiudad[0] != '*'){
			cout <<"----------------------------------------------------------------------------"<<endl;
			cout << "Id Ciudad: "<<IdCiudad <<endl;
			cout << "Nombre de la ciudad: " <<NameCiudad<<endl;
		}
		final++;
	}
	readFile.close();
}

void convertirNumero(){
	ifstream archivo("numero.txt");
	ofstream binario("numeros.bin");
	int rrn=-1, recorrido = 0;
	bool bandera = 0;
	binario.write( reinterpret_cast<char*>(&rrn), sizeof(int) );
	binario.write( reinterpret_cast<char*>(&recorrido), sizeof(int) );
	binario.write( reinterpret_cast<char*>(&bandera), sizeof(bool)  );
	char finalArchivo;
	while(archivo>>finalArchivo){
		/*if(archivo.eof())
			break;*/
		char Numero[9];
		char Id[15];
		string temp = "", temp1 = "";
		getline(archivo, temp, '@');
		getline(archivo, temp1, '@');
		for (int i = 0; i < sizeof(Numero); i++){
			Numero[i] = temp[i];
		}		
		for (int i = 0; i < sizeof(Id); i++){
			Id[i] = temp1[i];
		}
		binario.write((char*)Numero, sizeof(Numero));
		binario.write((char*)Id, sizeof(Id));
		recorrido++;
  		binario.seekp (sizeof(rrn));
  		binario.write(reinterpret_cast<char*>(&recorrido), sizeof(recorrido));
  		binario.seekp(sizeof(int)*2 +1 +(recorrido*23));
	}	
	archivo.close();
	binario.close();
	//ListNumber();
}

void mostrarNumero(){
	cout << "entra" << endl;
	int rrn=-1, recorrido = 0,finalArchivo = 0;
	bool bandera = 0;
	char Numero[9];
	char Id[14];
	ifstream leerArchivo("numeros.bin",ios::binary);
	leerArchivo.read( reinterpret_cast<char*>(&rrn), sizeof(int) );
	leerArchivo.read( reinterpret_cast<char*>(&recorrido), sizeof(int) );
	leerArchivo.read( reinterpret_cast<char*>(&bandera), sizeof(bool)  );
	leerArchivo.seekg(sizeof(int)+sizeof(int)+sizeof(bool));
	while(finalArchivo < recorrido){
		/*if(leerArchivo.eof())
			break;*/
		char Numero[9];
		char Id[14];
		leerArchivo.read((char*)Numero, sizeof(Numero));
		leerArchivo.read((char*)Id, sizeof(Id));
		if( Numero[0] != '*'){
			cout <<"----------------------------------------------------------------------------"<<endl;
			cout << "Numero: " << Numero << endl;
			cout << "Id Propietario: " << Id <<endl; 
		}
		finalArchivo++;

	}
	leerArchivo.close();
}

void indexarNumero(){
	llaveNumero.clear();
	rrnNumero.clear();
	ifstream leerArchivo("numeros.bin",ios::binary);
	leerArchivo.seekg(HeaderSize);
	int cont = 0;

 	while(true){
		stringstream rrn ;
		if(leerArchivo.eof())
			break;
		char Numero[9];
		char Id[14];
		leerArchivo.read(reinterpret_cast<char*>(&Numero), sizeof(Numero));
		leerArchivo.read((char*)Id, sizeof(Id));
		bool iguales = false;
		for (int i = 0; i < sizeof(Numero)-1; i++){
			if(Numero[i] == '*'){
				iguales = true;	
				break;			
			}
		}
		if(!iguales){
			stringstream ss;
			for (int i = 0; i < sizeof(Numero); i++){							
				ss<< Numero[i];	
			}
			//cout << ss.str()<<endl;
			rrn<< cont;
			//cout << rrn.str() << "|||"<< endl;
			int key = atoi(ss.str().c_str());
			int position = posicionIndicePrimario(llaveNumero, key);
			if (position == -1){
				llaveNumero.push_back(ss.str());
				rrnNumero.push_back( rrn.str());
			}else{
				llaveNumero.insert(llaveNumero.begin() + position, ss.str());
				rrnNumero.insert(rrnNumero.begin() + position, rrn.str());
			}

		}
		cont++;

	}
	/*for (int i = 0; i < llaveNumero.size(); i++)
	{
		cout << "Key: " << llaveNumero.at(i) << " RRN: " << rrnNumero.at(i)<< endl;
	}	*/
	leerArchivo.close();
	//writeIndexNumber();
}

void agregarPersona(){
	ifstream leerArchivo("personas.bin", ios::binary);
	char IdClient[15];
	char NameClient[40];
	char Gender[2];
	char IdCiudad[6];
	leerArchivo.seekg(0);
	int rrnHeader, recorrido,cont = 0;
	leerArchivo.read(reinterpret_cast<char*>(&rrnHeader), sizeof(int));
	leerArchivo.read(reinterpret_cast<char*>(&recorrido), sizeof(int));
	leerArchivo.seekg(HeaderSize + rrnHeader*( sizeof(IdClient) + sizeof(NameClient) + sizeof(Gender) + sizeof(IdCiudad))+ sizeof(IdClient) );
	leerArchivo.read(reinterpret_cast<char*>(&NameClient), sizeof(NameClient));
	stringstream streamNombre;
	for (int i = 0; i < sizeof(NameClient); i++){
		streamNombre << NameClient[i];
	}
	int nuevaRrn = atoi(streamNombre.str().c_str());
	cout << nuevaRrn << "°|°" << endl;
	leerArchivo.close();
	string leerName = "",leerId = "", leerGender = "",leerCiudad = "";
	if(rrnHeader != -1){
		cout << "Ingrese el Id del cliente: ";
		cin >> leerId;
		stringstream ss;
		for (int i = 0; i < sizeof(IdClient); i++){
			IdClient[i] = leerId[i];
			ss<< leerId[i];
		}
		
		cout << "Ingrese el nombre del cliente: ";
		cin >> leerName;
		for (int i = 0; i < sizeof(NameClient); i++){
			NameClient[i] = leerName[i];
		}

		cout << "Ingrese el genero del cliente: ";
		cin >> leerGender;
		for (int i = 0; i < sizeof(Gender); i++){
			Gender[i] = leerGender[i];
		}

		cout << "Ingrese la ciudad en la que el cliente vive: ";
		cin >> leerCiudad;
		for (int i = 0; i < sizeof(IdCiudad); i++){
			IdCiudad[i] = leerCiudad[i];
		}

		ofstream writeFile("personas.bin", ofstream::in | ofstream :: out);
		writeFile.seekp(HeaderSize + rrnHeader*( sizeof(IdClient) + sizeof(NameClient) + sizeof(Gender) + sizeof(IdCiudad))  );
		writeFile.write(reinterpret_cast<char*>(&IdClient), sizeof(IdClient));
		writeFile.write(reinterpret_cast<char*>(&NameClient), sizeof(NameClient));
		writeFile.write(reinterpret_cast<char*>(&Gender), sizeof(Gender));
		writeFile.write(reinterpret_cast<char*>(&IdCiudad), sizeof(IdCiudad));
		writeFile.seekp(0);
		writeFile.write(reinterpret_cast<char*>(&nuevaRrn
	), sizeof(nuevaRrn
));
		writeFile.close();
		int position = posicionIndicePrimario( llaveCliente  , atoi(ss.str().c_str()) );
		llaveCliente.insert(llaveCliente.begin()+ position, ss.str());
		//TreeClient.Agregar(Index(atol(ss.str().c_str()) , rrnHeader));
	}else{
		cout << "Ingrese el Id del cliente: ";
		cin >> leerId;
		stringstream ss;
		for (int i = 0; i < sizeof(IdClient); i++){
			IdClient[i] = leerId[i];
			ss<< leerId[i];
		}
		
		cout << "Ingrese el nombre del cliente: ";
		cin >> leerName;
		for (int i = 0; i < sizeof(NameClient); i++){
			NameClient[i] = leerName[i];
		}

		cout << "Ingrese el genero del cliente: ";
		cin >> leerGender;
		for (int i = 0; i < sizeof(Gender); i++){
			Gender[i] = leerGender[i];
		}

		cout << "Ingrese la ciudad en la que el cliente vive: ";
		cin >> leerCiudad;
		for (int i = 0; i < sizeof(IdCiudad); i++){
			IdCiudad[i] = leerCiudad[i];
		}
		ofstream writeFile("personas.bin", ofstream::in | ofstream::out);
		if(rrnHeader == -1){
			writeFile.seekp(HeaderSize + (recorrido-1)*( sizeof(IdClient) + sizeof(NameClient) + sizeof(Gender) + sizeof(IdCiudad))  );
		}else{
			writeFile.seekp(HeaderSize + (recorrido )*( sizeof(IdClient) + sizeof(NameClient) + sizeof(Gender) + sizeof(IdCiudad))  );
		}
		writeFile.seekp(HeaderSize + recorrido*( sizeof(IdClient) + sizeof(NameClient) + sizeof(Gender) + sizeof(IdCiudad)) );
		writeFile.write(reinterpret_cast<char*>(&IdClient), sizeof(IdClient));
		writeFile.write(reinterpret_cast<char*>(&NameClient), sizeof(NameClient));
		writeFile.write(reinterpret_cast<char*>(&Gender), sizeof(Gender));
		writeFile.write(reinterpret_cast<char*>(&IdCiudad), sizeof(IdCiudad));
		recorrido++;
		writeFile.seekp(sizeof(int));
		writeFile.write(reinterpret_cast<char*>(&recorrido), sizeof(int));
		writeFile.close();
		//TreeClient.Agregar(Index(atol(ss.str().c_str()) , recorrido-1));
	}
}

void agregarNumero(){
	ifstream leerArchivo("numeros.bin", ios::binary);
	char Numero[9];
	char Id[14];
	leerArchivo.seekg(0);
	int rrnHeader, recorrido,cont = 0;
	leerArchivo.read(reinterpret_cast<char*>(&rrnHeader), sizeof(int));
	leerArchivo.read(reinterpret_cast<char*>(&recorrido), sizeof(int));
	leerArchivo.seekg(HeaderSize + rrnHeader*( sizeof(Numero) + sizeof(Id) )+ sizeof(Numero) );
	leerArchivo.read(reinterpret_cast<char*>(&Id), sizeof(Id));
	stringstream streamNombre;
	for (int i = 0; i < sizeof(Id); i++){
		streamNombre << Id[i];
	}
	int nuevoRrn = atoi(streamNombre.str().c_str());
	leerArchivo.close();
	string leerId = "", leerDato = "";
	if(rrnHeader != -1){
		cout << "Ingrese el numero: ";
		cin >> leerDato;
		stringstream ss;
		for (int i = 0; i < sizeof(Numero); i++){
			Numero[i] = leerDato[i];
			ss<< leerDato[i];
		}
		
		cout << "Ingrese id del cliente que posee este numero: ";
		cin >> leerId;
		for (int i = 0; i < sizeof(Id); i++){
			Id[i] = leerId[i];
		}
		ofstream writeFile("numeros.bin", ofstream::in | ofstream :: out);
		writeFile.seekp(HeaderSize + rrnHeader*( sizeof(Numero) + sizeof(Id) )  );
		writeFile.write(reinterpret_cast<char*>(&Numero), sizeof(Numero));
		writeFile.write(reinterpret_cast<char*>(&Id), sizeof(Id));
		writeFile.seekp(0);
		writeFile.write(reinterpret_cast<char*>(&nuevoRrn
	), sizeof(nuevoRrn
));
		writeFile.close();
		int position = posicionIndicePrimario( llaveNumero  , atoi(ss.str().c_str()) );
		llaveNumero.insert(llaveNumero.begin()+ position, ss.str());
		//TreeNumber.Agregar(Index(atol(ss.str().c_str()) , rrnHeader));
	}else{
		cout << "Ingrese el numero: ";
		cin >> leerDato;
		stringstream ss;
		for (int i = 0; i < sizeof(Numero); i++){
			Numero[i] = leerDato[i];
			ss<< leerDato[i];
		}
		
		cout << "Ingrese id del cliente que posee este numero: ";
		cin >> leerId;
		for (int i = 0; i < sizeof(Id); i++){
			Id[i] = leerId[i];
		}
		ofstream writeFile("numeros.bin", ofstream::in | ofstream::out);
		if(rrnHeader == -1){
			writeFile.seekp(HeaderSize + (recorrido-1)*( sizeof(Numero) + sizeof(Id))  );
		}else{
			writeFile.seekp(HeaderSize + (recorrido)*( sizeof(Numero) + sizeof(Id))  );
		}
		writeFile.seekp(HeaderSize + recorrido*( sizeof(Numero) + sizeof(Id)) );
		writeFile.write(reinterpret_cast<char*>(&Numero), sizeof(Numero));
		writeFile.write(reinterpret_cast<char*>(&Id), sizeof(Id));
		recorrido++;
		writeFile.seekp(sizeof(int));
		writeFile.write(reinterpret_cast<char*>(&recorrido), sizeof(int));
		writeFile.close();
		//TreeNumber.Agregar(Index(atol(ss.str().c_str()) , recorrido-1));
	}
}

void agregarCiudad(){
	ifstream leerArchivo("ciudades.bin", ios::binary);
	char IdCiudad[5];
	char NameCiudad[40];
	leerArchivo.seekg(0);
	int rrnHeader, recordNumber,cont = 0;
	leerArchivo.read(reinterpret_cast<char*>(&rrnHeader), sizeof(int));
	leerArchivo.read(reinterpret_cast<char*>(&recordNumber), sizeof(int));
	leerArchivo.seekg(HeaderSize + rrnHeader*( sizeof(IdCiudad) + sizeof(NameCiudad) )+ sizeof(IdCiudad) );
	leerArchivo.read(reinterpret_cast<char*>(&NameCiudad), sizeof(NameCiudad));
	stringstream streamNombre;
	for (int i = 0; i < sizeof(NameCiudad); i++){
		streamNombre << NameCiudad[i];
	}
	int nuevoRrn = atoi(streamNombre.str().c_str());
	leerArchivo.close();
	string leerId = "", leerDato = "";
	if(rrnHeader != -1){
		cout << "Ingrese el Id de la ciudad: ";
		cin >> leerId;
		stringstream ss;
		for (int i = 0; i < sizeof(IdCiudad); i++){
			IdCiudad[i] = leerId[i];
			ss<< leerId[i];
		}
		cout << "Ingrese el nombre de la ciudad: ";
		cin >> leerDato;
		for (int i = 0; i < sizeof(NameCiudad); i++){
			NameCiudad[i] = leerDato[i];
		}
		ofstream writeFile("ciudades.bin", ofstream::in | ofstream :: out);
		writeFile.seekp(HeaderSize + rrnHeader*( sizeof(IdCiudad) + sizeof(NameCiudad) )  );
		writeFile.write(reinterpret_cast<char*>(&IdCiudad), sizeof(IdCiudad));
		writeFile.write(reinterpret_cast<char*>(&NameCiudad), sizeof(NameCiudad));
		writeFile.seekp(0);
		writeFile.write(reinterpret_cast<char*>(&nuevoRrn), sizeof(nuevoRrn));
		writeFile.close();
		int position = posicionIndicePrimario( llaveCiudad  , atoi(ss.str().c_str()) );
		llaveCiudad.insert(llaveCiudad.begin()+ position, ss.str());
		//TreeCity.Agregar(Index(atol(ss.str().c_str()) , rrnHeader));
	}else{
		cout << "Ingrese el Id de la ciudad: ";
		cin >> leerId;
		stringstream streamId;
		for (int i = 0; i < sizeof(IdCiudad); i++){
			IdCiudad[i] = leerId[i];
			streamId<< leerId[i];
		}

		cout << "Ingrese el nombre de la ciudad: ";
		cin >> leerDato;
		for (int i = 0; i < sizeof(NameCiudad); i++){
			NameCiudad[i] = leerDato[i];
		}
		ofstream writeFile("ciudades.bin", ofstream::in | ofstream::out);
		if(rrnHeader == -1){
			writeFile.seekp(HeaderSize + (recordNumber -1)*( sizeof(IdCiudad) + sizeof(NameCiudad) )  );
		}else{
			writeFile.seekp(HeaderSize + recordNumber*( sizeof(IdCiudad) + sizeof(NameCiudad)) );
		}
		
		writeFile.seekp(HeaderSize + recordNumber*( sizeof(IdCiudad) + sizeof(NameCiudad)) );
		writeFile.write(reinterpret_cast<char*>(&IdCiudad), sizeof(IdCiudad));
		writeFile.write(reinterpret_cast<char*>(&NameCiudad), sizeof(NameCiudad));
		recordNumber++;
		writeFile.seekp(sizeof(int));
		writeFile.write(reinterpret_cast<char*>(&recordNumber), sizeof(int));
		writeFile.close();
		//TreeCity.Agregar(Index(atol(streamId.str().c_str()) , recordNumber-1));
	}

}

void eliminarCiudad( int key ){
	char IdCiudad[4];
	char NameCiudad[40];
	int position = posicionIndicePrimario(llaveCiudad, key);
	string rrn = rrnCiudad.at(position);
	int rrnEntero = atoi(rrn.c_str());
	stringstream rrnToString;
	stringstream ss;
	ifstream readFile("ciudades.bin", ios::binary);
	readFile.seekg(0);
	int rrnHeader;
	int recorrido;
	readFile.read(reinterpret_cast<char*>(&rrnHeader), sizeof(int));
	readFile.read(reinterpret_cast<char*>(&recorrido), sizeof(int));
	readFile.close();
	ofstream binario("ciudades.bin", ios::out | ios::in);
	if (position != -1){
		IdCiudad[0] ='*';
		rrnToString<< rrnHeader;
		for (int i = 0; i < rrnToString.str().size(); i++){
			NameCiudad[i] = rrnToString.str()[i];
		}
		if(atoi(rrn.c_str()) == recorrido){
			binario.seekp(HeaderSize + (atoi((rrn).c_str()) -1)*( sizeof(IdCiudad) + sizeof(NameCiudad) )  );
		}else{
			binario.seekp(HeaderSize + (atoi((rrn).c_str()) )*( sizeof(IdCiudad) + sizeof(NameCiudad) )  );
		}
		binario.write(reinterpret_cast<char*>(&IdCiudad), sizeof(IdCiudad) );
		binario.write(reinterpret_cast<char*>(&NameCiudad), sizeof(NameCiudad) );// se escribe el rrn en el header
		binario.seekp(0);
		binario.write(reinterpret_cast<char*>(&rrnEntero), sizeof(rrnEntero));
	}
	llaveCiudad.erase(llaveCiudad.begin() +position);
	rrnCiudad.erase(rrnCiudad.begin() +position);
	//TreeCity.Eliminar(Index( (unsigned long)key , atoi(rrn.c_str())));
	binario.close();	
}
void eliminarPersona( long key ){
	char IdClient[14];
	char NameClient[40];
	char Gender[2];
	char IdCiudad[4];
	int position = posicionIndice(llaveCliente, key);
	string rrn = rrnCliente.at(position);
	int rrnInteger = atoi(rrn.c_str());
	stringstream rrnToString;
	ifstream readFile("personas.bin", ios::binary);
	readFile.seekg(0);
	int rrnHeader,recorrido;
	readFile.read(reinterpret_cast<char*>(&rrnHeader), sizeof(int));
	readFile.read(reinterpret_cast<char*>(&recorrido), sizeof(int));
	readFile.close();
	ofstream binario("personas.bin", ios::out | ios::in);
	if (position != -1){
		IdClient[0] ='*';
		rrnToString<< rrnHeader;
		for (int i = 0; i < rrnToString.str().size(); i++){
			NameClient[i] = rrnToString.str()[i];
		}
		if(atoi(rrn.c_str()) == recorrido){
			binario.seekp(HeaderSize + (atoi((rrn).c_str()) -1)*( sizeof(IdClient) + sizeof(NameClient) + sizeof(Gender) + sizeof(IdCiudad))  );
		}else{
			binario.seekp(HeaderSize + (atoi((rrn).c_str()) )*( sizeof(IdClient) + sizeof(NameClient) + sizeof(Gender) + sizeof(IdCiudad))  );
		}
		//binario.seekp(HeaderSize + atoi((rrn).c_str())*( sizeof(IdClient) + sizeof(NameClient) + sizeof(Gender) + sizeof(IdCiudad))  );
		binario.write(reinterpret_cast<char*>(&IdClient), sizeof(IdClient) );
		binario.write(reinterpret_cast<char*>(&NameClient), sizeof(NameClient) );// se escribe el rrn en el header
		binario.seekp(0);
		binario.write(reinterpret_cast<char*>(&rrnInteger), sizeof(rrnInteger));
	}
	llaveCliente.erase(llaveCliente.begin() +position);
	rrnCliente.erase(rrnCliente.begin() +position);
	//TreeClient.Eliminar(Index( (unsigned long)key , atoi(rrn.c_str())));
	binario.close();
}

void eliminarNumero( int key ){
	char Numero[9];
	char Id[15];
	
	int position = posicionIndice(llaveNumero, (long)key);
	string rrn = rrnNumero.at(position);
	int rrnInteger = atoi(rrn.c_str());
	stringstream rrnToString;
	ifstream readFile("Numeros.bin", ios::binary);
	readFile.seekg(0);
	int rrnHeader,recordNumber;
	readFile.read(reinterpret_cast<char*>(&rrnHeader), sizeof(int));
	readFile.read(reinterpret_cast<char*>(&recordNumber), sizeof(int));
	readFile.close();
	ofstream writeFile("Numeros.bin", ios::out | ios::in);
	if (position != -1){
		Numero[0] ='*';
		rrnToString<< rrnHeader;
		for (int i = 0; i < rrnToString.str().size(); i++){
			Id[i] = rrnToString.str()[i];
		}
		if(atoi(rrn.c_str()) == recordNumber){
			writeFile.seekp(HeaderSize + (atoi((rrn).c_str()) -1)*( sizeof(Numero) + sizeof(Id))  );
		}else{
			writeFile.seekp(HeaderSize + (atoi((rrn).c_str()) )*( sizeof(Numero) + sizeof(Id))  );
		}
		//writeFile.seekp(HeaderSize + atoi((rrn).c_str())*( sizeof(Numero) + sizeof(Id) )  );
		writeFile.write(reinterpret_cast<char*>(&Numero), sizeof(Numero) );
		writeFile.write(reinterpret_cast<char*>(&Id), sizeof(Id) );// se escribe el rrn en el header
		writeFile.seekp(0);
		writeFile.write(reinterpret_cast<char*>(&rrnInteger), sizeof(rrnInteger));
	}
	llaveNumero.erase(llaveNumero.begin() +position);
	rrnNumero.erase(rrnNumero.begin() +position);
	//TreeNumber.Eliminar(Index( (unsigned long)key , atoi(rrn.c_str())));
	writeFile.close();
}