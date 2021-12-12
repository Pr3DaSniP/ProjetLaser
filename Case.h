#ifndef CASE_H_INCLUDED
#define CASE_H_INCLUDED
#include "point.h"
#include <iostream>
using geom::point;


class Case{
public:
    Case();
    Case(const point& p1, const point& p2);
    Case(const point& p, double width, double height);
    Case(int positionHorizontale, int positionVerticale, int typeCase);
    int positionHorizontale() const;
	int positionVerticale() const;
    virtual ~Case()=default;
    point topLeft() const;
    point bottomRight() const;
    double left() const;
    double top() const;
    double right() const;
    double bottom() const;
    double width() const;
    double height() const;
    void move(double dx, double dy);
    void moveTo(double x, double y);
    bool contains(const point& p) const;
    virtual void print() const = 0;
    virtual int typeCase() const = 0;
protected:
    point d_topLeft;
    point d_bottomRight;
    int d_positionHorizontal;
    int d_positionVerticale;
    int d_typeCase;
};
//std::ostream& operator<<(std::ostream& ost, const Case& c);
//std::istream& operator<<(std::istream& ist, Case& c);


#endif // CASE_H_INCLUDED
