#include <iostream>                         //aca se especifican las 4 bibliotecas utilizadas en este codigo
#include <fstream>
#include <string>
#include <vector>

using namespace std;

struct Usuario {                             // la estructura que va a presentar cada usuario (por estudiante registrado)
    string nombre;
    string apellido;
    string correo;
    int edad;
};

vector<Usuario> usuarios;                   // Almacenar los usuarios en memoria

// Funciones prototipo
void mostrarMenu();                         // Especificamos las funciones autilizar, para luego asignarles su rol a cada una de ellas
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
void verCuotaMensual();
void registrarLog(const string& accion);    // Aqui se hizo uso de la funcion const que es para declarar una informacion que aparecera constantemente, en la línea 141 comenzamos a utilizarlo
void mostrarCursosDisponibles();            // Sobre esta funcion nos informamos mas en https://learn.microsoft.com/es-es/cpp/cpp/const-cpp?view=msvc-170

int main() {
    cargarDatos();  // Cargar datos existentes desde un archivo al iniciar el programa

    while (true) {
        mostrarMenu();
        int opcion;
        cin >> opcion;
        cin.ignore();                // Limpiar el buffer de entrada

        switch (opcion) {
            case 1:                  // Usuario Administrador
                mostrarMenuAdmin();
                int opcionAdmin;
                cin >> opcionAdmin;
                cin.ignore();

                switch (opcionAdmin) {              //las funciones que puede ejecutar el Administrador 
                    case 1: agregarUsuario(); break;
                    case 2: buscarUsuario(); break;
                    case 3: modificarUsuario(); break;
                    case 4: eliminarUsuario(); break;
                    case 5: mostrarUsuarios(); break;
                    case 6: break;              // Regresar al menu principal
                    case 7: return 0;           // Salir del programa
                    default: cout << "Opcion no valida." << endl;
                }
                break;

            case 2:  // Usuario General
                mostrarMenuUsuario();
                int opcionUsuario;
                cin >> opcionUsuario;
                cin.ignore();

                switch (opcionUsuario) {        //las funciones que puede ejecutar el estudiante
                    case 1: buscarUsuario(); break;
                    case 2: mostrarCursosDisponibles(); break;
                    case 3: verCuotaMensual();  break; // Llama a la función para ver la cuota mensual
                    case 4: break;  // Regresar al menú principal
                    case 5: return 0;  // Salir del programa
                    default: cout << "Opcion no valida." << endl;
                }
                break;

            case 3: return 0;  // Salir del programa
            default: cout << "Opcion no valida." << endl;
        }
    }

    return 0;
}

void mostrarMenu() {
    limpiarConsola();                                              
    cout << "Bienvenido al programa de gestion de usuarios" << endl;         //quien ejecute el código debe seleccionar dependiendo su funcion, o puede salir del programa
    cout << "1. Usuario Administrador" << endl;
    cout << "2. Usuario General" << endl;
    cout << "3. Salir" << endl;
    cout << "Ingrese su opcion: ";
}

void mostrarMenuAdmin() {
    limpiarConsola();                                               //si el usuario es administrador, puede seleccionar 5 acciones principales o regresar 
    cout << "Menu Administrador" << endl;
    cout << "1. Agregar Usuario" << endl;
    cout << "2. Buscar Usuario" << endl;
    cout << "3. Modificar Usuario" << endl;
    cout << "4. Eliminar Usuario" << endl;
    cout << "5. Mostrar Usuarios" << endl;
    cout << "6.. Regresar al menu principal" << endl;
    cout << "7. Salir del programa" << endl;
    cout << "Ingrese su opcion: ";
}

void mostrarMenuUsuario() {
    limpiarConsola();                                           //si el usuario es estudiante, puede seleccionar una de las 3 opciones principales o regresar 
    cout << "Menú Usuario General" << endl;
    cout << "1. Buscar Usuario" << endl;
    cout << "2. Mostrar Cursos disponibles" << endl;
    cout << "3. Matrícula en línea" << endl;
    cout << "4. Regresar al menú principal" << endl;
    cout << "5. Salir del programa" << endl;
    cout << "Ingrese su opcion: ";
}

