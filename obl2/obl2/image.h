#ifndef IMAGE_H
#define IMAGE_H

#include <vector> // std::vector
#include <algorithm>
#include "FreeImage.h"
#include "colors.h"
#include "parameters.h"
#include "math_helper.h"

using namespace std;

class Image {
public:
	int height;
	int width;
	Color image[IMAGE_WIDTH][IMAGE_HEIGHT];

	Image();
	~Image();

	FIBITMAP * float_to_bitmap();
};

#endif
