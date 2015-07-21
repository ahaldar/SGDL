#Simple Graph Decomposition Library (SGDL)

##Description

This library provides a simple C++ framework for the implementation of contour tree comparison algorithms.

It uses the Graph Modelling Language (GML) to represent and store graph information. It uses Graph Template Library (GTL) for basic graph manipulation and computation:
[GML and GTL](http://www.fim.uni-passau.de/index.php?id=17297&L=1).

It uses Graphviz to display graphs visually:
[Graphviz](http://www.graphviz.org/).

##Prerequisites

The code in this library has been developed and tested using:
* Ubuntu 14.04 LTS
* g++ version 4.8.4
* Graphviz version 2.36.0
* GTL version 1.2.4

The code should build without issues on any recent version of Ubuntu GNU/Linux and g++.

##Installation

* `sudo apt-get install g++`
* `sudo apt-get install graphviz`
* Download GTL from the [GTL project page](http://www.fim.uni-passau.de/fileadmin/files/lehrstuhl/brandenburg/projekte/gtl/GTL-1.2.4-lgpl.tar.gz) and extract
* Clone SGDL repository from GitHub (includes required patch for GTL):  
  `git clone https://github.com/ahaldar/SGDL.git`
* `cd GTL-1.2.4`
* `patch -p0 < ../SGDL/gtl-sgdl.patch`
* `./configure`
* `make`
* If make is successful then install GTL:  
  `sudo make install`
* `cd ../SGDL`
* `make`
* Run example main program without arguments for usage instructions:
  `./main`
* Enjoy
