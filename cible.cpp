#include"cible.h"

cible::cible(const geom::point& p1, const geom::point& p2, int rayon):caseCible{p1, p2}, d_rayon{rayon}
{

}
double cible::cibleX() const
{
    return d_x;
}
double cible::cibleY() const
{
    return d_y;
}
int cible::cibleRayon() const
{
    return d_rayon;
}
