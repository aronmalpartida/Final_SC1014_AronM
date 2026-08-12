// --------------------------------------------------
// Nombre: Aron Malpartida
// Fecha: 01/08/2026
// Proyecto: Bóveda Digital - Convertidor de Coordenadas
// --------------------------------------------------

#ifndef REGISTRO_H
#define REGISTRO_H

#include <string>
#include "Coordenada.h"

class Registro {
private:
    int id;
    std::string nombre;
    Coordenada topo;
    double lat;
    double lon;

public:
    Registro() : id(0), nombre(""), topo{0.0, 0.0, 0.0, 18, 'S'}, lat(0.0), lon(0.0) {}

    Registro(int id, const std::string& nom, Coordenada c, double lat, double lon)
        : id(id), nombre(nom), topo(c), lat(lat), lon(lon) {}

    int getId() const { return id; }
    std::string getNombre() const { return nombre; }
    Coordenada getTopo() const { return topo; }
    double getLat() const { return lat; }
    double getLon() const { return lon; }

    void setId(int nuevoId) { id = nuevoId; }
    void setNombre(const std::string& nuevoNombre) { nombre = nuevoNombre; }
    void setTopo(const Coordenada& nuevaTopo) { topo = nuevaTopo; }
    void setLat(double nuevaLat) { lat = nuevaLat; }
    void setLon(double nuevaLon) { lon = nuevaLon; }
};

#endif // REGISTRO_H