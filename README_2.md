*** Steps to download and build ***

git clone https://github.com/cezarsv/Intersections.git

cd Intersections

cd solution_iterative

rebuild everything:
make

run all the Unit Tests:
make run_test

run the example provided in the requirements:
./output/IntersectCalculator GoodFile.txt

cd ../solution_recursive
make
make run_test
./output/IntersectCalculator GoodFile.txt


*** Project organization ***

The project was created and tested on Cygwin and Linux, using GCC 4.8 and GNU Make.

There are two solutions: "solution_iterative" - the main solution, and "solution_recursive" - a suplementary one. 
They can be built and run in the same way. Each solution can be built separately, and contains also a set of Unit Tests.

rebuild from scratch everything:
make

build only the changed sources:
make build

run all the Unit Tests:
make run_test

run the main executable:
./output/IntersectCalculator file_name [max_num_of_intersect] 
e.g.
./output/IntersectCalculator GoodFile.txt

The files:

source files for reading the input file and calculating the intersections: 
IntersectCalculator.h, IntersectCalculator.cpp

source file containing the function 'main()' of IntersectCalculator executable: 
main.cpp

source files with the Unit Tests cases definitions: 
TestDriver.h, TestDriver.cpp

Json source files, downloaded from https://github.com/open-source-parsers/jsoncpp.git: 
jsoncpp.cpp, json/json.h, json/json-forwards.h

bad formatted Json file used in Unit Tests:
BadFile.txt

proper Json file used in Unit Tests (the example from the requirements):
GoodFile.txt

directory containing the executables and the obj files:
output

empty file needed to force Git to maintain the empty dir 'output':
output/gitkeep


*** General usage ***

The application can be run by: 
./output/IntersectCalculator file_name [max_num_of_intersect]

'file_name' is the input Json file, containing the rectangle definitions 
'max_num_of_intersections' is optional and it's provided in order to limit, if wanted, the number of detected solutions.

To run the example provided in the requirements: 
./output/IntersectCalculator GoodFile.txt

Why do we need the 'max_num_of_intersections' limit ? 
It's easy to imagine an input where any K rectangles have an intersection, with K = 2..1000. For instance all the rectangles 
can have the same definition. As the total number of combinations of K elements, K = 0..1000, is 21000, then it's possible for 
such an input to produce (21000 - 1000 -1) results. But 21000 ~= 10300, so that's a too big number of intersections and would 
take too long to find and list all of them.
