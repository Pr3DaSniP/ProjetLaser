#include "Case.h"
#include "point.h"
#include "Mur.h"
#include "CaseMur.h"

caseMur::caseMur(const point& p1, const point& p2, mur* m)
    : Case{p1, p2}, d_mur{m}
{}

caseMur::caseMur(const point& p, double width, double height, mur* m)
    : Case{p, width, height}, d_mur{m}
{}

caseMur::caseMur(int positionHorizontale, int positionVerticale, int typeCase, mur* m)
    : Case{positionHorizontale, positionVerticale, typeCase}, d_mur{m}
{}

mur* caseMur::getMur() const
{
    return d_mur;
}

void caseMur::print() const
{
    std::cout<<'['<<topLeft()<<", "<<bottomRight()<<']';
}

int caseMur::typeCase() const
{
    return d_typeCase;
}
