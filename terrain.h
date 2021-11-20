#ifndef TERRAIN_H
#define TERRAIN_H

#include <vector>
#include <iostream>
#include "json.hpp"

class Terrain {
public:
    Terrain();
    Terrain(int hauteur, int largeur);
    Terrain(int hauteur, int largeur, std::vector<std::vector<std::string>> map);
    int largeur() const;
    int hauteur() const;
    void setObstacle(int x, int y, const std::string& s);
    std::vector<std::vector<std::string>> map() const;
    void affiche(std::ostream& ost) const;
    nlohmann::json creerTerrainJSON() const;
private:
    std::vector<std::vector<std::string>> terrainBase(int largeur, int hauteur);
    int d_hauteur, d_largeur;
    std::vector<std::vector<std::string>> d_map;
};

#endif // TERRAIN_H

