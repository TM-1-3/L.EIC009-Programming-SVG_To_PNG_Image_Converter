<img src='https://sigarra.up.pt/feup/pt/imagens/LogotipoSI' width="30%"/>

<h3 align="center">BSc in Informatics and Computing Engineering<br>L.EIC009 - Programming<br> 2023/2024 </h3>

---
<h3 align="center"> Collaborators &#129309 </h2>

<div align="center">

| Name           | Number      |
|----------------|-------------|
| Leonor Azevedo | up202304040 |
| Maria Sousa    | up202307037 |
| Tomás Morais   | up202303834 |

Grade : 19,4

</div>

# SVG To PNG Image Converter Project Report

* [Accomplished Tasks](#accomplished-tasks) 
  * [SVG Element Classes and Subclasses (SVGElements.hpp and SVGElements.cpp)](#svg-element-classes-and-subclasses-svgelementshpp-and-svgelementscpp)
  * [Extraction and Manipulation of SVG Elements (readSVG.cpp)](#extraction-and-manipulation-of-svg-elements-readsvgcpp)
* [Compilation and Running](#compilation-and-running)



## Accomplished Tasks

Firstly, we declared every subclass and function in SVGElement.hpp, secondly we implemented them in SVGElement.cpp. Finally, we used readSVG.cpp to read the svg_file, extracting the geometrial figures in the svg image format as well as the transformations to be executed. With our code we managed to successfully extract and create the required geometrical figures, extract and apply the transformations to be applicated in them and, finally, to convert them to the png image format.

### SVG Element Clases and Subclasses (SVGElements.hpp and SVGElements.cpp)

- We've declared and implemented subclasses of SVGElement for various SVG shapes, including Ellipse, Polyline, Polygon and their respective subclasses: Circle, Line and Rect. Each subclass of SVGElements includes their member functions that include draw, translate, rotate, scale and copy.

- We have implemented the constructor for the Ellipse, Circle, Polyline, Line, Polygon and Rect classes.

- We initialized the properties of the classes and subclasses:
  - fill, radius and center for the ellipse and circle;
  - vertex and stroke for the polyline;
  - p1, p2 and stroke for the line;
  - vertex and fill for the Polygon;
  - c, widht, height and fill for the rect.

- The Ellipse class' constructor takes as its parameters a point, radius, with the two values of radii, a point, center, with the coordinates of its center and the fill, the color of the figure in order to build an ellipse.

- The Circle class, a subclass of Ellipse, is implemented with the Ellipse constructor that takes parameters for fill, center and radius, with the difference that the two radius have the same value, effectively creating a circle by setting both radii equal.

- The Polyline class' constructor takes as its parameters a vector of points, vertex, representing the coordinates of its vertex and the stroke(color) of the figure, in order to build a group of interconnected finite lines.

- The Line class, a subclass of Polyline, is implemented with the Polyline constructor, taking also the parameter for stroke with the difference that it takes only two points, p1 and p2, inside the vertex vector.

- The Polygon class' constructor takes as its parameters a vector of points, vertex, representing the coordinates of its vertex, and fill, the color of the figure, in order to build a polygon.

- The Rect class is implemented as a subclass of Polygon, representing rectangles. Its constructor takes parameters for the upper-left corner, width, height, and fill of the figure.

- We implemented the member functions, draw, translate, rotate, scale and copy on each subclass, with slight alterations between them according to their respective properties, that successfully draw, move, rotate, increase or decrease its size, and create a duplicate, respectively, of the figure in which they are applicated.

### Extraction and Manipulation of SVG Elements (readSVG.cpp)

- With the help_svg function we identify the contents of the svg_file, whether it contains individual figures or a group of figures, extracting the respective parameters and, with the calls to the constructors of the classes and subclasses, creating the figure. Also, the function manages to identify the transformation, and the respective parameters, to be aplicated to all the figures, in the case of a group, that will be executed using the apply_transformation function.

- With the get_points function we intend to extract, from elements in svg_file, the points related to the figure which come in the format of a string separated by spaces and/or commas, in order for them to be used in other functions when they are required, such as the construction of the figure.

- With the apply_transformation function, we manage to idenify the transformation to be applicated to each individual element, as well as the parameters related to it, and execute that respective transformation, with the calls to the respective member-function.

## Compilation and Running

On the project´s main directory run:

**Compilation:** $ make clean all

**Running:** $ ./test








