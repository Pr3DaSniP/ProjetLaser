#include "Laser.h"
#include "Case.h"
#include "CaseLaser.h"

caseLaser::caseLaser(const point& p1, const point& p2, laser* l)
    : Case{p1, p2}, d_laser{l}
{}

caseLaser::caseLaser(const point& p, double width, double height, laser* l)
    : Case{p, width, height}, d_laser{l}
{}

caseLaser::caseLaser(int positionHorizontale, int positionVerticale, int typeCase, laser* l)
    : Case{positionHorizontale, positionVerticale, typeCase}, d_laser{l}
{}

laser* caseLaser::getLaser() const
{
    return d_laser;
}

void caseLaser::print() const
{
    std::cout<<'['<<topLeft()<<", "<<bottomRight()<<']';
}

int caseLaser::typeCase() const
{
    return d_typeCase;
}


