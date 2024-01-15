#include <iostream> //para las entradas y salidas
#include <ctime> //se usa para la generación de números aleatorios

using namespace std; //para el cin y cout

struct StackNode { //Define un nodo de una pila con coordenadas X, Y y un puntero al siguiente nodo
    int coordX;
    int coordY;
    StackNode* next;

    StackNode(int coordX, int coordY); //Constructor de StackNode
};

class Stack { //Define una clase de pila con operaciones básicas como push, pop, isEmpty
private:
    StackNode* top; //puntero

public:
    Stack();
    ~Stack(); //libera la memoria de la pila.

    bool isEmpty(); //Devuelve true si la pila está vacía
    void push(int x, int y); //Añade un nuevo nodo al tope de la pila.
    void pop(); //Elimina el nodo del tope de la pila.
    void printStack(); //Imprime los elementos de la pila.
    StackNode* getTop() const; //Devuelve el nodo en el tope de la pila.
};

StackNode::StackNode(int coordX, int coordY): coordX(coordX), coordY(coordY), next(nullptr) {} 

Stack::Stack() : top(nullptr) {} //Constructor de la clase Stack, inicializa el tope de la pila a nulo.

Stack::~Stack() {
    while (!isEmpty()) {
        pop();
    }
}

bool Stack::isEmpty() {
    return top == nullptr;
}

void Stack::push(int x, int y) {
    StackNode* newNode = new StackNode(x, y);
    newNode->next = top;
    top = newNode;
}

void Stack::pop() {
    if (!isEmpty()) {
        StackNode* temp = top;
        top = top->next;
        delete temp;
    }
}

void Stack::printStack() {
    StackNode* current = top;                       
   
    
    while (current != nullptr) {
        std::cout << "(" << current->coordX << ", " << current->coordY << ") ";
        current = current->next;
    }

    std::cout << std::endl;
}

StackNode* Stack::getTop() const { return top; }


int** Matriz(int filas, int columnas, float densidad); //función para generar una matriz que representa el laberinto.


void Laberinto(int **laberinto, int filas, int columnas); //funcion que permite visualizar el laberinto y el camino de salida

void Camino(int **&matriz, Stack camino); //funcion que actualiza el laberinto con el camino a la salida

bool buscar_salida(int x, int y, int filas, int columnas, int** &matriz, Stack &camino); //funcion que encuentra el camino a la salida 

bool esValido(int x, int y, int filas, int columnas, int** &matriz); //función que verifica si una celda dada es válida para moverse dentro del laberinto.



int main() { //se define el tamaño del laberinto, su densidad, y se inicia la búsqueda de una salida.
	int filas = 15;
	int columnas = 35;
	float densidad = 0.5; // entre 0 y 1

	int **laberinto = Matriz(filas, columnas, densidad);

	// Se hace una copia del laberinto para buscar una salida y buscamos la coord de la entrada
	int** copia_laberinto = new int*[filas];
	int entradaX, entradaY;

    for (int y = 0; y < filas; ++y) {
        copia_laberinto[y] = new int[columnas];
        for (int x = 0; x < columnas; ++x) {
            copia_laberinto[y][x] = laberinto[y][x];
			if (laberinto[y][x] == -1) {
				entradaX = x;
				entradaY = y;
			}
        }
    }

	// Se busca un camino a la salida
	Stack camino;
	bool haySalida = buscar_salida(entradaX, entradaY, filas, columnas, copia_laberinto, camino);

	if (haySalida) {
		Camino(laberinto, camino);
		Laberinto(laberinto, filas, columnas);
	} 

    return 0;
}

