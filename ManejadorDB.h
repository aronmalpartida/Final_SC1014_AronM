// --------------------------------------------------
// Nombre: Aron Malpartida
// Fecha: 01/08/2026
// Proyecto: Bóveda Digital - Convertidor de Coordenadas
// --------------------------------------------------

#ifndef MANEJADORDB_H
#define MANEJADORDB_H

#include <vector>
#include <iostream>
#include <cmath>
#include <iomanip>
#include <fstream>
#include "Registro.h"

class ManejadorDB {
private:
    std::vector<Registro> lista;
    int contadorId = 1;

    void convertirUTMExacto(double x, double y, int zona, char hemisferio, double& latitud, double& longitud) const {
        const double a = 6378137.0;
        const double ee = 0.00669437999014;
        const double k0 = 0.9996;

        double x_rel = x - 500000.0;
        double y_rel = (hemisferio == 'S' || hemisferio == 's') ? y - 10000000.0 : y;

        double m = y_rel / k0;
        double mu = m / (a * (1.0 - ee / 4.0 - 3.0 * ee * ee / 64.0 - 5.0 * ee * ee * ee / 256.0));

        double e1 = (1.0 - std::sqrt(1.0 - ee)) / (1.0 + std::sqrt(1.0 - ee));

        double phi1 = mu + (3.0 * e1 / 2.0 - 27.0 * std::pow(e1, 3) / 32.0) * std::sin(2.0 * mu)
                        + (21.0 * e1 * e1 / 16.0 - 55.0 * std::pow(e1, 4) / 32.0) * std::sin(4.0 * mu)
                        + (151.0 * std::pow(e1, 3) / 96.0) * std::sin(6.0 * mu);

        double sin_phi1 = std::sin(phi1);
        double cos_phi1 = std::cos(phi1);
        double tan_phi1 = std::tan(phi1);

        double n1 = a / std::sqrt(1.0 - ee * sin_phi1 * sin_phi1);
        double r1 = a * (1.0 - ee) / std::pow(1.0 - ee * sin_phi1 * sin_phi1, 1.5);
        double t1 = tan_phi1 * tan_phi1;
        double c1 = (ee / (1.0 - ee)) * cos_phi1 * cos_phi1;

        double d = x_rel / (n1 * k0);

        double lat_rad = phi1 - (n1 * tan_phi1 / r1) * (d * d / 2.0 - (5.0 + 3.0 * t1 + 10.0 * c1 - 4.0 * c1 * c1 - 9.0 * (ee / (1.0 - ee))) * std::pow(d, 4) / 24.0
                        + (61.0 + 90.0 * t1 + 298.0 * c1 + 45.0 * t1 * t1 - 252.0 * (ee / (1.0 - ee)) - 3.0 * c1 * c1) * std::pow(d, 6) / 720.0);

        double central_meridian = (zona - 1) * 6 - 180 + 3;
        double lon_rad = (d - (1.0 + 2.0 * t1 + c1) * std::pow(d, 3) / 6.0
                        + (5.0 - 2.0 * c1 + 28.0 * t1 - 3.0 * c1 * c1 + 8.0 * (ee / (1.0 - ee)) + 24.0 * t1 * t1) * std::pow(d, 5) / 120.0) / cos_phi1;

        const double rad2deg = 180.0 / 3.14159265358979323846;
        latitud = lat_rad * rad2deg;
        longitud = central_meridian + (lon_rad * rad2deg);
    }

public:
      void insertar(std::string nombre, double e, double n, double z, int zona, char hemisferio) {
        Coordenada c{e, n, z, zona, hemisferio};
        double lat = 0.0, lon = 0.0;

        convertirUTMExacto(e, n, zona, hemisferio, lat, lon);

        lista.push_back(Registro(contadorId++, nombre, c, lat, lon));
        std::cout << "\n[+] Punto UTM (" << zona << (char)toupper(hemisferio) << ") procesado y guardado en RAM.\n";
    }

    void listar() const {
        if (lista.empty()) {
            std::cout << "\n[!] No hay puntos registrados en memoria.\n";
            return;
        }
        std::cout << "\n-------------------------------- LISTA DE PUNTOS CONVERTIDOS (WGS84) --------------------------------\n";
        std::cout << std::fixed << std::setprecision(6);
        for (const auto& p : lista) {
            std::cout << "ID: " << p.getId() << " | Nombre: " << p.getNombre()
                      << " | Zona: " << p.getTopo().zona << p.getTopo().hemisferio
                      << " | Este: " << p.getTopo().este << "m, Norte: " << p.getTopo().norte << "m"
                      << " -> Lat: " << p.getLat() << "°, Lon: " << p.getLon() << "°\n";
        }
        std::cout << "----------------------------------------------------------------------------------------------------\n";
    }

    void borrar(int id) {
        for (auto it = lista.begin(); it != lista.end(); ++it) {
            if (it->getId() == id) {
                lista.erase(it);
                std::cout << "\n[-] Punto con ID " << id << " eliminado correctamente.\n";
                return;
            }
        }
        std::cout << "\n[!] ID no encontrado.\n";
    }

     void guardarEnArchivo() const {
        std::ofstream archivo("puntos.csv");
        if (archivo.is_open()) {
            archivo << "ID,Nombre,Zona,Hemisferio,Este,Norte,Cota,Latitud,Longitud\n";
            for (const auto& p : lista) {
                archivo << p.getId() << ","
                        << p.getNombre() << ","
                        << p.getTopo().zona << ","
                        << p.getTopo().hemisferio << ","
                        << p.getTopo().este << ","
                        << p.getTopo().norte << ","
                        << p.getTopo().cota << ","
                        << p.getLat() << ","
                        << p.getLon() << "\n";
            }
            archivo.close();
            std::cout << "\n[+] Datos exportados exitosamente en 'puntos.csv'.\n";
        } else {
            std::cout << "\n[!] Error al abrir/crear el archivo 'puntos.csv'.\n";
        }
    }
};

#endif // MANEJADORDB_H