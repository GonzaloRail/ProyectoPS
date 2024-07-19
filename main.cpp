
#include "biblioteca.h"

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <stdexcept>
#include <ctime>
#include <limits>

// ... (mantén las estructuras y la clase Biblioteca como estaban antes)

void mostrarMenuPrincipal() {
    std::cout << "\n--- MENU PRINCIPAL ---\n";
    std::cout << "1. Gestion de Registros\n";
    std::cout << "2. Gestion de Usuarios\n";
    std::cout << "3. Gestion de Prestamos\n";
    std::cout << "0. Salir\n";
    std::cout << "Seleccione una opcion: ";
}

void mostrarMenuRegistros() {
    std::cout << "\n--- MENU DE REGISTROS ---\n";
    std::cout << "1. Agregar Registro\n";
    std::cout << "2. Eliminar Registro\n";
    std::cout << "3. Buscar Registro\n";
    std::cout << "4. Actualizar Registro\n";
    std::cout << "5. Listar Registros\n";
    std::cout << "6. Guardar en Fichero\n";
    std::cout << "7. Cargar desde Fichero\n";
    std::cout << "0. Volver al Menu Principal\n";
    std::cout << "Seleccione una opcion: ";
}

void mostrarMenuUsuarios() {
    std::cout << "\n--- MENU DE USUARIOS ---\n";
    std::cout << "1. Agregar Usuario\n";
    std::cout << "2. Eliminar Usuario\n";
    std::cout << "3. Listar Usuarios\n";
    std::cout << "0. Volver al Menu Principal\n";
    std::cout << "Seleccione una opcion: ";
}

void mostrarMenuPrestamos() {
    std::cout << "\n--- MENU DE PRESTAMOS ---\n";
    std::cout << "1. Establecer Prestamos\n";
    std::cout << "2. Establecer Devolución\n";
    std::cout << "3. Listar Prestamos\n";
    std::cout << "0. Volver al Menu Principal\n";
    std::cout << "Seleccione una opcion: ";
}

void gestionRegistros(Biblioteca& biblioteca) {
    int opcion;
    do {
        mostrarMenuRegistros();
        std::cin >> opcion;
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        switch(opcion) {
            case 1: {
                Registro reg;
                std::cout << "Ingrese codigo: ";
                std::cin >> reg.codigo;
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                std::cout << "Ingrese nombre: ";
                std::getline(std::cin, reg.nombre);
                std::cout << "Ingrese autor: ";
                std::getline(std::cin, reg.autor);
                std::cout << "Ingrese año de publicacion: ";
                std::cin >> reg.anioPublicacion;
                std::cout << "Ingrese precio: ";
                std::cin >> reg.precio;
                biblioteca.agregarRegistro(reg);
                std::cout << "Registro agregado con exito.\n";
                break;
            }
            case 2: {
                int codigo;
                std::cout << "Ingrese el codigo del registro a eliminar: ";
                std::cin >> codigo;
                try {
                    biblioteca.eliminarRegistro(codigo);
                    std::cout << "Registro eliminado con exito.\n";
                } catch (const std::exception& e) {
                    std::cout << "Error: " << e.what() << std::endl;
                }
                break;
            }
            case 3: {
                int codigo;
                std::cout << "Ingrese el codigo del registro a buscar: ";
                std::cin >> codigo;
                try {
                    Registro reg = biblioteca.buscarRegistro(codigo);
                    std::cout << "Registro encontrado:\n";
                    std::cout << "Codigo: " << reg.codigo << ", Nombre: " << reg.nombre << ", Autor: " << reg.autor
                              << ", Año: " << reg.anioPublicacion << ", Precio: " << reg.precio << std::endl;
                } catch (const std::exception& e) {
                    std::cout << "Error: " << e.what() << std::endl;
                }
                break;
            }
            case 4: {
                Registro reg;
                std::cout << "Ingrese el codigo del registro a actualizar: ";
                std::cin >> reg.codigo;
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                std::cout << "Ingrese nuevo nombre: ";
                std::getline(std::cin, reg.nombre);
                std::cout << "Ingrese nuevo autor: ";
                std::getline(std::cin, reg.autor);
                std::cout << "Ingrese nuevo año de publicacion: ";
                std::cin >> reg.anioPublicacion;
                std::cout << "Ingrese nuevo precio: ";
                std::cin >> reg.precio;
                try {
                    biblioteca.actualizarRegistro(reg);
                    std::cout << "Registro actualizado con exito.\n";
                } catch (const std::exception& e) {
                    std::cout << "Error: " << e.what() << std::endl;
                }
                break;
            }
            case 5:
                biblioteca.listarRegistros();
                break;
            case 6: {
                std::string nombreFichero;
                std::cout << "Ingrese el nombre del fichero para guardar: ";
                std::cin >> nombreFichero;
                try {
                    biblioteca.guardarEnFichero(nombreFichero);
                    std::cout << "Registros guardados en fichero con exito.\n";
                } catch (const std::exception& e) {
                    std::cout << "Error al guardar en fichero: " << e.what() << std::endl;
                }
                break;
            }
            case 7: {
                std::string nombreFichero;
                std::cout << "Ingrese el nombre del fichero para cargar: ";
                std::cin >> nombreFichero;
                try {
                    biblioteca.cargarDesdeFichero(nombreFichero);
                    std::cout << "Registros cargados desde fichero con exito.\n";
                } catch (const std::exception& e) {
                    std::cout << "Error al cargar desde fichero: " << e.what() << std::endl;
                }
                break;
            }
            case 0:
                std::cout << "Volviendo al menu principal...\n";
                break;
            default:
                std::cout << "Opcion no valida. Intente de nuevo.\n";
        }
    } while (opcion != 0);
}

