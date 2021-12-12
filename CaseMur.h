#ifndef CASEMUR_H_INCLUDED
#define CASEMUR_H_INCLUDED
#include "Case.h"
#include "point.h"
#include "Mur.h"

using geom::point;

class caseMur : public Case{
public:
    caseMur(const point& p1, const point& p2, mur* m=nullptr);
    caseMur(const point& p, double width, double height, mur* m=nullptr);
    caseMur(int positionHorizontale, int positionVerticale, int typeCase, mur* m=nullptr);
    mur* getMur() const;
    virtual void print() const override;
    virtual int typeCase() const override;
private:
    mur* d_mur;

};


#endif // CASEMUR_H_INCLUDED
