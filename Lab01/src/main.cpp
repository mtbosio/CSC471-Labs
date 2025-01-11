#include <iostream>
#include <string>
#include <vector>
#include <memory>
#include "Image.h"
#include <algorithm>

// This allows you to skip the `std::` in front of C++ standard library
// functions. You can also say `using std::cout` to be more selective.
// You should never do this in a header file.
using namespace std;

struct bbox{             
    int xmin;         
	int xmax;
	int ymin;
	int ymax;
};     

int main(int argc, char **argv)
{
	bbox boundingBox;
	if(argc < 10) {
		cout << "Usage: Lab1 <out_image_name>.png width height" << endl;
		return 0;
	}
	// Output filename
	string filename(argv[1]);
	// Width of image
	int width = atoi(argv[2]);
	// Height of image
	int height = atoi(argv[3]);
	int v1x = atoi(argv[4]);
	int v1y = atoi(argv[5]);
	int v2x = atoi(argv[6]);
	int v2y = atoi(argv[7]);
	int v3x = atoi(argv[8]);
	int v3y = atoi(argv[9]);

	if(v1x < 0 || v1x >= width || v1y < 0 || v1y >= height ||
       v2x < 0 || v2x >= width || v2y < 0 || v2y >= height ||
       v3x < 0 || v3x >= width || v3y < 0 || v3y >= height) {
        std::cout << "Error: Vertex coordinates must be within the image bounds." << endl;
        return 1;
    }

	boundingBox.xmin = min({v1x, v2x, v3x});
	boundingBox.xmax = max({v1x, v2x, v3x});
	boundingBox.ymax = max({v1y, v2y, v3y});
	boundingBox.ymin = min({v1y, v2y, v3y});
	// Create the image. We're using a `shared_ptr`, a C++11 feature.
	auto image = make_shared<Image>(width, height);
	// Draw a rectangle
	for(int y = boundingBox.ymin; y < boundingBox.ymax; ++y) {
		for(int x = boundingBox.xmin; x < boundingBox.xmax; ++x) {
			unsigned char r = 255;
			unsigned char g = 0;
			unsigned char b = 0;
			image->setPixel(x, y, r, g, b);
		}
	}
	image->setPixel(v1x, v1y, 0, 255, 0);
	image->setPixel(v2x, v2y, 0, 255, 0);
	image->setPixel(v3x, v3y, 0, 255, 0);
	// Write image to file
	image->writeToFile(filename);
	return 0;
}
