#ifndef BIBLIOTECA_H
#define BIBLIOTECA_H

#include <vector>
#include <string>

struct Registro {
    int codigo;
    std::string nombre;
    std::string autor;
    int anioPublicacion;
    double precio;
};

struct Usuario {
    std::string dni;
    std::string nombre;
    std::string email;
    std::string telefono;
};

struct Prestamo {
    int codigoRegistro;
    std::string dniUsuario;
    std::string fechaPrestamo;
    std::string fechaDevolucion;
};

class Biblioteca {
private:
    std::vector<Registro> registros;
    std::vector<Usuario> usuarios;
    std::vector<Prestamo> prestamos;
    
public:
    // Funciones para Registro
    void agregarRegistro(const Registro& reg);
    void eliminarRegistro(int codigo);
    Registro buscarRegistro(int codigo) const;
    void actualizarRegistro(const Registro& reg);
    void listarRegistros() const;
    
    // Funciones para Usuario
    void agregarUsuario(const Usuario& user);
    void eliminarUsuario(const std::string& dni);
    void listarUsuarios() const;
    
    // Funciones para Préstamo
    void establecerPrestamo(int codigoRegistro, const std::string& dniUsuario);
    void establecerDevolucion(int codigoRegistro, const std::string& dniUsuario);
    void listarPrestamos() const;
    
    // Funciones para manejo de ficheros
    void guardarEnFichero(const std::string& nombreFichero) const;
    void cargarDesdeFichero(const std::string& nombreFichero);
};

#endif // BIBLIOTECA_H