#include "image.h"
#include <ostream>
using namespace std;

void Image::flipleft()
{
	for ( size_t x = 0; x < (width()/2); x++)
	{
		for( size_t y =0 ; y < height(); y++)

		{
			RGBAPixel temp = *((*this)(x,y));
			*((*this)(x,y)) = *((*this)(width()-x-1, y));
			*((*this)((*this).width()-x-1, y))=temp;
			

		}
	}

}

void Image:: adjustbrightness(int r, int g, int b)
{
	
	for(size_t x = 0; x < width(); x++)
	{
		for(size_t y = 0; y <height(); y++)
		{
		int red = (*this)(x,y)->red + r;
		int green = (*this)(x,y)->green + g;
		int blue = (*this)(x,y)->blue + b;
		
		if( red < 0 ) red =0;
		if( red > 255) red = 255;
		if( green < 0 ) green =0;
		if( green > 255) green = 255;
		if( blue < 0 ) blue =0;
		if( blue > 255) blue = 255;
		
		(*this)(x,y)-> red =red;
		(*this)(x,y)-> green = green;
		(*this)(x,y)->blue = blue;

		}
	}

}

void Image :: invertcolors()
{
	for(size_t x = 0; x < width(); x++)
	{
		for( size_t y = 0; y <height(); y++)
		{
			((*this)(x,y)->red) = 255 - ((*this)(x,y)-> red);
			((*this)(x,y)->green) = 255 - ((*this)(x,y)-> green);
			((*this)(x,y)->blue) = 255 - ((*this)(x,y)-> blue);

		}
	}



}

