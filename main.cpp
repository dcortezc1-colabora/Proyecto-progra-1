#include <iostream>
#include <string>
#include <vector>
#include <map>

#include "MySQLConexion.h"
#include "EloquentORM.h"

using namespace std;

// COLORES ANSI
#define RESET    "\033[0m"
#define ROJO     "\033[31m"
#define VERDE    "\033[32m"
#define AMARILLO "\033[33m"
#define AZUL     "\033[34m"
#define CYAN     "\033[36m"

// FUNCIONES AUXILIARES
void limpiar_pantalla() {
    system("cls");
}

void pausar() {
    system("pause");
}

void mostrar_titulo(string titulo) {
    cout << CYAN;
    cout << "\n=====================================\n";
    cout << " " << titulo << endl;
    cout << "=====================================\n";
    cout << RESET;
}

// CAMBIA TU CONTRASEÑA AQUÍ
MySQLConexion db("root", "Root123", "biblioteca_db");

// CLASE ESTUDIANTE
class Estudiante {
private:
    string nombre;
    string carnet;
    string correo;

public:
    void crear() {
        cout << AMARILLO << "\nCREAR ESTUDIANTE\n" << RESET;

        cin.ignore();

        cout << "Nombre: ";
        getline(cin, nombre);

        cout << "Carnet: ";
        getline(cin, carnet);

        cout << "Correo: ";
        getline(cin, correo);

        vector<string> columnas = {"nombre", "carnet", "correo"};

        EloquentORM estudiante(db, "estudiantes", columnas);

        estudiante.set("nombre", nombre);
        estudiante.set("carnet", carnet);
        estudiante.set("correo", correo);

        if (estudiante.create()) {
            cout << VERDE << "\nEstudiante guardado correctamente en MySQL.\n" << RESET;
        } else {
            cout << ROJO << "\nError al guardar estudiante.\n" << RESET;
        }
    }

    void listar() {
        cout << AMARILLO << "\nLISTADO DE ESTUDIANTES\n" << RESET;

        vector<string> columnas = {"nombre", "carnet", "correo"};

        EloquentORM estudiante(db, "estudiantes", columnas);

        vector<map<string, string>> registros = estudiante.getAll();

        for (auto &fila : registros) {
            cout << "\nID: " << fila["id"] << endl;
            cout << "Nombre: " << fila["nombre"] << endl;
            cout << "Carnet: " << fila["carnet"] << endl;
            cout << "Correo: " << fila["correo"] << endl;
        }
    }
};

// CLASE LIBRO
class Libro {
private:
    string titulo;
    string autor;
    string disponible;

public:
    void crear() {
        cout << AMARILLO << "\nCREAR LIBRO\n" << RESET;

        cin.ignore();

        cout << "Titulo: ";
        getline(cin, titulo);

        cout << "Autor: ";
        getline(cin, autor);

        disponible = "1";

        vector<string> columnas = {"titulo", "autor", "disponible"};

        EloquentORM libro(db, "libros", columnas);

        libro.set("titulo", titulo);
        libro.set("autor", autor);
        libro.set("disponible", disponible);

        if (libro.create()) {
            cout << VERDE << "\nLibro guardado correctamente en MySQL.\n" << RESET;
        } else {
            cout << ROJO << "\nError al guardar libro.\n" << RESET;
        }
    }

    void listar() {
        cout << AMARILLO << "\nLISTADO DE LIBROS\n" << RESET;

        vector<string> columnas = {"titulo", "autor", "disponible"};

        EloquentORM libro(db, "libros", columnas);

        vector<map<string, string>> registros = libro.getAll();

        for (auto &fila : registros) {
            cout << "\nID: " << fila["id"] << endl;
            cout << "Titulo: " << fila["titulo"] << endl;
            cout << "Autor: " << fila["autor"] << endl;

            if (fila["disponible"] == "1") {
                cout << VERDE << "Disponible: SI\n" << RESET;
            } else {
                cout << ROJO << "Disponible: NO\n" << RESET;
            }
        }
    }
};

