#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

struct Usuario {
    string nombre;
    string correo;
    int edad;
};

vector<Usuario> usuarios; // Para guardar datos del usuario

//funcion para limpiar consola
void limpiarConsola() {
    system("cls");
}

// Aqui se hizo uso de la funcion const que es para declarar una informacion que aparecera constantemente
// Sobre esta funcion nos informamos mas en https://learn.microsoft.com/es-es/cpp/cpp/const-cpp?view=msvc-170


//Funcion para mostrar la informacion de los usuarios
void mostrarInformacion(const vector<Usuario>& usuarios) {
    cout << "Informacion del Usuario:\n";
    cout << "---------------------------------\n";
    for (const auto& Usuario : usuarios) {
    cout << "Nombre Completo: " << Usuario.nombre << "\tCorreo: " << Usuario.correo<< "\tEdad: "<< Usuario.edad<<"\n";
        // Mostrar otros campos según sea necesario
        cout << "---------------------------------\n";
    }};
     

     //Funcion con log para guardar el registro en un archivo
    void guardarLog(const string& accion) {
    ofstream logFile("log.txt", ios::app);
    if (logFile.is_open()) {
        logFile << accion << "\n";
        logFile.close();
    } else {
        cout << "Error al abrir el archivo de registro.\n";
    }
}

//
void agregarNuevaInformacion(vector<Usuario>& usuarios) {
    Usuario nuevoUsuario;
    cout << "Ingrese el nombre del nuevo usuario: ";
    cin >> nuevoUsuario.nombre;

    // aqui comprobaremos si ese nombre de usuario aun no ha sido ingresado a registro
    for (const auto& Usuario : usuarios) {
        if (Usuario.nombre == nuevoUsuario.nombre) {
            cout << "Este usuario ya existe en la base de datos.\n";
            return;
        }
    }

    cout << "Ingrese la edad del nuevo estudiante: ";
    cin >> nuevoUsuario.edad;

    cout << "Ingrese el correo del nuevo estudiante: ";
    cin >> nuevoUsuario.correo;

    // Agregamos el nuevo usuario
   usuarios.push_back(nuevoUsuario);

    // Aqui usamos log nuevamente
    guardarLog("Se agregó nueva información para " + nuevoUsuario.nombre);
}

