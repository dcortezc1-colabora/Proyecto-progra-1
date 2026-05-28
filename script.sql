CREATE DATABASE IF NOT EXISTS biblioteca_db;

USE biblioteca_db;

-- TABLA ESTUDIANTES
CREATE TABLE estudiantes (

    id INT AUTO_INCREMENT PRIMARY KEY,

    nombre VARCHAR(100) NOT NULL,

    carnet VARCHAR(50) NOT NULL,

    correo VARCHAR(100) NOT NULL
);

-- TABLA LIBROS
CREATE TABLE libros (

    id INT AUTO_INCREMENT PRIMARY KEY,

    titulo VARCHAR(100) NOT NULL,

    autor VARCHAR(100) NOT NULL,

    disponible TINYINT(1) DEFAULT 1
);

-- TABLA PRESTAMOS
CREATE TABLE prestamos (

    id INT AUTO_INCREMENT PRIMARY KEY,

    estudiante_id INT NOT NULL,

    libro_id INT NOT NULL,

    fecha_prestamo DATE NOT NULL,

    fecha_devolucion DATE NOT NULL,

    CONSTRAINT fk_estudiante
        FOREIGN KEY (estudiante_id)
        REFERENCES estudiantes(id),

    CONSTRAINT fk_libro
        FOREIGN KEY (libro_id)
        REFERENCES libros(id)
);