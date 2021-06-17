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
	// TODO: https://www.notion.so/Gamma-Correction-Normalizar-colores-en-imagenes-844a1e1e05e84ebca0efce7155a3c5b9
	// Gamma-Correction: Re-Normalize color values when they go beyond 0..1

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
}
