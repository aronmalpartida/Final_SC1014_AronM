// -// --------------------------------------------------
// Nombre: Aron Malpartida
// Fecha: 01/08/2026
// Proyecto: Bóveda Digital - Convertidor de Coordenadas
// --------------------------------------------------

#include <iostream>
#include "ManejadorDB.h"

int main() {
    ManejadorDB db;
    int opcion = 0;

    while (opcion != 4) {
        std::cout << "\n=== CONVERTIDOR GEODESICO UTM (WGS84) A LAT/LON ===\n";
        std::cout << "1. Agregar Punto Topografico (UTM)\n";
        std::cout << "2. Ver Todos los Puntos Convertidos\n";
        std::cout << "3. Eliminar Punto por ID\n";
        std::cout << "4. Salir y Guardar en CSV\n";
        std::cout << "Seleccione una opcion: ";

        if (!(std::cin >> opcion)) {
            std::cin.clear();
            std::cin.ignore(10000, '\n');
            std::cout << "\n[!] Entrada invalida. Por favor, ingrese un numero.\n";
            continue;
        }

        switch (opcion) {
            case 1: {
                std::string nombre;
                double e, n, z;
                int zona;
                char hemisferio;

                std::cout << "Nombre del punto: ";
                std::cin >> nombre;
                std::cout << "Coordenada Este X (metros): ";
                std::cin >> e;
                std::cout << "Coordenada Norte Y (metros): ";
                std::cin >> n;
                std::cout << "Cota Z (elevacion): ";
                std::cin >> z;
                std::cout << "Zona UTM (ejemplo 17, 18, 19): ";
                std::cin >> zona;
                std::cout << "Hemisferio ('N' o 'S'): ";
                std::cin >> hemisferio;

                db.insertar(nombre, e, n, z, zona, hemisferio);
                break;
            }
            case 2:
                db.listar();
                break;
            case 3: {
                int id;
                std::cout << "Ingrese el ID a eliminar: ";
                std::cin >> id;
                db.borrar(id);
                break;
            }
            case 4:
                db.guardarEnArchivo();
                std::cout << "\nCerrando el Convertidor Geodesico... ¡Hasta luego!\n";
                break;
            default:
                std::cout << "\n[!] Opcion invalida. Intente de nuevo.\n";
        }
    }
    return 0;
}