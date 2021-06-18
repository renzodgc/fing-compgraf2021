#ifndef IMAGE_H
#define IMAGE_H


// DEPENDENCIES
// -----------------------------------------------------------------------------------

#include <vector> // std::vector
#include <algorithm>
#include "FreeImage.h"
#include "colors.h"
#include "parameters.h"
#include "math_helper.h"

// ENUMERATES
// -----------------------------------------------------------------------------------

enum class ImageIs {
	FullResult,
	ColorAmbient, ColorDiffuse, ColorSpecular,
	Ambient, Diffuse, Specular, Reflection, Transmission
};

// MAIN CLASS
// -----------------------------------------------------------------------------------

class Image {

	public:

		// Constructor
		Image();
		~Image();

		// Main properties
		int height;
		int width;
		Color image[IMAGE_WIDTH][IMAGE_HEIGHT];

		// Main methods
		FIBITMAP * float_to_bitmap();
};

#endif
