#ifndef CASEVIDE_H_INCLUDED
#define CASEVIDE_H_INCLUDED
#include "Case.h"
#include "point.h"

class caseVide : public Case{
public:
    caseVide(const point& p1, const point& p2);
    caseVide(const point& p, double width, double height);
    caseVide(int positionHorizontale, int positionVerticale, int typeCase);
    virtual void print() const override;
    virtual int typeCase() const override;

};


#endif // CASEVIDE_H_INCLUDED
