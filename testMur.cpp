#include "mur.h"
#include "point.h"
#include "type.h"
#include "doctest.h"

using geom::point;
using TYPE::OBJET;

void lesCoordonneesDuPointDuMurSontExact(const point& p, double x, double y)
{
    REQUIRE_EQ(p.x(), x);
    REQUIRE_EQ(p.y(), y);
}

TEST_CASE("Les valeurs du mur sont bien entrées")
{
    double x1{7.5}, x2{6.75};
    double y1{-15.5}, y2{10.5};
    point p1{}, p2{};
    p1.moveTo(x1, y1);
    p2.moveTo(x2, y2);
    mur m{p1, p2, OBJET::MUR, false};
    SUBCASE("Les coordonnées des points du mur sont correctes")
    {
        lesCoordonneesDuPointDuMurSontExact(m.getP1(), x1, y1);
        lesCoordonneesDuPointDuMurSontExact(m.getP2(), x2, y2);
        double x3{-7.5}, x4{-6.75};
        double y3{15.5}, y4{-10.5};
        point p3{x3, y3}, p4{x4, y4};
        m.setP1(p3);
        m.setP2(p4);
        lesCoordonneesDuPointDuMurSontExact(m.getP1(), x3, y3);
        lesCoordonneesDuPointDuMurSontExact(m.getP2(), x4, y4);
    }
    SUBCASE("Le type d'objet est correct")
    {
        REQUIRE_EQ(m.getType(), OBJET::MUR);
    }
    SUBCASE("La valeur si le mur est touché ou pas est correcte")
    {
        REQUIRE_EQ(m.estTouche(), false);
        m.setTouche(true);
        REQUIRE_EQ(m.estTouche(), true);
    }
}
