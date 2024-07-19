#include "biblioteca.h"
#include <algorithm>
#include <fstream>
#include <stdexcept>
#include <ctime>
#include <iostream>

void Biblioteca::agregarRegistro(const Registro& reg) {
    registros.push_back(reg);
}

void Biblioteca::eliminarRegistro(int codigo) {
    auto it = std::find_if(registros.begin(), registros.end(),
                           [codigo](const Registro& r) { return r.codigo == codigo; });
    if (it != registros.end()) {
        registros.erase(it);
    } else {
        throw std::runtime_error("Registro no encontrado");
    }
}

Registro Biblioteca::buscarRegistro(int codigo) const {
    auto it = std::find_if(registros.begin(), registros.end(),
                           [codigo](const Registro& r) { return r.codigo == codigo; });
    if (it != registros.end()) {
        return *it;
    } else {
        throw std::runtime_error("Registro no encontrado");
    }
}

void Biblioteca::actualizarRegistro(const Registro& reg) {
    auto it = std::find_if(registros.begin(), registros.end(),
                           [&reg](const Registro& r) { return r.codigo == reg.codigo; });
    if (it != registros.end()) {
        *it = reg;
    } else {
        throw std::runtime_error("Registro no encontrado");
    }
}

void Biblioteca::listarRegistros() const {
    for (const auto& reg : registros) {
        std::cout << "Código: " << reg.codigo << ", Nombre: " << reg.nombre << ", Autor: " << reg.autor
                  << ", Año: " << reg.anioPublicacion << ", Precio: " << reg.precio << std::endl;
    }
}

void Biblioteca::agregarUsuario(const Usuario& user) {
    usuarios.push_back(user);
}

void Biblioteca::eliminarUsuario(const std::string& dni) {
    auto it = std::find_if(usuarios.begin(), usuarios.end(),
                           [&dni](const Usuario& u) { return u.dni == dni; });
    if (it != usuarios.end()) {
        usuarios.erase(it);
    } else {
        throw std::runtime_error("Usuario no encontrado");
    }
}

void Biblioteca::listarUsuarios() const {
    for (const auto& user : usuarios) {
        std::cout << "DNI: " << user.dni << ", Nombre: " << user.nombre
                  << ", Email: " << user.email << ", Teléfono: " << user.telefono << std::endl;
    }
}

void Biblioteca::establecerPrestamo(int codigoRegistro, const std::string& dniUsuario) {
    Prestamo prestamo;
    prestamo.codigoRegistro = codigoRegistro;
    prestamo.dniUsuario = dniUsuario;
    
    time_t now = time(0);
    char* dt = ctime(&now);
    prestamo.fechaPrestamo = std::string(dt);
    prestamo.fechaDevolucion = "Pendiente";
    
    prestamos.push_back(prestamo);
}

void Biblioteca::establecerDevolucion(int codigoRegistro, const std::string& dniUsuario) {
    auto it = std::find_if(prestamos.begin(), prestamos.end(),
                           [codigoRegistro, &dniUsuario](const Prestamo& p) {
                               return p.codigoRegistro == codigoRegistro && p.dniUsuario == dniUsuario;
                           });
    if (it != prestamos.end()) {
        time_t now = time(0);
        char* dt = ctime(&now);
        it->fechaDevolucion = std::string(dt);
    } else {
        throw std::runtime_error("Préstamo no encontrado");
    }
}

void Biblioteca::listarPrestamos() const {
    for (const auto& prestamo : prestamos) {
        std::cout << "Código Registro: " << prestamo.codigoRegistro
                  << ", DNI Usuario: " << prestamo.dniUsuario
                  << ", Fecha Préstamo: " << prestamo.fechaPrestamo
                  << ", Fecha Devolución: " << prestamo.fechaDevolucion << std::endl;
    }
}

void Biblioteca::guardarEnFichero(const std::string& nombreFichero) const {
    std::ofstream file(nombreFichero);
    if (file.is_open()) {
        for (const auto& reg : registros) {
            file << reg.codigo << "," << reg.nombre << "," << reg.autor << ","
                 << reg.anioPublicacion << "," << reg.precio << "\n";
        }
        file.close();
    } else {
        throw std::runtime_error("No se pudo abrir el archivo para escritura");
    }
}

void Biblioteca::cargarDesdeFichero(const std::string& nombreFichero) {
    std::ifstream file(nombreFichero);
    if (file.is_open()) {
        registros.clear();
        std::string line;
        while (std::getline(file, line)) {
            Registro reg;
            size_t pos = 0;
            std::string token;
            int i = 0;
            while ((pos = line.find(",")) != std::string::npos) {
                token = line.substr(0, pos);
                switch(i) {
                    case 0: reg.codigo = std::stoi(token); break;
                    case 1: reg.nombre = token; break;
                    case 2: reg.autor = token; break;
                    case 3: reg.anioPublicacion = std::stoi(token); break;
                }
                line.erase(0, pos + 1);
                i++;
            }
            reg.precio = std::stod(line);
            registros.push_back(reg);
        }
        file.close();
    } else {
        throw std::runtime_error("No se pudo abrir el archivo para lectura");
    }
}