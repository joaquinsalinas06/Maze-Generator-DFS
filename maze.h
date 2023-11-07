#include <iostream>
#include <stack>
#include <vector>
#include <random>
#include <ctime>
#include <iomanip>
using namespace std;

void imprimirLaberinto(char** laberinto);

// Define la estructura del nodo en el laberinto
struct Nodo {
    Nodo* arriba = nullptr;
    Nodo* abajo = nullptr;
    Nodo* izquierda = nullptr;
    Nodo* derecha = nullptr;
    pair<int, int> valor;  // Almacena la posición del nodo en la matriz
    bool visitado = false; // Indica si el nodo ha sido visitado
};

// Crea una matriz de nodos 10x10 y la inicializa
Nodo** crearMatriz() {
    Nodo** matriz = new Nodo*[10];
    for (int i = 0; i < 10; ++i)
        matriz[i] = new Nodo[10];

    for (int i = 0; i < 10; i++) {
        for (int j = 0; j < 10; j++) {
            matriz[i][j].valor.first = i;
            matriz[i][j].valor.second = j;
        }
    }
    return matriz;
}

//crea una funcion que tome a la matriz y obtenga el numero de nodos visitados, sume 1 a la variable y la retorne


// Genera un laberinto utilizando el algoritmo de generación de laberintos DFS
void crearLaberinto(Nodo** matrix) {
    srand(time(NULL)); // Inicializa el generador de números aleatorios
    Nodo* inicio = &matrix[0][0]; // Nodo inicial
    Nodo* actual = inicio;       // Nodo actual
    stack<Nodo*> camino;      // Almacena el camino recorrido
    int visitados = 1;          // Contador de nodos visitados

    random_device rd; // Genera un número aleatorio
    mt19937 gen(rd()); // Inicializa el generador de números aleatorios
    uniform_int_distribution<> dis(0, 3); // Genera un número aleatorio entre 0 y 3

    while (visitados != 115) { // Mientras no se hayan visitado todos los nodos


        vector<int> direccionesValidas; // Almacena las direcciones válidas en las que se puede mover
        cout<<"----------------------"<<endl;
        // Verifica las direcciones válidas en las que se puede mover
        if (actual->valor.first > 0 && !matrix[actual->valor.first - 1][actual->valor.second].visitado) {
            cout<<matrix[actual->valor.first - 1][actual->valor.second].visitado<<endl;
            direccionesValidas.push_back(0); // Arriba
        }
        if (actual->valor.first < 9 && !matrix[actual->valor.first + 1][actual->valor.second].visitado) {
            cout<<matrix[actual->valor.first +1][actual->valor.second].visitado<<endl;
            direccionesValidas.push_back(1); // Abajo
        }
        if (actual->valor.second > 0 && !matrix[actual->valor.first][actual->valor.second - 1].visitado) {
            cout<<matrix[actual->valor.first][actual->valor.second - 1].visitado<<endl;
            direccionesValidas.push_back(2); // Izquierda
        }
        if (actual->valor.second < 9 && !matrix[actual->valor.first][actual->valor.second + 1].visitado) {
            cout<<matrix[actual->valor.first][actual->valor.second + 1].visitado<<endl;
            direccionesValidas.push_back(3); // Derecha
        }
        cout<<"----------------------"<<endl;

        if (!direccionesValidas.empty()) { // Si hay direcciones válidas
            int direction = direccionesValidas[dis(gen) % direccionesValidas.size()]; // Selecciona una dirección aleatoria
            Nodo* siguiente = nullptr; // Nodo siguiente

            // Realiza la acción según la dirección seleccionada y conecta los nodos
            if (direction == 0) {
                siguiente = &matrix[actual->valor.first - 1][actual->valor.second]; // Arriba
                actual->arriba = siguiente; // Conecta el nodo actual con el siguiente
                siguiente->abajo = actual; // Conecta el nodo siguiente con el actual

            } else if (direction == 1) {    // Abajo
                siguiente = &matrix[actual->valor.first + 1][actual->valor.second]; // Abajo
                actual->abajo = siguiente;
                siguiente->arriba = actual;


            } else if (direction == 2) {   // Izquierda
                siguiente = &matrix[actual->valor.first][actual->valor.second - 1];
                actual->izquierda = siguiente;
                siguiente->derecha = actual;


            } else if (direction == 3) {  // Derecha
                siguiente = &matrix[actual->valor.first][actual->valor.second + 1];
                actual->derecha = siguiente;
                siguiente->izquierda = actual;

            }
            actual->visitado = true; // Marca el nodo actual como visitado
            actual = siguiente; // El nodo actual ahora es el siguiente
            visitados++; // Incrementa el contador de nodos visitados
            camino.push(actual); // Almacena el nodo en el camino recorrido
        } else { // Si no hay direcciones válidas
            cout<<"----------------------"<<endl;
            cout<<"No hay direcciones validas"<<endl;
            cout<<"----------------------"<<endl;
            if (!camino.empty()) { // Si el camino recorrido no está vacío
                actual = camino.top(); // El nodo actual ahora es el último nodo del camino recorrido
                camino.pop(); // Elimina el último nodo del camino recorrido

            }
        }
    }
}

