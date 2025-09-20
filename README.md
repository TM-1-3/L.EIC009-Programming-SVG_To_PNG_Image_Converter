<img src='https://sigarra.up.pt/feup/pt/imagens/LogotipoSI' width="30%"/>

<p align="center">
🌍 [English] (README.md) | 🇵🇹 [Português] (README.pt.md)
</p>

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
  * [SVG Element Classes and Subclasses](#svg-element-classes)
  * [Extraction and Manipulation of SVG Elements](#extraction-and-manipulation-of-svg-elements-readsvgcpp)
* [Compilation and Execution](#compilation-and-execution)
  * [Compilation](#compilation)
  * [Execution](#execution)


## Accomplished Tasks

First, we declared every subclass and function in `SVGElement.hpp`. Then, we implemented them in `SVGElement.cpp`. Finally, we used `readSVG.cpp` to read the `svg_file`, extracting the geometrical figures in the SVG image format as well as the transformations to be executed.  

With our code, we successfully extracted and created the required geometrical figures, applied the corresponding transformations, and ultimately converted them into the PNG image format.

### <a id="svg-element-classes"></a>SVG Element Classes and Subclasses (`SVGElements.hpp` and `SVGElements.cpp`)

- We declared and implemented subclasses of `SVGElement` for various SVG shapes, including `Ellipse`, `Polyline`, `Polygon`, and their respective subclasses: `Circle`, `Line`, and `Rect`.  
  Each subclass of `SVGElement` includes member functions such as `draw`, `translate`, `rotate`, `scale`, and `copy`.

- We implemented constructors for the classes `Ellipse`, `Circle`, `Polyline`, `Line`, `Polygon`, and `Rect`.

- We initialized the properties of the classes and subclasses:
  - `fill`, `radius`, and `center` for `Ellipse` and `Circle`;
  - `vertex` and `stroke` for `Polyline`;
  - `p1`, `p2`, and `stroke` for `Line`;
  - `vertex` and `fill` for `Polygon`;
  - `c`, `width`, `height`, and `fill` for `Rect`.

- The constructor of the `Ellipse` class takes a center point (`center`), two radii (`radius`), and the fill color (`fill`) to build an ellipse.

- The `Circle` class, a subclass of `Ellipse`, is implemented using the `Ellipse` constructor, but with both radii equal, effectively creating a circle.

- The constructor of the `Polyline` class takes a vector of points (`vertex`), representing the coordinates of its vertices, and a stroke color (`stroke`) to build a group of interconnected finite lines.

- The `Line` class, a subclass of `Polyline`, is implemented using the `Polyline` constructor but only takes two points (`p1` and `p2`) in the `vertex` vector.

- The constructor of the `Polygon` class takes a vector of points (`vertex`) representing the coordinates of its vertices, and a fill color (`fill`) to build a polygon.

- The `Rect` class is implemented as a subclass of `Polygon`, representing rectangles. Its constructor takes the upper-left corner (`c`), width (`width`), height (`height`), and fill color (`fill`).

- We implemented the member functions `draw`, `translate`, `rotate`, `scale`, and `copy` in each subclass, with slight variations depending on their properties. These functions successfully draw, move, rotate, resize, and duplicate each figure.

### <a id="extraction-and-manipulation-of-svg-elements-readsvgcpp"></a>Extraction and Manipulation of SVG Elements (`readSVG.cpp`)

- With the function `help_svg`, we identify the contents of the `svg_file`, whether it contains individual figures or groups of figures.  
  We extract the respective parameters and, by calling the class constructors, create the figures.  
  The function also identifies transformations and their parameters to be applied to all figures in a group, executed via the `apply_transformation` function.

- With the function `get_points`, we extract from the `svg_file` the points related to each figure.  
  These points come as a string separated by spaces and/or commas and are then used for figure construction.

- With the function `apply_transformation`, we identify the transformation to apply to each element, along with its parameters, and execute it via the corresponding member function.


## Compilation and Execution

On the project´s main directory run:

### <a id="compilation"></a>Compilation

```bash
make clean all
```
### <a id="execution"></a>Execution

```bash
./test
```








