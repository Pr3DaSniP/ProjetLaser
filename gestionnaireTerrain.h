#ifndef GESTIONNAIRETERRAIN_H
#define GESTIONNAIRETERRAIN_H

#include <iostream>
#include "json.hpp"
#include "terrain.h"
//#include "afficheur.h"

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
    vector<terrain> getTerrains();
private:
    int choixMenu();
    void creerTerrain();
    void saveToJSON(vector<terrain>& tTerrain);
    void supprimerTerrain();
    void visualisation(const vector<terrain>& tTerrain);
    vector<terrain> initialisation(const string& nomFichier);
    vector<terrain> d_Terrains;
    string d_Filename;
};

#endif // GESTIONNAIRETERRAIN_H
