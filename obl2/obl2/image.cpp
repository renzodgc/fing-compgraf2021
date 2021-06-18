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
	double max_intensity = 0.;

	FIBITMAP* result = FreeImage_Allocate(IMAGE_WIDTH, IMAGE_HEIGHT, IMAGE_BITS_PER_PIXEL);
	RGBQUAD color;
	if (!result) {
		cerr << "Failed to allocate bitmap" << endl;
		exit(1);
	}

	// Get highest color value for normalization 0..1
	for (size_t i = 0; i < IMAGE_WIDTH; i++) {
		for (size_t j = 0; j < IMAGE_HEIGHT; j++) {
			max_intensity = max(max_intensity, max(this->image[i][j].red, max(this->image[i][j].green, this->image[i][j].blue)));
		}
	}

	// Normalize. Apply Gamma Correction. Convert to Byte
	for (size_t i = 0; i < IMAGE_WIDTH; i++) {
		for (size_t j = 0; j < IMAGE_HEIGHT; j++) {
			color.rgbRed = (BYTE)(pow(this->image[i][j].red / max_intensity, GAMMA_CORRECTION) * 255.0);
			color.rgbGreen = (BYTE)(pow(this->image[i][j].green / max_intensity, GAMMA_CORRECTION) * 255.0);
			color.rgbBlue = (BYTE)(pow(this->image[i][j].blue / max_intensity, GAMMA_CORRECTION) * 255.0);
			FreeImage_SetPixelColor(result, i, j, &color);
		}
	}
	return result;
}
