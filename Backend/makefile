# For generators
CC:=g++
GEN_SOURCES:=$(wildcard html/*.cpp json/*.cpp)
GEN_OUTPUT:=libbackend.o
LIB_NAME:=libbeg.a

%.o: %.cpp
	$(CC) -c $< -o $@

# builds generators library
gen: $(GEN_SOURCES:.cpp=.o)
	$(CC) -o $(GEN_OUTPUT) $^
	ar rcs libbeg.a libbackend.o
	ranlib -U libbeg.a

# builds back end executable
backend: gen
	$(CC) main.cpp -L. libbeg.a -o backend

run: backend
	./backend

clear:
	rm $(wildcard ./*/*.o *.a ./*/*.gch) $(LIB_NAME) backend