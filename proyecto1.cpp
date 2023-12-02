#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

struct Usuario {
    string nombre;
    string apellido;
    string correo;
    int edad;
};

vector<Usuario> usuarios;  // Almacenar los usuarios en memoria

// Funciones prototipo
void mostrarMenu();
void mostrarMenuAdmin();
void mostrarMenuUsuario();
void limpiarConsola();
void cargarDatos();
void guardarDatos();
void agregarUsuario();
void buscarUsuario();
void modificarUsuario();
void eliminarUsuario();
void mostrarUsuarios();
void registrarLog(const string& accion);
void mostrarCursosDisponibles();

int main() {
    cargarDatos();  // Cargar datos existentes desde un archivo al iniciar el programa

    while (true) {
        mostrarMenu();
        int opcion;
        cin >> opcion;
        cin.ignore();  // Limpiar el buffer de entrada

        switch (opcion) {
            case 1:  // Usuario Administrador
                mostrarMenuAdmin();
                int opcionAdmin;
                cin >> opcionAdmin;
                cin.ignore();

                switch (opcionAdmin) {
                    case 1: agregarUsuario(); break;
                    case 2: buscarUsuario(); break;
                    case 3: modificarUsuario(); break;
                    case 4: eliminarUsuario(); break;
                    case 5: mostrarUsuarios(); break;
                    case 6: break;  // Regresar al menú principal
                    case 7: return 0;  // Salir del programa
                    default: cout << "Opción no válida." << endl;
                }
                break;

            case 2:  // Usuario General
                mostrarMenuUsuario();
                int opcionUsuario;
                cin >> opcionUsuario;
                cin.ignore();

                switch (opcionUsuario) {
                    case 1: buscarUsuario(); break;
                    case 2: mostrarCursosDisponibles(); break;
                    case 3: break;  // Regresar al menú principal
                    case 4: return 0;  // Salir del programa
                    default: cout << "Opción no válida." << endl;
                }
                break;

            case 3: return 0;  // Salir del programa
            default: cout << "Opción no válida." << endl;
        }
    }

    return 0;
}

void mostrarMenu() {
    limpiarConsola();
    cout << "Bienvenido al programa de gestión de usuarios" << endl;
    cout << "1. Usuario Administrador" << endl;
    cout << "2. Usuario General" << endl;
    cout << "3. Salir" << endl;
    cout << "Ingrese su opción: ";
}

void mostrarMenuAdmin() {
    limpiarConsola();
    cout << "Menú Administrador" << endl;
    cout << "1. Agregar Usuario" << endl;
    cout << "2. Buscar Usuario" << endl;
    cout << "3. Modificar Usuario" << endl;
    cout << "4. Eliminar Usuario" << endl;
    cout << "5. Mostrar Usuarios" << endl;
    cout << "6.. Regresar al menú principal" << endl;
    cout << "7. Salir del programa" << endl;
    cout << "Ingrese su opción: ";
}

void mostrarMenuUsuario() {
    limpiarConsola();
    cout << "Menú Usuario General" << endl;
    cout << "1. Buscar Usuario" << endl;
    cout << "2. Mostrar Cursos disponibles" << endl;
    cout << "3. Regresar al menú principal" << endl;
    cout << "4. Salir del programa" << endl;
    cout << "Ingrese su opción: ";
}

void limpiarConsola() {
    system( "cls");
}

void cargarDatos() {
    ifstream archivo("usuarios.txt");
    if (archivo.is_open()) {
        Usuario usuario;
        while (getline(archivo, usuario.nombre)) {
            getline(archivo, usuario.apellido);
            getline(archivo, usuario.correo);
            archivo >> usuario.edad;
            usuarios.push_back(usuario);
        }
        archivo.close();
    } else {
        cout << "No se pudo abrir el archivo de usuarios." << endl;
    }
}

void guardarDatos() {
    ofstream archivo("usuarios.txt");
    if (archivo.is_open()) {
        for (const Usuario& usuario : usuarios) {
            archivo << usuario.nombre << endl;
            archivo << usuario.apellido << endl;
            archivo << usuario.correo << endl;
            archivo << usuario.edad << endl;
        }
        archivo.close();
    } else {
        cout << "No se pudo abrir el archivo de usuarios." << endl;
    }
}