void limpiarConsola() {                                        //para general el bucle siempre y cuando el usuario no seleccione la opcion de salir del programa
   
}

void cargarDatos() {                                            //funcion que ejecuta el archivo donde se encuentran almacenados los usuarios, para luego poder realizar cambios(si es solicitado)
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

void guardarDatos() {                                               //esta función permite que los datos sean almacenados directamente en un archivo .txt y de esa forma
    ofstream archivo("usuarios.txt");                               //facilitar diferentes acciones que el usuario administrador puede realizar
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

void agregarUsuario() {                                         //aca se une el STRUCT Usuario que definimos al principio del codigo, el usuario debe ingresar su informacion
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
    registrarLog("Se agrego un usuario.");
    cout << "Usuario agregado exitosamente." << endl;                //y por la funcion REGISTRAR LOG, se ejecuta correctamente nuestro struct 
}

void buscarUsuario() {
    string busqueda;
    cout << "Ingrese el termino de busqueda: ";                       //ambos usuarios pueden utilizar esta función (ya sea admin o el estudiante)
    getline(cin, busqueda);

    limpiarConsola();
    cout << "Resultados de la busqueda:" << endl;
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

void modificarUsuario() {                               //el usuario del estudiante se encontrara por medio de su correo para posteriormente
    string correo;                                                          //realizar los cambios necesarios, siempre siguiendo el STRUCT Usuario 
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
            registrarLog("Se modifico un usuario.");                                //se combinan ambas funciones para poder guardar correctamente los cambios 
            cout << "Usuario modificado exitosamente." << endl;
            return;
        }
    }

    cout << "Usuario no encontrado." << endl;
}

void eliminarUsuario() {                            //con esta funcion, el admin puede ingresar el usuario que desea eliminar de la base de datos (el archivo .txt)
    string correo;
    cout << "Ingrese el correo del usuario que desea eliminar: ";
    getline(cin, correo);

    for (auto it = usuarios.begin(); it != usuarios.end(); ++it) {
        if (it->correo == correo) {
            usuarios.erase(it);
            guardarDatos();
            registrarLog("Se elimino un usuario.");
            cout << "Usuario eliminado exitosamente." << endl;          //una vez el usuario es encontrado, el sistema muestra si fue eliminado correctamente
            return;
        }
    }

    cout << "Usuario no encontrado." << endl;
}

void mostrarUsuarios() {    //Funcion para mostrar la informacion de los usuarios
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
void verCuotaMensual() {        //funcion para calcular, y mostrar la cuota al estudiante
    int meses;
    int mensualidad;

    cout << "Ingrese la duracion en meses de sus estudios: ";
    cin >> meses;

    mensualidad = 100; // la cuota mensual es de $100
    mensualidad *= meses;  //aqui se realiza la multiplicacion segun los meses que el estudiante va a cursar 

    cout << "La cuota mensual para " << meses << " meses es: $" << mensualidad << endl;     // se imprime la cuota para el usuario 
}

void registrarLog(const string& accion) {           //se utiliza para añadir nuevas entradas al archivo de registro, en caso de un nuevo registro por ejemplo
    ofstream log("log.txt", ios::app);
    if (log.is_open()) {
        log << accion << endl;
        log.close();
    } else {
        cout << "No se pudo abrir el archivo de registro." << endl;
    }
}

void mostrarCursosDisponibles() {                                   //esta funcion le muestra al estudiante todo lo que la academia posee en cuanto a material educativo 
    std::cout << "=== CURSOS DISPONIBLES ===" << std::endl;  
    cout << "1. Ingles como Segundo Idioma (principiantes)" << endl;
    cout << "2  Cursos Academicos (medio, avanzado)" << endl;
    cout << "3. Taller bilingue de arte y cultura (General)" << endl;
    cout << "4. Habilidades Interpersonales (principiante, medio)" << endl;
    cout << "5. Habilidades de Idioma Nativo (avanzado)" << endl;
} 
