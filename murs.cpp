#include <iostream>
#include <string>
#include "objets_terrain.h"
#include "murs.h"

murs::murs(double x, double y,const std::string& representation) : objets_terrain{x,y}, d_representation{representation} {}

void murs::affiche() const {
    std::cout << d_representation;
}

std::string murs::representation() const {
    return d_representation;
}