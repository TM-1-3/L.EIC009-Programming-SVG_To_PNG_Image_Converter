//! @file shape.hpp
#ifndef __svg_SVGElements_hpp__
#define __svg_SVGElements_hpp__
#include "Color.hpp"
#include "Point.hpp"
#include "PNGImage.hpp"
#include "external/tinyxml2/tinyxml2.h"
using namespace tinyxml2;

namespace svg
{
    class SVGElement
    {

    public:
        SVGElement();
        virtual ~SVGElement();
        virtual void draw(PNGImage &img) const = 0;

        //virtual pure functions for the transformation
        virtual void translate(const Point &p) = 0;
        virtual void rotate(int degrees, const Point &origin = {0,0}) = 0;
        virtual void scale(int v, const Point &origin = {0,0}) = 0;

        virtual SVGElement* copy() = 0;
    };

    // Declaration of namespace functions
    // readSVG -> implement it in readSVG.cpp
    // convert -> already given (DO NOT CHANGE) in convert.cpp

    void readSVG(const std::string &svg_file,
                 Point &dimensions,
                 std::vector<SVGElement *> &svg_elements);
    void convert(const std::string &svg_file,
                 const std::string &png_file);

    //! A function to help read the svg file, implemented in readSVG.cpp.
    //! @param elem The element we are reading.
    //! @param objects A vector of pairs string and SVGElement, in which the string is the id of the respective element - for <use> elements.
    //! @return Returns a vector of dynamically allocated SVGElements, that will in the end become the svg_elements vector.
    std::vector<SVGElement*> help_SVG(XMLElement* elem, std::vector<std::pair<std::string, SVGElement*>> &objects);

    //! A function that recieves a string of points and turns them into a vector of points.
    //! @param str The string with the points.
    //! @return A vector of the points in the string.
    std::vector<Point> get_points(std::string str);

    //! A function to implement transformations, implemented in readSVG.cpp.
    //! @param transformation A string with the information about the transformation.
    //! @param transf_og The origin of the transformation.
    //! @param to_change The element we want to apply changes to.
    void apply_transformation(std::string transformation, std::string transf_og, SVGElement& to_change);


    // Declaration of subclass Ellipse of SVGElement.

    class Ellipse : public SVGElement
    {
    public:
        Ellipse(const Color &fill, const Point &center, const Point &radius);
        void draw(PNGImage &img) const override;

        //! Translates an Ellipse given a direction.
        //! @param p Translation direction.
        void translate(const Point &p) override;

        //! Rotates an Ellipse.
        //! The generic value of the origin is {0,0}.
        //! @param origin Origin of rotation.
        //! @param degrees Degrees of rotation.
        void rotate(int degrees, const Point &origin = {0,0}) override;

        //! Changes the scale of the Ellipse.
        //! The generic value of the origin is {0,0}.
        //! @param origin Scaling origin.
        //! @param v Scale amount.
        void scale(int v, const Point &origin = {0,0}) override;

        //! Makes a copy of an Ellipse element.
        //! @return Returns a dynamically allocated copy of the element.
        SVGElement* copy() override;

    private:
        // Private variables.
        Color fill;
        Point center;
        Point radius;
    };


    // Declaration of subclass Circle of Ellipse.

    class Circle : public Ellipse{
    public:
        //! Circle constructor.
        //! @param fill Color of the Circle.
        //! @param center Center of the Circle.
        //! @param radius Radius of the Circle.
        Circle(const Color &fill, const Point &center, int radius);
    };


    // Declaration of subclass Polyline of SVGElement

    class Polyline : public SVGElement {
    public:
        //! Polyline constructor.
        //! @param vertex A comma-separated sequence of connected lines.
        //! @param stroke Color of lines.
        Polyline(const std::vector<Point>& vertex, const Color &stroke);

        //! Draws the Polyline in the PNG image.
        //! @param img The image in which we will draw the Polyline.
        void draw(PNGImage &img) const override;

        //! Translates a Polyline given a direction.
        //! @param p Translation direction.
        void translate(const Point &p) override;

        //! Rotates a Polyline.
        //! The generic value of the origin is {0,0}.
        //! @param degrees Degrees of rotation.
        //! @param origin Origin of rotation.
        void rotate(int degrees, const Point &origin = {0,0}) override;

        //! Changes the scale of the Polyline.
        //! The generic value of the origin is {0,0}.
        //! @param origin Scaling origin.
        //! @param v Scale amount.
        void scale(int v, const Point &origin = {0,0}) override;

        //! Makes a copy of a Polyline element.
        //! @return Returns a dynamically allocated copy of the element.
        SVGElement* copy() override;

    private:
        // Private variables.
        std::vector<Point> vertex;
        Color stroke;
    
   };

   // Declaration of subclass Line of Polyline.

    class Line : public Polyline {
    public:
        //! Line constructor.
        //! @param vertex A comma-separated sequence of two points.
        //! @param p1 Start point.
        //! @param p2 End point.
        Line(const Point &p1, const Point &p2, const Color &stroke);
   };


   // Declaration of subclass Polygon of SVGElement.

    class Polygon : public SVGElement {
    public:
        //! Polygon constructor.
        //! @param vertex A comma-separated sequence of XY coordinates.
        //! @param fill Color of Polygon.
        Polygon(const std::vector<Point> &vertex, const Color &fill);

        //! Draws the Polygon in the PNG image.
        //! @param img The image in which we will draw the Polygon.
        void draw(PNGImage &img) const override;

        //! Translates a Polygon given a direction.
        //! @param p Translation direction.
        void translate(const Point &p) override;

        //! Rotates a Polygon.
        //! The generic value of the origin is {0,0}.
        //! @param origin Origin of rotation.
        //! @param degrees Degrees of rotation.
        void rotate(int degrees, const Point &origin = {0,0}) override;

        //! Changes the scale of the Polygon.
        //! The generic value of the origin is {0,0}.
        //! @param origin Scaling origin.
        //! @param v Scale amount.
        void scale(int v, const Point &origin = {0,0}) override;

        //! Makes a copy of a Polygon element.
        //! @return Returns a dynamically allocated copy of the element.
        SVGElement* copy() override;

    protected:
        // Private variables.
        std::vector<Point> vertex;
        Color fill;
   };


   // Declaration of subclass Rectangle of Polygon.

    class Rect : public Polygon {
    public:
        //! Rectangle constructor.
        //! @param c XY coordinates of the upper left corner of the Rectangle.
        //! @param width Width of the Rectangle.
        //! @param height Height of the Rectangle.
        //! @param fill Color of Rectangle.
        Rect(const Point &c, int width, int height, const Color &fill);
   };
}
#endif
