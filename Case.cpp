#include "Case.h"
#include "point.h"
using geom::point;

Case::Case() : d_topLeft{}, d_bottomRight{}
{}

Case::Case(const point& p1, const point& p2)
    : d_topLeft{p1}, d_bottomRight{p2}
{}

Case::Case(const point& p, double width, double height)
    : d_topLeft{p}, d_bottomRight{p.x()+width, p.y()+height}
{}

Case::Case(int positionHorizontale, int positionVerticale, int typeCase)
    : d_positionHorizontal{positionHorizontale}, d_positionVerticale{positionVerticale}, d_typeCase{typeCase}
{}

int Case::positionHorizontale() const
{
    return d_positionHorizontal;
}

int Case::positionVerticale() const
{
    return d_positionVerticale;
}

point Case::topLeft() const
{
    return d_topLeft;
}

point Case::bottomRight() const
{
    return d_bottomRight;
}

double Case::left() const
{
    return d_topLeft.x();
}
double Case::top() const
{
    return d_topLeft.y();
}

double Case::right() const
{
    return d_bottomRight.x();
}

double Case::bottom() const
{
    return d_bottomRight.y();
}

double Case::width() const
{
    return d_bottomRight.x()-d_topLeft.x();
}

double Case::height() const
{
    return d_topLeft.y()-d_bottomRight.y();
}

void Case::move(double dx, double dy)
{
    d_topLeft.move(dx, dy); d_bottomRight.move(dx, dy);
}

void Case::moveTo(double x, double y)
{
    d_topLeft.moveTo(x, y + height());
    d_bottomRight.moveTo(x + width(), y);
}

bool Case::contains(const point& p) const
{
    return (d_topLeft.x()<p.x() && p.x()<d_bottomRight.x())&&
            (d_bottomRight.y()<p.y() && p.y()<d_topLeft.y());
}
