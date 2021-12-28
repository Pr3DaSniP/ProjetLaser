#include "miroir.h"
#include "point.h"
#include "type.h"
#include "doctest.h"

using geom::point;
using TYPE::OBJET;

void lesCoordonneesDuPointDuMiroirSontExact(const point& p, double x, double y)
{
    REQUIRE_EQ(p.x(), x);
    REQUIRE_EQ(p.y(), y);
}

TEST_CASE("Les valeurs du miroir sont bien entrées")
{
    double x1{13.05}, x2{16.9};
    double y1{15.5}, y2{10.5};
    point p1{}, p2{};
    p1.moveTo(x1, y1);
    p2.moveTo(x2, y2);
    miroir m{p1, p2, OBJET::MIROIR_SLASH};
    SUBCASE("Les coordonnées des points P1 et P2 du miroir sont correctes")
    {
        lesCoordonneesDuPointDuMiroirSontExact(m.getP1(), x1, y1);
        lesCoordonneesDuPointDuMiroirSontExact(m.getP2(), x2, y2);
        double x3{-12}, x4{-15};
        double y3{7}, y4{12};
        point p3{x3, y3}, p4{x4, y4};
        m.setP1(p3);
        m.setP2(p4);
        lesCoordonneesDuPointDuMiroirSontExact(m.getP1(), x3, y3);
        lesCoordonneesDuPointDuMiroirSontExact(m.getP2(), x4, y4);
    }
    SUBCASE("Le type d'objet miroir est correct")
    {
        REQUIRE_EQ(m.getType(), OBJET::MIROIR_SLASH);
        m.setType(OBJET::MIROIR_BACKSLASH);
        REQUIRE_EQ(m.getType(), OBJET::MIROIR_BACKSLASH);
    }
}