void gestionUsuarios(Biblioteca& biblioteca) {
    int opcion;
    do {
        mostrarMenuUsuarios();
        std::cin >> opcion;
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        switch(opcion) {
            case 1: {
                Usuario user;
                std::cout << "Ingrese DNI: ";
                std::getline(std::cin, user.dni);
                std::cout << "Ingrese nombre: ";
                std::getline(std::cin, user.nombre);
                std::cout << "Ingrese email: ";
                std::getline(std::cin, user.email);
                std::cout << "Ingrese telefono: ";
                std::getline(std::cin, user.telefono);
                biblioteca.agregarUsuario(user);
                std::cout << "Usuario agregado con exito.\n";
                break;
            }
            case 2: {
                std::string dni;
                std::cout << "Ingrese el DNI del usuario a eliminar: ";
                std::getline(std::cin, dni);
                try {
                    biblioteca.eliminarUsuario(dni);
                    std::cout << "Usuario eliminado con exito.\n";
                } catch (const std::exception& e) {
                    std::cout << "Error: " << e.what() << std::endl;
                }
                break;
            }
            case 3:
                biblioteca.listarUsuarios();
                break;
            case 0:
                std::cout << "Volviendo al menu principal...\n";
                break;
            default:
                std::cout << "Opcion no valida. Intente de nuevo.\n";
        }
    } while (opcion != 0);
}

void gestionPrestamos(Biblioteca& biblioteca) {
    int opcion;
    do {
        mostrarMenuPrestamos();
        std::cin >> opcion;
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        switch(opcion) {
            case 1: {
                int codigoRegistro;
                std::string dniUsuario;
                std::cout << "Ingrese el codigo del registro: ";
                std::cin >> codigoRegistro;
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                std::cout << "Ingrese el DNI del usuario: ";
                std::getline(std::cin, dniUsuario);
                try {
                    biblioteca.establecerPrestamo(codigoRegistro, dniUsuario);
                    std::cout << "prestamos establecido con exito.\n";
                } catch (const std::exception& e) {
                    std::cout << "Error: " << e.what() << std::endl;
                }
                break;
            }
            case 2: {
                int codigoRegistro;
                std::string dniUsuario;
                std::cout << "Ingrese el codigo del registro: ";
                std::cin >> codigoRegistro;
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                std::cout << "Ingrese el DNI del usuario: ";
                std::getline(std::cin, dniUsuario);
                try {
                    biblioteca.establecerDevolucion(codigoRegistro, dniUsuario);
                    std::cout << "Devolución establecida con exito.\n";
                } catch (const std::exception& e) {
                    std::cout << "Error: " << e.what() << std::endl;
                }
                break;
            }
            case 3:
                biblioteca.listarPrestamos();
                break;
            case 0:
                std::cout << "Volviendo al menu principal...\n";
                break;
            default:
                std::cout << "Opcion no valida. Intente de nuevo.\n";
        }
    } while (opcion != 0);
}

int main() {
    Biblioteca biblioteca;
    int opcion;

    do {
        mostrarMenuPrincipal();
        std::cin >> opcion;

        switch(opcion) {
            case 1:
                gestionRegistros(biblioteca);
                break;
            case 2:
                gestionUsuarios(biblioteca);
                break;
            case 3:
                gestionPrestamos(biblioteca);
                break;
            case 0:
                std::cout << "Saliendo del programa...\n";
                break;
            default:
                std::cout << "Opcion no valida. Intente de nuevo.\n";
        }
    } while (opcion != 0);

    return 0;
}