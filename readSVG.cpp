#include <iostream>
#include "SVGElements.hpp"
#include "external/tinyxml2/tinyxml2.h"
#include <sstream>
#include <string>
#include <cstdlib>
#include <bits/stdc++.h>

using namespace std;
using namespace tinyxml2;

namespace svg
{
    void readSVG(const string& svg_file, Point& dimensions, vector<SVGElement *>& svg_elements)
    {
        XMLDocument doc;
        XMLError r = doc.LoadFile(svg_file.c_str());
        if (r != XML_SUCCESS)
        {
            throw runtime_error("Unable to load " + svg_file);
        }
        XMLElement *xml_elem = doc.RootElement();

        dimensions.x = xml_elem->IntAttribute("width");
        dimensions.y = xml_elem->IntAttribute("height");
        
        vector<pair<string, SVGElement*>> objects = {}; // Creating the objects vector.
        vector<SVGElement*> help_vect = help_SVG(xml_elem, objects); // Calling the help function.

        svg_elements = help_vect; 
    }

    //! A function to help read the svg file, implemented in readSVG.cpp.
    //! @param elem The element we are reading.
    //! @param objects A vector of pairs string and SVGElement, in which the string is the id of the respective element - for <use> elements.
    //! @return Returns a vector of dynamically allocated SVGElements, that will in the end become the svg_elements vector.
    vector<SVGElement*> help_SVG(XMLElement* elem, vector<pair<string, SVGElement*>> &objects){

        // This is the vector we want to return in the end.
        vector<SVGElement*> final = {};
        string elem_name = elem->Name();

        // This is a flag to see if the element is a shape, and not a group or a copy.
        bool flag = false;
        // This is the element we want to put in the vector to return (final).
        SVGElement* to_vector;

        // Now we check which type of element it is.
        if (elem_name=="ellipse"){
            Point center = {elem->IntAttribute("cx"), elem->IntAttribute("cy")}; // Discover the Ellipse's center.
            Point radius = {elem->IntAttribute("rx"), elem->IntAttribute("ry")}; // Discover the Ellipse's radius.
            to_vector = new Ellipse(parse_color(elem->Attribute("fill")), center, radius); // Create the Ellipse.
            flag = true;
        }

        else if (elem_name=="circle"){
            Point center = {elem->IntAttribute("cx"), elem->IntAttribute("cy")}; // Discover the Circle's center.
            to_vector = new Circle(parse_color(elem->Attribute("fill")), center, elem->IntAttribute("r")); // Create the Circle.
            flag = true;
        }

        else if (elem_name=="polyline"){
            vector<Point> v = get_points(elem->Attribute("points")); // Get the points of the Polyline.
            to_vector = new Polyline(v, parse_color(elem->Attribute("stroke"))); // Create the Polyline.
            flag = true;
        }

        else if (elem_name=="line"){
            Point p1 = {elem->IntAttribute("x1"), elem->IntAttribute("y1")}; // Discover the Line's start point.
            Point p2 = {elem->IntAttribute("x2"), elem->IntAttribute("y2")}; // Discover the Line's end point.
            to_vector = new Line(p1, p2, parse_color(elem->Attribute("stroke"))); // Create the Line.
            flag = true;
        }

        else if (elem_name=="polygon"){
            vector<Point> v = get_points(elem->Attribute("points")); // Get the point of the Polygon.
            to_vector = new Polygon(v, parse_color(elem->Attribute("fill"))); // Create the Polygon.
            flag = true;
        }

        else if (elem_name=="rect"){
            Point p = {elem->IntAttribute("x"), elem->IntAttribute("y")}; // Discover the upper left corner of the Rectangle.
            to_vector = new Rect(p, elem->IntAttribute("width"), elem->IntAttribute("height"), parse_color(elem->Attribute("fill"))); // Create the Rectangle.
            flag = true;
        }

        else if (elem_name == "use"){
            string ref = elem->Attribute("href");
            ref = ref.substr(1, ref.size()-1); // Ref is now the id of the element we want to copy.
            vector<pair<string,SVGElement*>> yoyo = {}; // This is an auxiliary vector for the objects vector, as we can not change the objects vector inside the for cycle.

            // We will now go throught the objects vector to find out which element we want to copy.
            for (pair<string, SVGElement*> p : objects){
                
                if (p.first==ref){ // Checking if the id of the element is equal to the reference.

                    // Calling the copy function of the SVGElement class.
                    SVGElement* to_vector = (*p.second).copy();

                    // A string that houses the transformation origin.
                    // It is empty if it has none.
                    string transf_og = "";

                    if(elem->Attribute("transform-origin")!=nullptr){
                        transf_og = elem->Attribute("transform-origin");
                    }

                    // If use has a transformation associated, we call the apply_transformation function.
                    // Defined below.
                    if(elem->Attribute("transform")!=nullptr){
                        apply_transformation(elem->Attribute("transform"),transf_og,*to_vector);
                    }

                    // We put the transformed copied element in the final vector.
                    final.push_back(to_vector);

                    // If the element has an id, we put it in the auxiliary vector.
                    if(elem->Attribute("id")!=nullptr){
                        yoyo.push_back({elem->Attribute("id"),to_vector});
                    }
                }
            }

            // Now we pass the elements from the auxiliary vector to the objects vector.
            for (pair<string,SVGElement*> nen : yoyo){
                objects.push_back(nen);
            }
            
        }

        // If the element is only a shape, apply the transformations and put the element in the vector.
        if (flag){
            string transf_og = "";

            // If it has a transformation origin, we put the string in transf_og.
            if(elem->Attribute("transform-origin")!=nullptr){
                transf_og = elem->Attribute("transform-origin");
            }

            // If it has a transformation, we call the apply_transformation function.
            if(elem->Attribute("transform")!=nullptr){
                apply_transformation(elem->Attribute("transform"),transf_og,*to_vector);
            }
            // We put the element in the final vector.
            final.push_back(to_vector);

            // If it has an id, we put it in the objects vector, so it can be copied later.
            if(elem->Attribute("id")!=nullptr){
                objects.push_back({elem->Attribute("id"),to_vector});
            }
        }

        // Recursive call of the function for all the children element of elem.
        // Only appliable in the inicial case (the svg element) or when the element is a group.
        for (XMLElement *child = elem->FirstChildElement(); child != nullptr; child = child->NextSiblingElement()){           
            vector<SVGElement*> help = help_SVG(child, objects);

            // We put the elements that were returned in the final vector.
            for (SVGElement* i : help){
                final.push_back(i);
            }
        }

        if(elem_name=="g"){

            // We check if the group has an origin, a transformation and an id.
            string transf_og = "";
            string transformation = "";
            string id = "";

            if(elem->Attribute("transform-origin")!=nullptr){
                transf_og = elem->Attribute("transform-origin");
            }

            if(elem->Attribute("transform")!=nullptr){
                transformation= elem->Attribute("transform");
            }

            if(elem->Attribute("id")!=nullptr){
                id = elem->Attribute("id");
            }

            // In the case of a group, the recursive cycle above makes it so that the final vector has all the group elements.
            // So we need to apply the tranformation to all elements of final.
            for (SVGElement* e : final){
                if (transformation!=""){
                    apply_transformation(transformation, transf_og, *e);
                }
                if (id!=""){
                    objects.push_back({id,e});
                }
            }
        }

        // We return the final vector.
        // It has only one element in case of shapes or several in the case of group, use or svg (the root element).
        return final;
    }

