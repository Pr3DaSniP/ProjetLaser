#ifndef CASELASER_H_INCLUDED
#define CASELASER_H_INCLUDED
#include "Laser.h"
#include "Case.h"

using geom::point;


class caseLaser : public Case{
public:
    caseLaser(const point& p1, const point& p2, laser* l=nullptr);
    caseLaser(const point& p, double width, double height, laser* l=nullptr);
    caseLaser(int positionHorizontale, int positionVerticale, int typeCase, laser* l=nullptr);
    laser* getLaser() const;
    virtual void print() const override;
    virtual int typeCase() const override;

private:
    laser* d_laser;

};


#endif // CASELASER_H_INCLUDED
