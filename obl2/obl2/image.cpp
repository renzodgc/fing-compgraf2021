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
			max_intensity = max(max_intensity, this->image[i][j].red);
			max_intensity = max(max_intensity, this->image[i][j].green);
			max_intensity = max(max_intensity, this->image[i][j].blue);
		}
	}

	// Normalize and convert to Byte
	for (size_t i = 0; i < IMAGE_WIDTH; i++) {
		for (size_t j = 0; j < IMAGE_HEIGHT; j++) {

			// Apply gamma correction if max intensity gets over 1
			if (max_intensity > 1) {
				color.rgbRed = (BYTE)(pow(this->image[i][j].red / max_intensity, GAMMA_CORRECTION) * 255.0);
				color.rgbGreen = (BYTE)(pow(this->image[i][j].green / max_intensity, GAMMA_CORRECTION) * 255.0);
				color.rgbBlue = (BYTE)(pow(this->image[i][j].blue / max_intensity, GAMMA_CORRECTION) * 255.0);
			}

			// If not, just convert to byte
			else {
				color.rgbRed = (BYTE)(this->image[i][j].red * 255.0);
				color.rgbGreen = (BYTE)(this->image[i][j].green * 255.0);
				color.rgbBlue = (BYTE)(this->image[i][j].blue  * 255.0);
			}
			FreeImage_SetPixelColor(result, i, j, &color);
		}
	}
	return result;
}
