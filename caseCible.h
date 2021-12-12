#ifndef CASECIBLE_H_INCLUDED
#define CASECIBLE_H_INCLUDED
#include "Case.h"
#include "point.h"
#include "Cible.h"

using geom::point;

class caseCible : public Case{
public:
    caseCible(const point& p1, const point& p2, cible* c=nullptr);
    caseCible(const point& p, double width, double height, cible* c=nullptr);
    caseCible(int positionHorizontale, int positionVerticale, int typeCase, cible* c=nullptr);
    cible* getCible() const;
    virtual void print() const override;
    virtual int typeCase() const override;


private:
    cible* d_cible;

};

#endif // CASECIBLE_H_INCLUDED
