#ifndef GESTIONNAIRETERRAIN_H
#define GESTIONNAIRETERRAIN_H

#include <iostream>
#include "json.hpp"
#include "Terrains.h"

using std::vector;
using std::unique_ptr;
using std::make_unique;
using std::string;
using std::cout;
using std::cin;
using std::endl;

class gestionnaireTerrain {
public:
    gestionnaireTerrain(const string& nomFichier);
    void execute();
private:
    int choixMenu();
    void creerTerrain();
    void saveToJSON(vector<Terrain> tTerrain);
    void supprimerTerrain();
    void visualisation(const vector<Terrain>& tTerrain);
        
    vector<Terrain> initialisation(const string& nomFichier);
    vector<Terrain> d_Terrains;
    string d_Filename;
};

#endif // GESTIONNAIRETERRAIN_H
