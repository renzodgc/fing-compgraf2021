// HEADERS
// -----------------------------------------------------------------------------------

#include <iostream>
#include "image.h"

// METHODS
// -----------------------------------------------------------------------------------

// Constructors / Destructors
// -----------------------------------------------------------------------------------

Image::Image() {
	fill(*image, *image + IMAGE_WIDTH * IMAGE_HEIGHT, BLACK);
}

Image::~Image() {}

// Methods
// -----------------------------------------------------------------------------------

// Reference: http://graphics.stanford.edu/courses/cs148-10-summer/docs/UsingFreeImage.pdf
FIBITMAP * Image::float_to_bitmap() {
	// TODO: It may be needed to re-normalize color values if they go beyond 0..1. See questions page

	FIBITMAP* result = FreeImage_Allocate(IMAGE_WIDTH, IMAGE_HEIGHT, IMAGE_BITS_PER_PIXEL);
	RGBQUAD color;
	if (!result) {
		cerr << "Failed to allocate bitmap" << endl;
		exit(1);
	}

	for (size_t i = 0; i < IMAGE_WIDTH; i++) {
		for (size_t j = 0; j < IMAGE_HEIGHT; j++) {
			color.rgbRed = (BYTE)(this->image[i][j].red * 255.0);
			color.rgbGreen = (BYTE)(this->image[i][j].green * 255.0);
			color.rgbBlue = (BYTE)(this->image[i][j].blue * 255.0);
			FreeImage_SetPixelColor(result, i, j, &color);
		}
	}
	return result;
	// TODO: in Scene_Manager
	// if(FreeImage_Save(FIF_PNG, bitmap, "test.png", 0)) {
		// cout << "Image successfully saved!" << endl;
	// }
}