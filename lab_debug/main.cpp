#include <cstdlib>
#include "png.h"
#include <iostream>
using namespace std;

// sets up the output image
PNG * setupOutput(int w, int h);

// Returns my favorite color
RGBAPixel * myFavoriteColor(int intensity);

int main()
{
        cout << "Reached line 14" << endl;
	// Load in.png
	PNG * original;

	original = new PNG();
	original->readFromFile("in.png");

	cout << "Reached line 14" << endl;
	int width  = original->width();
	int height = original->height();

	// Create out.png
	PNG *output;
	output=setupOutput(width, height);	

	// Loud our favorite color to color the outline
	RGBAPixel * myPixel = myFavoriteColor(192);

	// Go over the whole image, and if a pixel differs from that to its upper
	// left, color it my favorite color in the output
	cout << "Reached line 34"<<endl;
	for (int y = 1; y < height; y++)
	{
	  for (int x = 1;  x < width; x++)
		{
			// Calculate the pixel difference
			RGBAPixel * prev = (*original)(x-1, y-1);
			RGBAPixel * curr = (*original)(x  , y  );
			int diff = abs(curr->red   - prev->red  ) +
					   abs(curr->green - prev->green) +
					   abs(curr->blue  - prev->blue );

			// If the pixel is an edge pixel,
			// color the output pixel with my favorite color
			 RGBAPixel * currOutPixel = (*output)(x,y);
			if (diff > 100)
			  *currOutPixel =* myPixel;
			  
		}
	}
	cout << "reached line 54" << endl;
	// Save the output file
	output->writeToFile("out.png");

	cout << "reached line 58"<<endl;
	// Clean up memory
	
	delete  myPixel;
	cout << "reached line 61"<<endl;
	delete  output;
	delete original;
	return 0;
}


// sets up the output image
PNG * setupOutput(int w, int h)
{
	PNG * image = new PNG(w, h);
	return image;
}


// Returns my favorite color
RGBAPixel * myFavoriteColor(int intensity)
{
	RGBAPixel *color=new RGBAPixel;
	color->red   = 0;
	color->green = intensity/2;
	color->blue  = intensity;
	return color;
}