void agregarUsuario() {
    Usuario usuario;
    cout << "Ingrese el nombre: ";
    getline(cin, usuario.nombre);
    cout << "Ingrese el apellido: ";
    getline(cin, usuario.apellido);
    cout << "Ingrese el correo: ";
    getline(cin, usuario.correo);
    cout << "Ingrese la edad: ";
    cin >> usuario.edad;
    cin.ignore();
    usuarios.push_back(usuario);
    guardarDatos();
    registrarLog("Se agregó un usuario.");
    cout << "Usuario agregado exitosamente." << endl;
}

void buscarUsuario() {
    string busqueda;
    cout << "Ingrese el término de búsqueda: ";
    getline(cin, busqueda);

    limpiarConsola();
    cout << "Resultados de la búsqueda:" << endl;
    for (const Usuario& usuario : usuarios) {
        if (usuario.nombre.find(busqueda) != string::npos ||
            usuario.apellido.find(busqueda) != string::npos ||
            usuario.correo.find(busqueda) != string::npos ||
            to_string(usuario.edad).find(busqueda) != string::npos) {
            cout << "Nombre: " << usuario.nombre << endl;
            cout << "Apellido: " << usuario.apellido << endl;
            cout << "Correo: " << usuario.correo << endl;
            cout << "Edad: " << usuario.edad << endl;
            cout << "---------------------------" << endl;
        }
    }
}

void modificarUsuario() {
    string correo;
    cout << "Ingrese el correo del usuario que desea modificar: ";
    getline(cin, correo);

    for (Usuario& usuario : usuarios) {
        if (usuario.correo == correo) {
            cout << "Ingrese el nuevo nombre: ";
            getline(cin, usuario.nombre);
            cout << "Ingrese el nuevo apellido: ";
            getline(cin, usuario.apellido);
            cout << "Ingrese el nuevo correo: ";
            getline(cin, usuario.correo);
            cout << "Ingrese la nueva edad: ";
            cin >> usuario.edad;
            cin.ignore();
            guardarDatos();
            registrarLog("Se modificó un usuario.");
            cout << "Usuario modificado exitosamente." << endl;
            return;
        }
    }

    cout << "Usuario no encontrado." << endl;
}

void eliminarUsuario() {
    string correo;
    cout << "Ingrese el correo del usuario que desea eliminar: ";
    getline(cin, correo);

    for (auto it = usuarios.begin(); it != usuarios.end(); ++it) {
        if (it->correo == correo) {
            usuarios.erase(it);
            guardarDatos();
            registrarLog("Se eliminó un usuario.");
            cout << "Usuario eliminado exitosamente." << endl;
            return;
        }
    }

    cout << "Usuario no encontrado." << endl;
}

void mostrarUsuarios() {
    limpiarConsola();
    cout << "Lista de Usuarios:" << endl;
    for (const Usuario& usuario : usuarios) {
        cout << "Nombre: " << usuario.nombre << endl;
        cout << "Apellido: " << usuario.apellido << endl;
        cout << "Correo: " << usuario.correo << endl;
        cout << "Edad: " << usuario.edad << endl;
        cout << "---------------------------" << endl;
    }
}

void registrarLog(const string& accion) {
    ofstream log("log.txt", ios::app);
    if (log.is_open()) {
        log << accion << endl;
        log.close();
    } else {
        cout << "No se pudo abrir el archivo de registro." << endl;
    }
}

void mostrarCursosDisponibles() {
    std::cout << "=== CURSOS DISPONIBLES ===" << std::endl;  
    cout << "1. Inglés como Segundo Idioma (principiantes)" << endl;
    cout << "2.Cursos Académicos (medio, avanzado)" << endl;
    cout << "3. Taller bilingue de arte y cultura (General)" << endl;
    cout << "4. Habilidades Interpersonales (principiante, medio)" << endl;
    cout << "habilidades de Idioma Nativo (avanzado)" << endl;
    cout << "Ingrese su opción: ";
} 