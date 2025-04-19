# For generators
GEN_SOURCES=$(wildcard html/*.hpp json/*.hpp generators/*.hpp)
LIB_NAME=libbeg.a

# builds generators library
gen:
	gcc -c $(GEN_SOURCES)
	gcc $(GEN_SOURCES:.hpp=.hpp.gch) -o libbackend.o
	ar rcs libbeg.a libbackend.o

# builds back end executable
backend:
	gcc main.cpp -L. libbeg.a -o backend

clear:
	rm $(wildcard *.o *.a ./*/*.gch) $(LIB_NAME) backend