// CLASE PRESTAMO
class Prestamo {
private:
    string estudianteId;
    string libroId;
    string fechaPrestamo;
    string fechaDevolucion;

public:
    void crear() {
        cout << AMARILLO << "\nCREAR PRESTAMO\n" << RESET;

        cin.ignore();

        cout << "ID del estudiante: ";
        getline(cin, estudianteId);

        cout << "ID del libro: ";
        getline(cin, libroId);

        cout << "Fecha prestamo (YYYY-MM-DD): ";
        getline(cin, fechaPrestamo);

        cout << "Fecha devolucion (YYYY-MM-DD): ";
        getline(cin, fechaDevolucion);

        vector<string> columnasLibro = {"titulo", "autor", "disponible"};
        EloquentORM libro(db, "libros", columnasLibro);

        if (!libro.find(stoi(libroId))) {
            cout << ROJO << "\nLibro no encontrado.\n" << RESET;
            return;
        }

        if (libro.get("disponible") == "0") {
            cout << ROJO << "\nEl libro ya esta prestado.\n" << RESET;
            return;
        }

        vector<string> columnas = {
            "estudiante_id",
            "libro_id",
            "fecha_prestamo",
            "fecha_devolucion"
        };

        EloquentORM prestamo(db, "prestamos", columnas);

        prestamo.set("estudiante_id", estudianteId);
        prestamo.set("libro_id", libroId);
        prestamo.set("fecha_prestamo", fechaPrestamo);
        prestamo.set("fecha_devolucion", fechaDevolucion);

        if (prestamo.create()) {
            libro.set("disponible", "0");
            libro.update();

            cout << VERDE << "\nPrestamo guardado correctamente en MySQL.\n" << RESET;
        } else {
            cout << ROJO << "\nError al guardar prestamo.\n" << RESET;
        }
    }

    void listar() {
        cout << AMARILLO << "\nLISTADO DE PRESTAMOS\n" << RESET;

        string consulta =
            "SELECT prestamos.id, estudiantes.nombre, libros.titulo, "
            "prestamos.fecha_prestamo, prestamos.fecha_devolucion "
            "FROM prestamos "
            "INNER JOIN estudiantes ON prestamos.estudiante_id = estudiantes.id "
            "INNER JOIN libros ON prestamos.libro_id = libros.id";

        vector<string> columnas = {
            "id",
            "nombre",
            "titulo",
            "fecha_prestamo",
            "fecha_devolucion"
        };

        EloquentORM prestamo(db, "prestamos", columnas);

        vector<map<string, string>> registros = prestamo.raw(consulta).getAll();

        for (auto &fila : registros) {
            cout << "\nID: " << fila["id"] << endl;
            cout << "Estudiante: " << fila["nombre"] << endl;
            cout << "Libro: " << fila["titulo"] << endl;
            cout << "Fecha prestamo: " << fila["fecha_prestamo"] << endl;
            cout << "Fecha devolucion: " << fila["fecha_devolucion"] << endl;
        }
    }
};

// MENUS
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

        switch (opcion) {
            case 1:
                estudiante.crear();
                pausar();
                break;
            case 2:
                estudiante.listar();
                pausar();
                break;
        }

    } while (opcion != 3);
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

        switch (opcion) {
            case 1:
                libro.crear();
                pausar();
                break;
            case 2:
                libro.listar();
                pausar();
                break;
        }

    } while (opcion != 3);
}

void menu_prestamos() {
    int opcion;
    Prestamo prestamo;

    do {
        limpiar_pantalla();
        mostrar_titulo("GESTION DE PRESTAMOS");

        cout << "1. Crear prestamo\n";
        cout << "2. Listar prestamos\n";
        cout << "3. Volver\n";

        cout << "\nSeleccione una opcion: ";
        cin >> opcion;

        switch (opcion) {
            case 1:
                prestamo.crear();
                pausar();
                break;
            case 2:
                prestamo.listar();
                pausar();
                break;
        }

    } while (opcion != 3);
}

void menu_principal() {
    int opcion;

    do {
        limpiar_pantalla();
        mostrar_titulo("SISTEMA DE PRESTAMO DE LIBROS");

        cout << "1. Gestion de estudiantes\n";
        cout << "2. Gestion de libros\n";
        cout << "3. Gestion de prestamos\n";
        cout << "4. Salir\n";

        cout << "\nSeleccione una opcion: ";
        cin >> opcion;

        switch (opcion) {
            case 1:
                menu_estudiantes();
                break;
            case 2:
                menu_libros();
                break;
            case 3:
                menu_prestamos();
                break;
            case 4:
                cout << VERDE << "\nSaliendo del sistema...\n" << RESET;
                break;
            default:
                cout << ROJO << "\nOpcion invalida.\n" << RESET;
                pausar();
        }

    } while (opcion != 4);
}

int main() {
    if (!db.open()) {
        cout << ROJO << "Error conectando a MySQL.\n" << RESET;
        return 1;
    }

    menu_principal();

    return 0;
}