#include "objets_terrain.h"

objets_terrain::objets_terrain(double x, double y) : d_x{x}, d_y{y} {}

double objets_terrain::x() const
{
    return d_x;
}

double objets_terrain::y() const
{
    return d_y;
}
