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
	// TODO: Re-Normalize color values when they go beyond 0..1
	// Ojo que no es tan simple como usar min-max
	// porque si una pequenia parte de la imagen tiene como 1000 de color y la pasas a 1 entonces el resto queda ultra oscuro
	// Hay que hacer algo tipo limitar el maximo de color antes de normalizar o alguna otra estrategia.

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
