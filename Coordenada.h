// --------------------------------------------------
// Nombre: Aron Malpartida
// Fecha: 01/08/2026
// Proyecto: Bóveda Digital - Convertidor de Coordenadas
// --------------------------------------------------

#ifndef COORDENADA_H
#define COORDENADA_H

struct Coordenada {
    double este;       // X (en metros)
    double norte;      // Y (en metros)
    double cota;       // Z (en metros)
    int zona;          // Zona UTM (ejemplo: 17, 18, 19)
    char hemisferio;   // 'N' para Norte, 'S' para Sur
};

#endif // COORDENADA_H