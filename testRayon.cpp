#include"doctest.h"
#include"rayon.h"
#include"objet.h"
#include"type.h"
using namespace TYPE;


TEST_CASE("La creation de rayon est correcte")
{
    geom::point p1{4.2, 5.3};
    geom::point p2{6.2, 5.3};
    int type{OBJET::RAYON};
    objet o{p1, p2, type};
    geom::point po= o.getP1();
    REQUIRE_EQ(po, p1);
    geom::point poi= o.getP2();
    REQUIRE_EQ(poi, p2);
    int t= o.getType();
    REQUIRE_EQ(t, type);
}
