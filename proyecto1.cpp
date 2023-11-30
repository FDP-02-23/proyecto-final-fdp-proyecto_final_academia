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

void eliminarInformacionExistente(vector<Usuario>& usuarios) {
    string nombreEliminar;
    cout << "Ingrese el nombre a eliminar: ";
    cin >> nombreEliminar;

    for (auto it = usuarios.begin(); it != usuarios.end(); ++it) {
        if (it->nombre == nombreEliminar) {
            // Eliminar el estudiante
            usuarios.erase(it);

            // Guardar en el log
            guardarLog("Se eliminó la información de " + nombreEliminar);
            return;
        }
    }

    cout << "No se encontró el estudiante con el nombre proporcionado.\n";
}

int main() {
    vector<Usuario> usuarios;

    int opcionPrincipal;
    do {

        //limpiamos nuestra consola
        limpiarConsola();

        //Mostramos las opciones del menu
        cout << "Programa de Gestion de Estudiantes\n";
        cout << "---------------------------------\n";
        cout << "1. Opciones administrativas\n";
        cout << "2. Opciones de usuario general\n";
        cout << "3. Salir del programa\n";
        
        cout << "Ingrese la opcion: ";
        cin >> opcionPrincipal;
   switch (opcionPrincipal) {
            case 1: // Opciones administrativas
                int opcionAdmin;
                do {
                    limpiarConsola();
                    cout << "1. Buscar y modificar un dato\n";
                    cout << "2. Agregar nueva informacion\n";
                    cout << "3. Eliminar informacion existente\n";
                    cout << "4. Regresar al menu principal\n";
                    cout << "5. Salir del programa\n";
                    cout << "Ingrese la opcion: ";
                    cin >> opcionAdmin;

                    switch (opcionAdmin) {
                        case 1:
                            
                            break;
                        case 2:
                            agregarNuevaInformacion(usuarios);
                            break;
                        case 3:
                            eliminarInformacionExistente(usuarios);
                            break;
                        case 4:
                            // Regresar al menú principal
                            break;
                        case 5:
                            // Salir del programa
                            break;
                        default:
                            cout << "Opcion no valida. Intente de nuevo.\n";
                    }

                } while (opcionAdmin != 4 && opcionAdmin != 5);
                break;


     } while (opcionPrincipal != 3);

    return 0;
}

