<img src='https://sigarra.up.pt/feup/pt/imagens/LogotipoSI' width="30%"/>

<div align="center">
🌍 <a href="README.md">English</a> | 🇵🇹 <a href="README.pt.md">Português</a>
</div>

<h3 align="center">Licenciatura em Engenharia Informática e Computação<br>L.EIC009 - Programação<br> 2023/2024 </h3>

---
<h3 align="center"> Colaboradores &#129309 </h3>

<div align="center">

| Nome           | Número      |
|----------------|-------------|
| Leonor Azevedo | up202304040 |
| Maria Sousa    | up202307037 |
| Tomás Morais   | up202303834 |

Nota: 19,4

</div>

# Relatório do Projeto Conversor de Imagens SVG para PNG

* [Tarefas Realizadas](#tarefas-realizadas) 
  * [Classes e Subclasses de Elementos SVG](#classes-e-subclasses-svg)
  * [Extração e Manipulação de Elementos SVG](#extracao-e-manipulacao-de-elementos-svg)
* [Compilação e Execução](#compilacao-e-execucao)
  * [Compilação](#compilacao)
  * [Execução](#execucao)


## Tarefas Realizadas

Em primeiro lugar, declaramos todas as subclasses e funções em `SVGElement.hpp`. Em seguida, implementámo-las em `SVGElement.cpp`. Finalmente, utilizámos `readSVG.cpp` para ler o ficheiro `svg_file`, extraindo as figuras geométricas no formato SVG, bem como as transformações a executar.  

Com o nosso código conseguimos extrair e criar corretamente as figuras geométricas necessárias, aplicar as transformações correspondentes e, por fim, convertê-las para o formato de imagem PNG.

### <a id="classes-e-subclasses-svg"></a>Classes e Subclasses de Elementos SVG (SVGElements.hpp e SVGElements.cpp)

- Declaramos e implementámos subclasses de `SVGElement` para várias formas SVG, incluindo `Ellipse`, `Polyline`, `Polygon` e as respetivas subclasses: `Circle`, `Line` e `Rect`.  
  Cada subclasse de `SVGElement` inclui as funções membro: `draw`, `translate`, `rotate`, `scale` e `copy`.

- Implementámos os construtores para as classes `Ellipse`, `Circle`, `Polyline`, `Line`, `Polygon` e `Rect`.

- Inicializámos as propriedades das classes e subclasses:
  - `fill`, `radius` e `center` para a elipse e o círculo;
  - `vertex` e `stroke` para a polilinha;
  - `p1`, `p2` e `stroke` para a linha;
  - `vertex` e `fill` para o polígono;
  - `c`, `width`, `height` e `fill` para o retângulo.

- O construtor da classe `Ellipse` recebe como parâmetros um ponto (`center`), dois valores de raio (`radius`) e a cor (`fill`), de forma a construir uma elipse.

- A classe `Circle`, subclasse de `Ellipse`, é implementada com o construtor de `Ellipse`, mas com ambos os raios iguais, criando assim um círculo.

- O construtor da classe `Polyline` recebe como parâmetros um vetor de pontos (`vertex`), representando as coordenadas dos vértices, e a cor (`stroke`), construindo um conjunto de linhas interligadas.

- A classe `Line`, subclasse de `Polyline`, é implementada com o construtor de `Polyline`, mas apenas recebe dois pontos (`p1` e `p2`) no vetor `vertex`.

- O construtor da classe `Polygon` recebe como parâmetros um vetor de pontos (`vertex`), representando os vértices, e a cor (`fill`), de forma a construir um polígono.

- A classe `Rect` é implementada como subclasse de `Polygon`, representando retângulos. O seu construtor recebe parâmetros para o canto superior esquerdo, a largura, a altura e a cor da figura.

- Implementámos as funções membro `draw`, `translate`, `rotate`, `scale` e `copy` em cada subclasse, com pequenas variações de acordo com as propriedades. Estas funções permitem desenhar, mover, rodar, aumentar ou diminuir o tamanho e duplicar a figura.

### <a id="extracao-e-manipulacao-de-elementos-svg"></a>Extração e Manipulação de Elementos SVG (readSVG.cpp)

- Com a função `help_svg`, identificamos o conteúdo do ficheiro `svg_file`, verificando se contém figuras individuais ou grupos de figuras.  
  Extraímos os parâmetros correspondentes e, através das chamadas aos construtores das classes e subclasses, criamos as figuras.  
  A função também identifica as transformações e os respetivos parâmetros a aplicar às figuras (ou ao grupo), executando-as com a função `apply_transformation`.

- Com a função `get_points`, extraímos do ficheiro `svg_file` os pontos relacionados com cada figura.  
  Estes pontos vêm no formato de string, separados por espaços e/ou vírgulas, e são depois utilizados para a construção da figura.

- Com a função `apply_transformation`, identificamos a transformação a aplicar a cada elemento, bem como os parâmetros associados, e executamos essa transformação através da função membro correspondente.

## <a id="compilacao-e-execucao"></a>Compilação e Execução

No diretório principal do projeto, correr:

### <a id="compilacao"></a>Compilação  

```bash
make clean all
```

### <a id="execucao"></a>Execução

```bash
./test
```
