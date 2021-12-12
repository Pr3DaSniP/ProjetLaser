#include "Case.h"
#include "point.h"
#include "CaseVide.h"

caseVide::caseVide(const point& p1, const point& p2)
    : Case{p1, p2}
{}

caseVide::caseVide(const point& p, double width, double height)
    : Case{p, width, height}
{}

caseVide::caseVide(int positionHorizontale, int positionVerticale, int typeCase)
    : Case{positionHorizontale, positionVerticale, typeCase}
{}

void caseVide::print() const
{
    std::cout<<'['<<topLeft()<<", "<<bottomRight()<<']';
}

int caseVide::typeCase() const
{
    return d_typeCase;
}
