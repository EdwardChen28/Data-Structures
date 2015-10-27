# This makefile is use for MP1-cs225  

COMPILER = g++
COMPILER_FLAGS = -c -g -O0 -Wall -Werror
LINKER = g++


mp1 : main.o png.o rgbapixel.o
	$(LINKER) main.o png.o rgbapixel.o -lpng -o mp1

rgbapixel.o : rgbapixel.cpp rgbapixel.h
	$(COMPILER) $(COMPILER_FLAGS) rgbapixel.cpp
png.o : png.cpp png.h rgbapixel.h
	$(COMPILER) $(COMPILER_FLAGS) png.cpp

main.o : main.cpp png.h rgbapixel.h
	$(COMPILER) $(COMPILER_FLAGS) main.cpp


clean:
	-rm -f *.o mp1