char** generarLaberinto(Nodo** matriz) {
    int nodovalido=0;
    int nodocount=0;

    char** laberinto = new char*[30];
    for (int i = 0; i < 30; i++) {
        laberinto[i] = new char[30];
    }

    for (int i = 0; i < 30; i++) {
        for (int j = 0; j < 30; j++) {
            laberinto[i][j] = '#';
        }
    }

    for(int i=1;i<29;i+=3){
        for(int j=1;j<29;j+=3){
            Nodo* nodo = &matriz[i/3][j/3];

            if(nodo->arriba!=nullptr){
                nodovalido++;
                laberinto[i-1][j]=' ';
            }

            if(nodo->abajo!=nullptr){
                nodovalido++;
                laberinto[i+1][j]=' ';
            }

            if(nodo->izquierda!=nullptr){
                nodovalido++;
                laberinto[i][j-1]=' ';
            }

            if(nodo->derecha!=nullptr){
                nodovalido++;
                laberinto[i][j+1]=' ';
            }
            if(nodovalido!=0){
                laberinto[i][j]=' ';
                nodocount++;
            }
            nodovalido=0;
        }
    }
    cout<<"Nodos: "<<nodocount<<endl;
    return laberinto;
}

void imprimirLaberinto(char** laberinto){
    for(int i=0;i<30;i++){
        for(int j=0;j<30;j++){
            cout<<setw(3)<<laberinto[i][j];
        }
        cout<<endl;
    }
}

void InicioFin(Nodo** Nodos, char** dibujo) {
    //make the user insert x and y point for the start point
    int x, y;
    cout << "Ingrese la posicion x del punto de inicio" << endl;
    cin >> x;
    cout << "Ingrese la posicion y del punto de inicio" << endl;
    cin >> y;
    //validate if the point is inside the bounding of the matrix, which is 10x10
    while (x < 0 || x > 9 || y < 0 || y > 9) {
        cout << "El punto ingresado no esta dentro de los limites de la matriz" << endl;
        cout << "Ingrese la posicion x del punto de inicio" << endl;
        cin >> x;
        cout << "Ingrese la posicion y del punto de inicio" << endl;
        cin >> y;
    }

    pair<int, int> inicio(x, y);
    while (Nodos[inicio.first][inicio.second].arriba == nullptr && Nodos[inicio.first][inicio.second].abajo == nullptr && Nodos[inicio.first][inicio.second].izquierda == nullptr && Nodos[inicio.first][inicio.second].derecha == nullptr) {
        cout << "El nodo seleccionado no tiene conecciones" << endl;
        cout << "Ingrese la posicion x del punto de inicio" << endl;
        cin >> x;
        cout << "Ingrese la posicion y del punto de inicio" << endl;
        cin >> y;
        inicio.first = x;
        inicio.second = y;
        while (x < 0 || x > 9 || y < 0 || y > 9) {
            cout << "El punto ingresado no esta dentro de los limites de la matriz" << endl;
            cout << "Ingrese la posicion x del punto de inicio" << endl;
            cin >> x;
            cout << "Ingrese la posicion y del punto de inicio" << endl;
            cin >> y;
        }
    }


    dibujo[(inicio.first * 3)+1][(inicio.second * 3)+1] = 'S';

    cout << "Ingrese la posicion x del punto de fin" << endl;
    cin >> x;
    cout << "Ingrese la posicion y del punto de fin" << endl;
    cin >> y;

    while (x < 0 || x > 9 || y < 0 || y > 9) {
        cout << "El punto ingresado no esta dentro de los limites de la matriz" << endl;
        cout << "Ingrese la posicion x del punto de fin" << endl;
        cin >> x;
        cout << "Ingrese la posicion y del punto de fin" << endl;
        cin >> y;
    }

    pair<int, int> fin(x, y);
    while (Nodos[fin.first][fin.second].arriba == nullptr && Nodos[fin.first][fin.second].abajo == nullptr && Nodos[fin.first][fin.second].izquierda == nullptr && Nodos[fin.first][fin.second].derecha == nullptr) {
        cout << "El nodo seleccionado no tiene conecciones" << endl;
        cout << "Ingrese la posicion x del punto de fin" << endl;
        cin >> x;
        cout << "Ingrese la posicion y del punto de fin" << endl;
        cin >> y;
        fin.first = x;
        fin.second = y;
        while (x < 0 || x > 9 || y < 0 || y > 9) {
            cout << "El punto ingresado no esta dentro de los limites de la matriz" << endl;
            cout << "Ingrese la posicion x del punto de fin" << endl;
            cin >> x;
            cout << "Ingrese la posicion y del punto de fin" << endl;
            cin >> y;
        }
    }
    dibujo[(fin.first * 3)+1][(fin.second * 3)+1] = 'F';

    imprimirLaberinto(dibujo);
}


