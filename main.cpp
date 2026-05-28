#include <iostream>
#include <string>
#include <vector>
#include <map>

#include "MySQLConexion.h"
#include "EloquentORM.h"

using namespace std;

// FUNCION LIMPIAR PANTALLA
void limpiar_pantalla() {

    system("cls");
}

// FUNCION PAUSA
void pausar() {

    system("pause");
}

// TITULO
void mostrar_titulo(string titulo) {

    cout << "\n=====================================\n";
    cout << " " << titulo << endl;
    cout << "=====================================\n";
}

// CONEXION MYSQL
MySQLConexion db("root", "Root123", "biblioteca_db");

// CLASE ESTUDIANTE
class Estudiante {

private:

    string nombre;
    string carnet;
    string correo;

public:

    Estudiante() {}

    void crear() {

        cout << "\nCREAR ESTUDIANTE\n";

        cin.ignore();

        cout << "Nombre: ";
        getline(cin, nombre);

        cout << "Carnet: ";
        getline(cin, carnet);

        cout << "Correo: ";
        getline(cin, correo);

        vector<string> columnas = {
            "nombre",
            "carnet",
            "correo"
        };

        EloquentORM estudiante(db, "estudiantes", columnas);

        estudiante.set("nombre", nombre);
        estudiante.set("carnet", carnet);
        estudiante.set("correo", correo);

        if(estudiante.create()) {

            cout << "\nEstudiante guardado correctamente en MySQL.\n";

        } else {

            cout << "\nError al guardar estudiante.\n";
        }
    }

    void listar() {

        cout << "\nLISTADO DE ESTUDIANTES\n";

        vector<string> columnas = {
            "nombre",
            "carnet",
            "correo"
        };

        EloquentORM estudiante(db, "estudiantes", columnas);

        vector< map<string, string> > registros = estudiante.getAll();

        for(auto &fila : registros) {

            cout << "\nID: " << fila["id"] << endl;
            cout << "Nombre: " << fila["nombre"] << endl;
            cout << "Carnet: " << fila["carnet"] << endl;
            cout << "Correo: " << fila["correo"] << endl;
        }
    }
};

class Libro {

private:
    string titulo;
    string autor;
    string disponible;

public:

    void crear() {
        cout << "\nCREAR LIBRO\n";

        cin.ignore();

        cout << "Titulo: ";
        getline(cin, titulo);

        cout << "Autor: ";
        getline(cin, autor);

        disponible = "1";

        vector<string> columnas = {
            "titulo",
            "autor",
            "disponible"
        };

        EloquentORM libro(db, "libros", columnas);

        libro.set("titulo", titulo);
        libro.set("autor", autor);
        libro.set("disponible", disponible);

        if(libro.create()) {
            cout << "\nLibro guardado correctamente en MySQL.\n";
        } else {
            cout << "\nError al guardar libro.\n";
        }
    }

    void listar() {
        cout << "\nLISTADO DE LIBROS\n";

        vector<string> columnas = {
            "titulo",
            "autor",
            "disponible"
        };

        EloquentORM libro(db, "libros", columnas);

        vector< map<string, string> > registros = libro.getAll();

        for(auto &fila : registros) {
            cout << "\nID: " << fila["id"] << endl;
            cout << "Titulo: " << fila["titulo"] << endl;
            cout << "Autor: " << fila["autor"] << endl;
            cout << "Disponible: " << fila["disponible"] << endl;
        }
    }
};

// MENU ESTUDIANTES
void menu_estudiantes() {

    int opcion;

    Estudiante estudiante;

    do {

        limpiar_pantalla();

        mostrar_titulo("GESTION DE ESTUDIANTES");

        cout << "1. Crear estudiante\n";
        cout << "2. Listar estudiantes\n";
        cout << "3. Volver\n";

        cout << "\nSeleccione una opcion: ";
        cin >> opcion;

        switch(opcion) {

            case 1:
                estudiante.crear();
                pausar();
                break;

            case 2:
                estudiante.listar();
                pausar();
                break;
        }

    } while(opcion != 3);
}

void menu_libros() {

    int opcion;
    Libro libro;

    do {
        limpiar_pantalla();

        mostrar_titulo("GESTION DE LIBROS");

        cout << "1. Crear libro\n";
        cout << "2. Listar libros\n";
        cout << "3. Volver\n";

        cout << "\nSeleccione una opcion: ";
        cin >> opcion;

        switch(opcion) {
            case 1:
                libro.crear();
                pausar();
                break;

            case 2:
                libro.listar();
                pausar();
                break;
        }

    } while(opcion != 3);
}

// MENU PRINCIPAL
void menu_principal() {

    int opcion;

    do {

        limpiar_pantalla();

        mostrar_titulo("SISTEMA DE PRESTAMO DE LIBROS");

        cout << "1. Gestion de estudiantes\n";
        cout << "2. Gestion de libros\n";
        cout << "3. Salir\n";

        cout << "\nSeleccione una opcion: ";
        cin >> opcion;

        switch(opcion) {

            case 1:
                menu_estudiantes();
                break;

            case 2:
                menu_libros();
                break;

            case 3:
                cout << "\nSaliendo del sistema...\n";
                break;

            default:
                cout << "\nOpcion invalida.\n";
                pausar();
        }

    } while(opcion != 3);
}

int main() {

    if(!db.open()) {

        cout << "Error conectando a MySQL.\n";
        return 1;
    }

    menu_principal();

    return 0;
}