    //! A function that recieves a string of points and turns them into a vector of points.
    //! @param str The string with the points.
    //! @return A vector of the points in the string.
    vector<Point> get_points(string str){
        // This is the vector of points we want to return.
        vector<Point> final = {};

        // This is a temporary point whose values will be changed and then put into final.
        Point p = {0,0};
        string helper;

        // This is a boolean variable that tells us if the coordinate we are processing is the y coordinate.
        bool scnd_coord = false;

        istringstream in (str);

        // Each point is separated from the others by a space, so helper only has one point at a time.
        while(in>>helper){
            for(char c: helper){
                // When we read the comma, we pass from the first coordinate to the second.
                if(c==','){
                    scnd_coord = true;
                }

                // If we are working on the second coordinate, we change the second coordinate of point p accordingly.
                else if (scnd_coord){
                    p.y = p.y*10 + int(c)-int('0');
                }
                // If we are working on the first coordinate, we change the first coordinate of point p accordingly.
                else{
                    p.x = p.x*10 + int(c)-int('0');
                }
            }

            // When we are finished with a point, put p in final and reset the scnd_coord and p variables.
            scnd_coord = false;
            final.push_back(p);
            p = {0,0};
        }

        return final;
    }

    //! A function to implement transformations, implemented in readSVG.cpp.
    //! @param transformation A string with the information about the transformation.
    //! @param transf_og The origin of the transformation.
    //! @param to_change The element we want to apply changes to.
    void apply_transformation(string transformation, string transf_og, SVGElement& to_change){
        // Vector containing the x and y coordinates of the origin.
        vector<string> origin_cords;
        Point origin = {0,0};

        if (transf_og!=""){
            // Vector containing the x and y coordinates of the origin.
            vector<string> origin_cords;
            // While loop to iterate over the string related to the "transform-origin" attribute in order to obtain the x and y coordnates of the origin.
            istringstream iss (transf_og);
            do{
                // Words of the string corresponding to the coordinates of the origin.
                string cords;
                iss >> cords;
                // Addition of the coordinates in the vector.
                origin_cords.push_back(cords);
            } while (iss);
            // Conversion of the coordinates in the string format to int.
            origin.x = stoi(origin_cords[0]);
            origin.y = stoi(origin_cords[1]);
        }
        
        // Vector containing the parameters to be used by the transformation functions.
        vector<string> transform_vec;
        
        // String containing only the parameters of the transformation function.
        string numbers = transformation;
        // Index of the first parentheses to be incrementated in the following for loop.
        int index = 0;
        // For loop to find the index of the first parentheses.
        for (char &c: numbers){
            if (c == '('){
                break;
            }
            index++;
        }
            
        // Removal of all the characters in the string from the beggining to the first parentheses.
        numbers.erase(0, index+1);
        // Removal of the last parentheses making the string to only contain the parameters of the transformation function.
        numbers.pop_back();

        // Number of characters in the string.
        int length = transformation.length();
        // Removal of all the characters in the string from the first parentheses to the end  making the string to only contain the name of the transformation function.
        transformation.erase(index, length - index);

        // While loop to iterate over the string numbers related to the "transform" attribute in order to obtain the parameters of the transformation function.
        for (char& c: numbers){
            if (c==','){
                c=' ';
            }
        }
        
        istringstream iss (numbers);
        string transform_coords;

        while(iss>>transform_coords){
            transform_vec.push_back(transform_coords);
        }

        // Checking if the transformation is the translate one.
        if (transformation=="translate"){
            Point p;
            // Initialization of the parameters from the vector.
            // Conversion of the coordinates of point p in the string format to int.
            p.x = stoi(transform_vec[0]);
            p.y = stoi(transform_vec[1]);

            // Calling of the translate function.
            to_change.translate(p);
        }

        // Checking if the transformation is the rotate one.
        if (transformation=="rotate"){
            // Initialization of the parameter from the vector.
            // Conversion of the parameter degrees in the string format to int.
            int degrees = stoi(transform_vec[0]);

            // Calling of the rotate function.
            to_change.rotate(degrees, origin);
        }
            // Checking if the transformation is the scale one.
        if (transformation=="scale"){
            // Initialization of the parameter from the vector.
            // Conversion of the parameter v in the string format to int.
            int  v = stoi(transform_vec[0]);

            // Calling of the scale function.
            to_change.scale(v, origin);
        }
    }
}
