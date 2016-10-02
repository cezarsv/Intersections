Project organization:
---------------------

The project was created and tested on Cygwin and Linux, using GCC 4.8 and GNU Make.

There are two solutions: "solution_iterative" - the main solution, and "solution_recursive" - a suplementary one.
They can be built and run in the same way. Each solution can be built separately, and contains also a set of Unit Tests.

make		-> rebuild from scratch everything
make build	-> build only the changed sources
make run_test	-> run all the Unit Tests

./output/IntersectCalculator file_name [max_num_of_intersect]	-> run the main executable


The files:

IntersectCalculator.h, IntersectCalculator.cpp		-> source files for reading the input file and calculating the intersections

main.cpp						-> source file containing the function 'main()' of IntersectCalculator executable

TestDriver.h, TestDriver.cpp				-> source files with the Unit Tests cases definitions

jsoncpp.cpp, json					-> Json source files, downloaded from https://github.com/open-source-parsers/jsoncpp.git

BadFile.txt						-> bad formatted Json file used in Unit Tests

GoodFile.txt						-> proper Json file used in Unit Tests

output							-> directory containing the executables and the obj files

output/gitkeep						-> empty file needed to force Git to maintain the empty dir 'output'


General usage:
--------------

The application can be run by:
	./output/IntersectCalculator file_name [max_num_of_intersect]

'file_name' is the input Json file, containing the rectangle definitions
'max_num_of_intersections' is optional and it's provided in order to limit, if wanted, the number of detected solutions. 

To run the example provided in the requirements:
	./output/IntersectCalculator GoodFile.txt

Why do we need the 'max_num_of_intersections' limit ?
It's easy to imagine an input where any K rectangles have an intersection, with K = 2..1000. 
For instance all the rectangles can have the same definition. 
As the total number of combinations of K elements, K = 0..1000, is 2**1000, then it's possible 
for such an input to produce (2**1000 - 1000 -1)  results. But 2**1000 ~= 10**300, so that's
a too big number of intersections and would take too long to find and list all of them.


Steps to download and build:
----------------------------

git clone https://github.com/cezarsv/Intersections.git

cd Intersections

cd solution_iterative

### rebuild everything:
make

### run all the Unit Tests:
make run_test

### run the example provided in the requirements:
./output/IntersectCalculator GoodFile.txt

cd ../solution_recursive
make
make run_test
./output/IntersectCalculator GoodFile.txt

