#ifndef GESTIONNAIRETERRAIN_H
#define GESTIONNAIRETERRAIN_H

#include <iostream>
#include "json.hpp"
#include "terrain.h"

class gestionnaireTerrain {
public:
    gestionnaireTerrain(const std::string& nomFichier);
    void execute();
private:
    int choixMenu();
    void creerTerrain();
    void saveToJSON(std::vector<Terrain> tTerrain);
    void supprimerTerrain();
    void visualisation() const;
    std::vector<Terrain> initialisation(const std::string& nomFichier);

    std::vector<Terrain> d_Terrains;
    std::string d_Filename;
};

#endif // GESTIONNAIRETERRAIN_H
