#include"doctest.h"
#include"vide.h"
#include"objet.h"


TEST_CASE("La creation d'objet vide est correcte")
{
    geom::point p1{4.2, 5.3};
    geom::point p2{6.2, 5.3};
    int type{2};
    bool Traverse;
    vide v{p1, p2, type, Traverse};
    geom::point po= v.getP1();
    REQUIRE_EQ(po, p1);
    geom::point poi= v.getP2();
    REQUIRE_EQ(poi, p2);
    int t= v.getType();
    REQUIRE_EQ(t, type);
    bool x= v.estTraverse();
    REQUIRE_EQ(x, Traverse);
    SUBCASE("le changement de valeur de traverser est correcte")
    {
        v.setTraverse(!Traverse);
        bool x= v.estTraverse();
        REQUIRE_EQ(x, true);
    }


}
