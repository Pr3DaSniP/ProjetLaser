#include "laser.h"
#include "point.h"
#include "type.h"
#include "doctest.h"

using geom::point;
using TYPE::OBJET;
using TYPE::DIRECTION;

void lesCoordonneesDuPointDuLaserSontExact(const point& p, double x, double y)
{
    REQUIRE_EQ(p.x(), x);
    REQUIRE_EQ(p.y(), y);
}

TEST_CASE("Les valeurs du laser sont bien entrées")
{
    double x1{12.5}, x2{-10};
    double y1{5.5}, y2{0.5};
    point p1{}, p2{};
    p1.moveTo(x1, y1);
    p2.moveTo(x2, y2);
    laser l{p1, p2, OBJET::LASER, DIRECTION::DROITE};
    SUBCASE("Les coordonnées des points P1 et P2 du laser sont correctes")
    {
        lesCoordonneesDuPointDuLaserSontExact(l.getP1(), x1, y1);
        lesCoordonneesDuPointDuLaserSontExact(l.getP2(), x2, y2);
        double x3{-12}, x4{-15};
        double y3{7}, y4{12};
        point p3{x3, y3}, p4{x4, y4};
        l.setP1(p3);
        l.setP2(p4);
        lesCoordonneesDuPointDuLaserSontExact(l.getP1(), x3, y3);
        lesCoordonneesDuPointDuLaserSontExact(l.getP2(), x4, y4);
    }
    SUBCASE("Le type d'objet est correct")
    {
        REQUIRE_EQ(l.getType(), OBJET::LASER);
    }
    SUBCASE("La direction du laser est correcte")
    {
        REQUIRE_EQ(l.getDirection(), DIRECTION::DROITE);
        l.setDirection(DIRECTION::GAUCHE);
        REQUIRE_EQ(l.getDirection(), DIRECTION::GAUCHE);
    }
}
