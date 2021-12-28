#include"doctest.h"
#include"cible.h"
#include"objet.h"
#include"type.h"
using namespace TYPE;


TEST_CASE("La creation de la cible est correcte")
{
    geom::point p1{4.2, 5.3};
    geom::point p2{6.2, 5.3};
    int type{OBJET::CIBLE};
    bool touche;
    cible c{p1, p2, OBJET::CIBLE, touche};
    geom::point po= c.getP1();
    REQUIRE_EQ(po, p1);
    geom::point poi= c.getP2();
    REQUIRE_EQ(poi, p2);
    int t= c.getType();
    REQUIRE_EQ(t, type);
    bool x= c.estTouche();
    REQUIRE_EQ(x, touche);
    SUBCASE("le changement de valeur de toucher est correcte")
    {
        c.setTouche(!touche);
        bool x= c.estTouche();
        REQUIRE_EQ(x, true);
    }


}

