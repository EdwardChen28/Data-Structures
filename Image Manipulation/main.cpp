#include <algorithm>
#include <iostream>

#include "rgbapixel.h"
#include "png.h"

using namespace std;

PNG rotate(PNG image){
	PNG newImage(image.width(), image.height());

	for(size_t x = 0 ; x < image.width(); x++){
		for(size_t y = 0 ; y < image.height(); y++){
			size_t xlocation =  image.width()-x-1;
			size_t ylocation =  image.height()-y-1;
			*newImage(xlocation, ylocation) = *image(x,y);
		}
	}
return newImage;
}

int main(){
	PNG input("in.png");
	PNG output = rotate(input);
	output.writeToFile("out.png");



 return 0;
}

