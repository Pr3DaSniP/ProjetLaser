#include "Case.h"
#include "Miroir.h"
#include "CaseMiroir.h"

caseMiroir::caseMiroir(const point& p1, const point& p2, miroir* m)
    : Case{p1, p2}, d_miroir{m}
{}

caseMiroir::caseMiroir(const point& p, double width, double height, miroir* m)
    : Case{p, width, height}, d_miroir{m}
{}

caseMiroir::caseMiroir(int positionHorizontale, int positionVerticale, int typeCase, miroir* m)
    : Case{positionHorizontale, positionVerticale, typeCase}, d_miroir{m}
{}

miroir* caseMiroir::getMiroir() const
{
    return d_miroir;
}

void caseMiroir::print() const
{
    std::cout<<'['<<topLeft()<<", "<<bottomRight()<<']';
}

int caseMiroir::typeCase() const
{
    return d_typeCase;
}
