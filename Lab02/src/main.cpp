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
	int xa = atoi(argv[4]);
	int ya = atoi(argv[5]);
	int xb = atoi(argv[6]);
	int yb = atoi(argv[7]);
	int xc = atoi(argv[8]);
	int yc = atoi(argv[9]);

	if(xa < 0 || xa >= width || ya < 0 || ya >= height ||
       xb < 0 || xb >= width || yb < 0 || yb >= height ||
       xc < 0 || xc >= width || yc < 0 || yc >= height) {
        std::cout << "Error: Vertex coordinates must be within the image bounds." << endl;
        return 1;
    }

	boundingBox.xmin = min({xa, xb, xc});
	boundingBox.xmax = max({xa, xb, xc});
	boundingBox.ymax = max({ya, yb, yc});
	boundingBox.ymin = min({ya, yb, yc});
	// Create the image. We're using a `shared_ptr`, a C++11 feature.
	auto image = make_shared<Image>(width, height);
	// Draw a rectangle
	for(float y = boundingBox.ymin; y < boundingBox.ymax; ++y) {
		for(float x = boundingBox.xmin; x < boundingBox.xmax; ++x) {
			// beta  =  | xa - xc : x - xc | / | xb - xa : xc - xa |  =  ((xa - xc)(y - yc) - (x - xc)(ya - yc)) / ((xb - xa)(yc - ya) - (xc - xa )(yb - ya)) 
			//			| ya - yc : y - yc |   | yb - ya : yc - ya |

			// gamma =  | xb - xa : x - xa | / | xb - xa : xc - xa |  =  ((xb - xa)(y - ya) - (x - xa)(yb - ya)) / ((xb - xa)(yc - ya) - (xc - xa )(yb - ya)) 
			//			| yb - ya : y - ya |   | yb - ya : yc - ya |

			// alpha = 1 - beta - gamma

			// if alpha, beta, and gamma are between 0 - 1 then color it accordingly	

			float beta = ((xa - xc) * (y - yc) - (x - xc) * (ya - yc)) / ((xb - xa) * (yc - ya) - (xc - xa) * (yb - ya));
			float gamma = ((xb - xa) * (y - ya) - (x - xa) * (yb - ya)) / ((xb - xa) * (yc - ya) - (xc - xa) * (yb - ya));
			float alpha = 1 - beta - gamma;
			
			unsigned char r = 255 * alpha + 255 * beta + 128 * gamma;
			unsigned char g = 0 * alpha + 223 * beta + 0 * gamma;
			unsigned char b = 0 * alpha + 0 * beta + 128 * gamma;


			if (alpha > 0.0f && alpha < 1.0f && beta > 0.0f && beta < 1.0f && gamma > 0.0f && gamma < 1.0f){
				image->setPixel(x, y, r, g, b);
			}

		}
	}
	// Write image to file
	image->writeToFile(filename);
	return 0;
}
