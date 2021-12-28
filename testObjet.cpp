#include"doctest.h"
#include"cible.h"
#include"objet.h"


TEST_CASE("La creation d'objet est correcte")
{
    geom::point p1{4.2, 5.3};
    geom::point p2{6.2, 5.3};
    int type{2};
    objet o{p1, p2, type};
    geom::point po= o.getP1();
    REQUIRE_EQ(po, p1);
    geom::point poi= o.getP2();
    REQUIRE_EQ(poi, p2);
    int t= o.getType();
    REQUIRE_EQ(t, type);
}
TEST_CASE("Le changement de cordonnées d'objet est correcte")
{
    geom::point p1{4.2, 5.3};
    geom::point p2{6.2, 5.3};
    int type{2};
    objet o{p1, p2, type};
    o.setP1(p1);
    geom::point po= o.getP1();
    REQUIRE_EQ(po, p1);
    o.setP2(p2);
    geom::point poi= o.getP2();
    REQUIRE_EQ(poi, p2);
    o.setType(type);
    int t= o.getType();
    REQUIRE_EQ(t, type);
}
