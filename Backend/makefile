# For generators
CC:=g++
GEN_FLAGS:= -Werror
GEN_SOURCES:=$(wildcard html/*.cpp json/*.cpp)
GEN_OUTPUT:=libbackend.o
LIB_NAME:=libbeg.a

clear:
	rm -f $(wildcard ./*/*.o ./*.o *.a ./*/*.gch) $(LIB_NAME) backend

# builds generators library
gen:
	$(CC) $(GEN_FLAGS) -c $(GEN_SOURCES)
	ar rcs libbeg.a $(wildcard ./*.o)
	rm -f $(wildcard ./*.o)
	ranlib -U libbeg.a

# builds back end executable
backend: gen
	$(CC) main.cpp -L. ./libbeg.a -o backend

run: backend
	./backend