EXE = testimage
EXE2 = testscene
OBJS = testimage.o rgbapixel.o png.o image.o
OBJS2 = testscene.o rgbapixel.o png.o image.o scene.o
COMPILER = g++
COMPILER_MP = -c -g -O0 -Wall -Werror
LINKER = g++

all: testimage testscene

testimage : $(OBJS)
	g++ $(OBJS) -lpng -o testimage

testscene : $(OBJS2) 
	g++ $(OBJS2) -lpng -o testscene

testimage.o : testimage.cpp image.h png.h rgbapixel.h
	$(COMPILER) $(COMPILER_MP) testimage.cpp

testscene.o : testscene.cpp scene.h image.h
	$(COMPILER) $(COMPILER_MP) testscene.cpp

rgbapixel.o : rgbapixel.cpp rgbapixel.h
	$(COMPILER) $(COMPILER_MP) rgbapixel.cpp

png.o: png.cpp png.h rgbapixel.h
	$(COMPILER) $(COMPILER_MP) png.cpp

image.o : image.cpp image.h png.h
	$(COMPILER) $(COMPILER_MP) image.cpp
scene.o : scene.cpp image.h
	$(COMPILER) $(COMPILER_MP) scene.cpp
clean: 
	-rm -f *.o $(EXE) $(EXE2)




