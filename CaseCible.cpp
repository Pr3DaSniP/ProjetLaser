#include "caseCible.h"
#include "Case.h"
#include "Cible.h"
#include <iostream>

caseCible::caseCible(const point& p1, const point& p2, cible* c)
    : Case{p1, p2}, d_cible{c}
{}

caseCible::caseCible(const point& p, double width, double height, cible* c)
    : Case{p, width, height}, d_cible{c}
{}

caseCible::caseCible(int positionHorizontale, int positionVerticale, int typeCase, cible* c)
    : Case{positionHorizontale, positionVerticale, typeCase}, d_cible{c}
{}

cible* caseCible::getCible() const
{
    return d_cible;
}

void caseCible::print() const
{
    std::cout<<'['<<topLeft()<<", "<<bottomRight()<<']';
}

int caseCible::typeCase() const
{
    return d_typeCase;
}
