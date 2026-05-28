#include <iostream>
#include <string>
#include <vector>
#include <map>

#include "MySQLConexion.h"
#include "EloquentORM.h"

using namespace std;

#define RESET    "\033[0m"
#define ROJO     "\033[31m"
#define VERDE    "\033[32m"
#define AMARILLO "\033[33m"
#define CYAN     "\033[36m"

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

// CAMBIA TU CONTRASEÑA
MySQLConexion db("root", "Root123", "biblioteca_db");

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
            cout << VERDE << "\nEstudiante guardado correctamente.\n" << RESET;
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

    void actualizar() {
        int id;
        cout << AMARILLO << "\nACTUALIZAR ESTUDIANTE\n" << RESET;

        cout << "ID del estudiante: ";
        cin >> id;
        cin.ignore();

        vector<string> columnas = {"nombre", "carnet", "correo"};
        EloquentORM estudiante(db, "estudiantes", columnas);

        if (!estudiante.find(id)) {
            cout << ROJO << "\nEstudiante no encontrado.\n" << RESET;
            return;
        }

        cout << "Nuevo nombre: ";
        getline(cin, nombre);

        cout << "Nuevo carnet: ";
        getline(cin, carnet);

        cout << "Nuevo correo: ";
        getline(cin, correo);

        estudiante.set("nombre", nombre);
        estudiante.set("carnet", carnet);
        estudiante.set("correo", correo);

        if (estudiante.update()) {
            cout << VERDE << "\nEstudiante actualizado correctamente.\n" << RESET;
        } else {
            cout << ROJO << "\nError al actualizar estudiante.\n" << RESET;
        }
    }

    void eliminar() {
        int id;
        cout << AMARILLO << "\nELIMINAR ESTUDIANTE\n" << RESET;

        cout << "ID del estudiante: ";
        cin >> id;

        vector<string> columnas = {"nombre", "carnet", "correo"};
        EloquentORM estudiante(db, "estudiantes", columnas);

        if (!estudiante.find(id)) {
            cout << ROJO << "\nEstudiante no encontrado.\n" << RESET;
            return;
        }

        if (estudiante.remove()) {
            cout << VERDE << "\nEstudiante eliminado correctamente.\n" << RESET;
        } else {
            cout << ROJO << "\nNo se pudo eliminar. Puede tener prestamos asociados.\n" << RESET;
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
            cout << VERDE << "\nLibro guardado correctamente.\n" << RESET;
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

    void actualizar() {
        int id;
        cout << AMARILLO << "\nACTUALIZAR LIBRO\n" << RESET;

        cout << "ID del libro: ";
        cin >> id;
        cin.ignore();

        vector<string> columnas = {"titulo", "autor", "disponible"};
        EloquentORM libro(db, "libros", columnas);

        if (!libro.find(id)) {
            cout << ROJO << "\nLibro no encontrado.\n" << RESET;
            return;
        }

        cout << "Nuevo titulo: ";
        getline(cin, titulo);

        cout << "Nuevo autor: ";
        getline(cin, autor);

        libro.set("titulo", titulo);
        libro.set("autor", autor);

        if (libro.update()) {
            cout << VERDE << "\nLibro actualizado correctamente.\n" << RESET;
        } else {
            cout << ROJO << "\nError al actualizar libro.\n" << RESET;
        }
    }

    void eliminar() {
        int id;
        cout << AMARILLO << "\nELIMINAR LIBRO\n" << RESET;

        cout << "ID del libro: ";
        cin >> id;

        vector<string> columnas = {"titulo", "autor", "disponible"};
        EloquentORM libro(db, "libros", columnas);

        if (!libro.find(id)) {
            cout << ROJO << "\nLibro no encontrado.\n" << RESET;
            return;
        }

        if (libro.remove()) {
            cout << VERDE << "\nLibro eliminado correctamente.\n" << RESET;
        } else {
            cout << ROJO << "\nNo se pudo eliminar. Puede tener prestamos asociados.\n" << RESET;
        }
    }
};

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

            cout << VERDE << "\nPrestamo guardado correctamente.\n" << RESET;
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

    void eliminar() {
        int id;
        cout << AMARILLO << "\nELIMINAR PRESTAMO\n" << RESET;

        cout << "ID del prestamo: ";
        cin >> id;

        vector<string> columnas = {
            "estudiante_id",
            "libro_id",
            "fecha_prestamo",
            "fecha_devolucion"
        };

        EloquentORM prestamo(db, "prestamos", columnas);

        if (!prestamo.find(id)) {
            cout << ROJO << "\nPrestamo no encontrado.\n" << RESET;
            return;
        }

        string idLibro = prestamo.get("libro_id");

        if (prestamo.remove()) {
            vector<string> columnasLibro = {"titulo", "autor", "disponible"};
            EloquentORM libro(db, "libros", columnasLibro);

            if (libro.find(stoi(idLibro))) {
                libro.set("disponible", "1");
                libro.update();
            }

            cout << VERDE << "\nPrestamo eliminado correctamente.\n" << RESET;
            cout << VERDE << "El libro fue marcado como disponible.\n" << RESET;
        } else {
            cout << ROJO << "\nError al eliminar prestamo.\n" << RESET;
        }
    }
};

void menu_estudiantes() {
    int opcion;
    Estudiante estudiante;

    do {
        limpiar_pantalla();
        mostrar_titulo("GESTION DE ESTUDIANTES");

        cout << "1. Crear estudiante\n";
        cout << "2. Listar estudiantes\n";
        cout << "3. Actualizar estudiante\n";
        cout << "4. Eliminar estudiante\n";
        cout << "5. Volver\n";

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
            case 3:
                estudiante.actualizar();
                pausar();
                break;
            case 4:
                estudiante.eliminar();
                pausar();
                break;
        }

    } while (opcion != 5);
}

void menu_libros() {
    int opcion;
    Libro libro;

    do {
        limpiar_pantalla();
        mostrar_titulo("GESTION DE LIBROS");

        cout << "1. Crear libro\n";
        cout << "2. Listar libros\n";
        cout << "3. Actualizar libro\n";
        cout << "4. Eliminar libro\n";
        cout << "5. Volver\n";

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
            case 3:
                libro.actualizar();
                pausar();
                break;
            case 4:
                libro.eliminar();
                pausar();
                break;
        }

    } while (opcion != 5);
}

void menu_prestamos() {
    int opcion;
    Prestamo prestamo;

    do {
        limpiar_pantalla();
        mostrar_titulo("GESTION DE PRESTAMOS");

        cout << "1. Crear prestamo\n";
        cout << "2. Listar prestamos\n";
        cout << "3. Eliminar prestamo\n";
        cout << "4. Volver\n";

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
            case 3:
                prestamo.eliminar();
                pausar();
                break;
        }

    } while (opcion != 4);
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