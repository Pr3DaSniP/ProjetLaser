#ifndef CASEMIROIR_H_INCLUDED
#define CASEMIROIR_H_INCLUDED
#include "point.h"
#include <iostream>
#include "Case.h"
#include "Miroir.h"
using geom::point;


class caseMiroir : public Case{
public:
    caseMiroir(const point& p1, const point& p2, miroir* m=nullptr);
    caseMiroir(const point& p, double width, double height, miroir* m=nullptr);
    caseMiroir(int positionHorizontale, int positionVerticale, int typeCase, miroir* m=nullptr);
    miroir* getMiroir() const;
    virtual void print() const override;
    virtual int typeCase() const override;
private:
    miroir* d_miroir;
};



#endif // CASEMIROIR_H_INCLUDED
