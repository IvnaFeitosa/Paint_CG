#ifndef OBJ_CONTAINER_HPP
#define OBJ_CONTAINER_HPP

#include <list>
#include "point.hpp"
#include "line.hpp"
#include "polygon.hpp"

class ObjContainer {
private:
    std::list<Poly> polygons;
    std::list<Point> points;
    std::list<Line> lines;

public:
    ObjContainer();
    
    void addPoint(Point p);
    void addLine(Line l);
    void addPoly(Poly poly);

    void clear();

    list<Point>& get_points();
    list<Line>& get_lines();
    list<Poly>& get_polygons();

    Object* search_detection(float mx, float my);
    void search_for_deletion(Object* obj);
};

#endif