int** Matriz(int filas, int columnas, float densidad) { //crea y devuelve una matriz (laberinto) de tamaño especificado con una densidad de paredes. 
	int **matriz; //se crea una matriz doble 
	matriz = new int *[filas]; //inicializamos, creamos la cantidad de filas
	for (int i = 0; i < filas; i++) { // el for para cada fila creamos el num de columnas
		matriz[i] = new int[columnas]; //para la matriz en el punto i new int en el num de columnas, se crea un cuadro vacio
	}

	int FParedes = densidad * 8; 
	densidad = filas * columnas * densidad / 4;

	//valores
	for (int i = 0; i < filas; i++) { //recorremos toda la matriz con el doble for
		for (int j = 0; j < columnas; j++) {
			if (i == 0 || j == 0 || i == filas - 1 || j == columnas - 1) { //se marca todas las filas y columnas
				matriz[i][j] = 1; //las posicions se representan con el num 1
			}
			else {
				matriz[i][j] = 0; 
			}
		}
	}
	//matriz 
	srand(time(NULL));
	for (int i = 0; i < densidad; i++) {
		int x = rand() % (columnas - 4) +2; //declaramos los va.lores x e y que son para los valores aleatorios en el laberinto
		x = (x / 2) * 2; //dependindo de que valores tome el tama;o de mi area tambien se le evalua en que posicion calcular para generar los muros
		int y = rand() % (filas - 4) + 2; //rand desde 0 hasta filas, para el rand no tome valores fuera del campo
		y = (y / 2) * 2;
		matriz[y][x] = 1; //a todos los puntos aleatorios le asignamos como el num 1 
			int mx[4] = {x, 	x, 		x + 2, 	x - 2}; //creamos un array que se llama mx de 4 de longitud
			int my[4] = {y + 2, y - 2, 	y, 	y}; //para posicionar los 4 puntos posibls para generar el muro de obstaculos dentro del laberinto
			int r = rand() % 4; //se coloca a 4 para que vaya de 0 a 3
			if (matriz[my[r]][mx[r]] == 0) { // si el punto random elegido en la matriz 
				matriz[my[r]][mx[r]] = 1; 
				matriz[my[r] + (y - my[r])/2][mx[r] + (x- mx[r])/2] = 1;
			} 
			// armar pared con el borde
			else if (mx[r] == 0 || my[r] == 0 || mx[r] == columnas - 1 || my[r] == filas - 1) { 
				matriz[my[r] + (y - my[r])/2][mx[r] + (x- mx[r])/2] = 1;
			}
		
	}
	//generar entrada y salida aleatorias del laberinto
	int cantOpciones = 2 * (filas / 2 + columnas / 2);
	int entrada = rand() % (cantOpciones);
	int salida = rand() % (cantOpciones);

	// En caso de que la entrada sea la misma que la salida
	while (entrada == salida) {
		salida = rand() % (cantOpciones);
	}

	int entradaX = 0;
	int entradaY = 0;
	int salidaX = 0;
	int salidaY = 0;

	int aux;
	if (entrada < filas/2) {
		entradaY = 2*entrada+1;
	} else if (entrada < filas/2 + columnas/2) {
		aux = entrada - filas/2;
		entradaX = 2*aux+1;
	} else if (entrada < 2 * (filas/2) + columnas/2) {
		aux = entrada - filas/2 - columnas/2;
		entradaX = columnas -1;
		entradaY = 2*aux+1;
	} else {
		aux = entrada - 2*(filas/2) - columnas/2;
		entradaX = 2*aux+1;
		entradaY = filas - 1;
	}

	if (salida < filas/2) {
		salidaY = 2*salida+1;
	} else if (salida < filas/2 + columnas/2) {
		aux = salida - filas/2;
		salidaX = 2*aux+1;
	} else if (salida < 2 * (filas/2) + columnas/2) {
		aux = salida - filas/2 - columnas/2;
		salidaX = columnas -1;
		salidaY = 2*aux+1;
	} else {
		aux = salida - 2*(filas/2) - columnas/2;
		salidaX = 2*aux+1;
		salidaY = filas - 1;
	}

	matriz[entradaY][entradaX] = -1;
	matriz[salidaY][salidaX] = -2;

	return matriz;
}

void Laberinto(int **laberinto, int filas, int columnas) { 
	for (int i = 0; i < filas; i++) {
		for (int j = 0; j < columnas; j++) {
			if (laberinto[i][j] == 1) {  
				cout << "▉"; 
			} else if(laberinto[i][j] == 0) {
				cout << " ";
			} else if (laberinto[i][j] == -1) { 
				cout << "E"; 
			} else if (laberinto[i][j] == -2) { 
				cout << "S"; 
			} else if(laberinto[i][j] == 2) {
				cout << "*";
			}
		}
		cout << endl; 
	}
}

void Camino(int **&matriz, Stack camino) { //Actualiza la matriz del laberinto con el camino encontrado por la función buscar_salida
	StackNode* current = camino.getTop();
	int x,y;
    
    while (current != nullptr) { //entra en un bucle while que se ejecuta mientras el nodo actual no sea nullptr (indicando que la pila no está vacía).
		x = current -> coordX;	 
		y = current -> coordY;	
		//cargamos el camino, menos la entrada o la salida
		if (matriz[y][x] != -1 && matriz[y][x] != -2) {
			matriz[y][x] = 2;
		} //si la posición actual en la matriz no es la entrada o la salida, la función actualiza esa posición en la matriz a 2. Este valor 2 puede representar el camino encontrado.
        
        current = current->next; //actualizar la posición, avanza al siguiente nodo en la pila 
    }

}

bool buscar_salida(int x, int y, int filas, int columnas, int** &matriz, Stack &camino) { //busca recursivamente un camino desde un punto dado hasta la salida del laberinto.
	camino.push(x,y);
    if (x < 0 || x >= columnas || y < 0 || y >= filas) {
		camino.pop();
        return false;
    }

    if (matriz[y][x] == -2) {
        return true;  //se encuentra la salida
    }

    if (!esValido(x, y, filas, columnas, matriz) || matriz[y][x] == 2) {
		camino.pop();
        return false;  // Casilla inválida o ya visitada
    }

    matriz[y][x] = 2; //casilla visitada


    // prueba todas las direcciones posibles para moverse
    if (
		buscar_salida(x + 1, y, filas, columnas, matriz, camino) || 
		buscar_salida(x, y + 1, filas, columnas, matriz, camino) || 
		buscar_salida(x - 1, y, filas, columnas, matriz, camino) || 
		buscar_salida(x, y - 1, filas, columnas, matriz, camino)
	) {
        return true;  // Se encontró la salida en alguna de las direcciones
    }

    camino.pop();
    return false;
}

bool esValido(int x, int y, int filas, int columnas, int**&matriz) { //Verifica si una celda es un espacio vacío, la entrada o la salida, y no está fuera de los límites del laberinto.

	if (x >= 0 && x < columnas && y >= 0 && y < filas) // Validar si los valores son coordenadas de la matriz
		return matriz[y][x] == 0 || matriz[y][x] == -2 || matriz[y][x] == -1;
	return false;
	//verifica si la posicion es una pared o no, Si es una pared retorna false, caso contrario true
}