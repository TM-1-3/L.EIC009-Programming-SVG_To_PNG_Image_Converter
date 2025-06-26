#include "SVGElements.hpp"
#include <math.h>
#include <iostream>

namespace svg
{
    // These must be defined!
    SVGElement::SVGElement() {} 
    SVGElement::~SVGElement() {}

    // Ellipse (initial code provided)
    Ellipse::Ellipse(const Color &fill,
                     const Point &center,
                     const Point &radius)
        : fill(fill), center(center), radius(radius){}
    void Ellipse::draw(PNGImage &img) const
    {
        img.draw_ellipse(center, radius, fill);
    }

    //! Implementation of member function translate of subclass Elippse. 
    //! @param p Translation direction.
    void Ellipse::translate(const Point &p){
        center = center.translate(p);
    }

    //! Implementation of member function rotate of subclass Ellipse.
    //! @param origin Origin of rotation.
    //! @param degrees Degrees of rotation.
    void Ellipse::rotate(int degrees, const Point &origin){
        center = center.rotate(origin,degrees);
    }

    //! Implementation of member function scale of subclass Ellipse.
    //! @param origin Scaling origin.
    //! @param v Scale amount.
    void Ellipse::scale(int v, const Point &origin){
        center = center.scale(origin,v);
        radius.x = radius.x*v;
        radius.y = radius.y*v;
    }

    //! Implementation of member function copy of subclass Ellipse.
    //! @return Returns a dynamically allocated copy of the element.
    SVGElement* Ellipse::copy(){
        return new Ellipse(fill, center, radius);
    }

    // Circle

    //! Implementation of the constructor of subclass Circle.
    //! @param fill Color of the Circle.
    //! @param center Center of the Circle.
    //! @param radius Radius of the Circle.
    Circle::Circle(const Color &fill, const Point &center, int radius)
        : Ellipse(fill,center,Point{radius,radius}){}

    // Polyline

    //! Implementation of the constructor of subclass Polyline.
    //! @param vertex A comma-separated sequence of connected lines.
    //! @param stroke Color of lines.
    Polyline::Polyline(const std::vector<Point> &vertex, const Color &stroke)
        : vertex(vertex), stroke(stroke){}

    //! Implementation of member function draw of subclass Polyline.
    //! @param img The image in which we will draw the Polyline.
    void Polyline::draw(PNGImage &img) const{
        Point anterior;
        int iter = 0;
        for (Point i: vertex){
            if (iter!=0){
                img.draw_line(anterior, i, stroke);
            }
            anterior = i;
            iter++;
        }
    }

    //! Implementation of member function translate of subclass Polyline.
    //! @param p Translation direction.
    void Polyline::translate(const Point &p){
        for (Point& i : vertex){
            i = i.translate(p);
        }
    }
    //! Implementation of member function rotate of subclass Polyline.
    //! @param degrees Degrees of rotation.
    //! @param origin Origin of rotation.
    void Polyline::rotate(int degrees, const Point &origin){
        for (Point& i : vertex){
            i = i.rotate(origin,degrees);
        }
    }
    //! Implementation of member function scale of subclass Polyline.
    //! @param origin Scaling origin.
    //! @param v Scale amount.
    void Polyline::scale(int v, const Point &origin){
        for (Point& i : vertex){
            i = i.scale(origin,v);
        }
    }

    //! Implementation of member function copy of subclass Polyline.
    //! @return Returns a dynamically allocated copy of the element.
    SVGElement* Polyline::copy(){
        return new Polyline(vertex,stroke);
    }

    // Line

    //! Implementation of the constructor of subclass Line.
    //! @param vertex A comma-separated sequence of two points.
    //! @param p1 Start point.
    //! @param p2 End point.
    Line::Line(const Point &p1, const Point &p2, const Color &stroke)
        : Polyline({p1,p2}, stroke){}

    // Polygon

    //! Implementation of the constructor of subclass Polygon.
    //! @param vertex A comma-separated sequence of XY coordinates.
    //! @param fill Color of Polygon.
    Polygon::Polygon(const std::vector<Point> &vertex, const Color &fill)
        : vertex(vertex), fill(fill){}

    //! Implementation of member function draw of subclass Polygon.
    //! @param img The image in which we will draw the Polygon.
    void Polygon::draw(PNGImage &img) const
    {
        img.draw_polygon(vertex, fill);
    }
    //! Implementation of member function translate of subclass Polygon.
    //! @param p Translation direction.
    void Polygon::translate(const Point &p){
        for (Point& i : vertex){
            i = i.translate(p);
        }
    }
    //! Implementation of member function rotate of subclass Polygon.
    //! @param origin Origin of rotation.
    //! @param degrees Degrees of rotation.
    void Polygon::rotate(int degrees, const Point &origin){
        for (Point& i : vertex){
            i = i.rotate(origin,degrees);
        }
    }
    //! Implementation of member function scale of subclass Polygon.
    //! @param origin Scaling origin.
    //! @param v Scale amount.
    void Polygon::scale(int v, const Point &origin){
        for (Point& i : vertex){
            i = i.scale(origin,v);
        }
    }

    //! Implementation of member function copy of subclass Polygon.
    //! @return Returns a dynamically allocated copy of the element.
    SVGElement* Polygon::copy(){
        return new Polygon(vertex,fill);
    }

    // Rect

    //! Implementation of the constructor of subclass Rectangle.
    //! @param c XY coordinates of the upper left corner of the Rectangle.
    //! @param width Width of the Rectangle.
    //! @param height Height of the Rectangle.
    //! @param fill Color of Rectangle.
    Rect::Rect(const Point &c, int width, int height, const Color &fill)
        : Polygon({c, {c.x+width-1,c.y}, {c.x+width-1,c.y+height-1}, {c.x,c.y+height-1}},fill){}
}
